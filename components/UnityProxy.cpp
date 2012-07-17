#include "UnityProxy.h"
#include <nsCOMPtr.h>
#include <nsIObserverService.h>
#include <nsServiceManagerUtils.h>

static nsCOMPtr<nsIObserverService> observerService;
static UnityMusicPlayer *musicPlayer;
static UnityTrackMetadata *trackMetadata;
static GFile* coverFile;

void onPlayPause (GtkWidget *window,
                   gpointer data)
{
	UnityPlaybackState playbackState = unity_music_player_get_playback_state (musicPlayer);
	if (playbackState == UNITY_PLAYBACK_STATE_PLAYING) {
		//unity_music_player_set_playback_state(musicPlayer, UNITY_PLAYBACK_STATE_PAUSED);
		observerService->NotifyObservers (NULL, "sound-menu-pause", NULL);
	}
	else {
		//unity_music_player_set_playback_state(musicPlayer, UNITY_PLAYBACK_STATE_PLAYING);
		observerService->NotifyObservers (NULL, "sound-menu-play", NULL);
	}
}

void onNext  (GtkWidget *window,
                   gpointer data)
{
	observerService->NotifyObservers (NULL, "sound-menu-next", NULL);
}

void onPrevious  (GtkWidget *window,
                   gpointer data)
{
	observerService->NotifyObservers (NULL, "sound-menu-previous", NULL);
}

// Этот макрос вставляет стандартную реализацию методов AddRef(), Release() и QueryInterface().
// Параметры - класс и интерфейс.
NS_IMPL_ISUPPORTS1(UnityProxy, IUnityProxy)

UnityProxy::UnityProxy()
{	
	observerService = do_GetService ("@mozilla.org/observer-service;1");
	
	trackMetadata = unity_track_metadata_new ();
	
	musicPlayer = unity_music_player_new ("nightingale.desktop");
	unity_music_player_set_title (musicPlayer, "Nightingale");
	unity_music_player_export (musicPlayer);
	
	unity_music_player_set_can_go_next (musicPlayer, false);
	unity_music_player_set_can_play (musicPlayer, true);
	
	g_signal_connect (G_OBJECT (musicPlayer), "play_pause", G_CALLBACK (onPlayPause), NULL);
	g_signal_connect (G_OBJECT (musicPlayer), "next", G_CALLBACK (onNext), NULL);
	g_signal_connect (G_OBJECT (musicPlayer), "previous", G_CALLBACK (onPrevious), NULL);
}

UnityProxy::~UnityProxy()
{
	unity_music_player_unexport (musicPlayer);
}

// Реализация метода Add()
NS_IMETHODIMP UnityProxy::Add(PRInt32 a, PRInt32 b, PRInt32 *_retval)
{	
	UnityLauncherEntry* entry1 = unity_launcher_entry_get_for_desktop_id ("firefox.desktop");
	unity_launcher_entry_set_count_visible (entry1, true);

	*_retval = a + b;
	return NS_OK;
}

NS_IMETHODIMP UnityProxy::SoundMenuSetName(const char *title)
{
	unity_music_player_set_title (musicPlayer, title);
	
	return NS_OK;
}

NS_IMETHODIMP UnityProxy::SoundMenuSetTrackInfo(const char *artist = NULL, const char *album = NULL, const char *title = NULL, const char *coverFilePath = NULL)
{
	unity_track_metadata_set_artist (trackMetadata, artist);
	unity_track_metadata_set_album (trackMetadata, album);
	unity_track_metadata_set_title (trackMetadata, title);
	
	coverFile = g_file_new_for_path(coverFilePath);
	unity_track_metadata_set_art_location(trackMetadata, coverFile);
	
	unity_music_player_set_current_track (musicPlayer, trackMetadata);
	
	return NS_OK;
}

NS_IMETHODIMP UnityProxy::SoundMenuSetPlayingState(PRInt16 playing)
{
	if (playing < 0) {
		unity_music_player_set_playback_state (musicPlayer, UNITY_PLAYBACK_STATE_PAUSED);
		unity_music_player_set_current_track (musicPlayer, NULL);
	}
	else if (!!playing) {
		unity_music_player_set_playback_state (musicPlayer, UNITY_PLAYBACK_STATE_PLAYING);
	}
	else {
		unity_music_player_set_playback_state (musicPlayer, UNITY_PLAYBACK_STATE_PAUSED);
	}
		
	return NS_OK;
}
