#include "UnityProxy.h"
#include <nsCOMPtr.h>
#include <nsIObserverService.h>
#include <nsServiceManagerUtils.h>

static nsCOMPtr<nsIObserverService> observerService = NULL;
static UnityMusicPlayer *musicPlayer = NULL;
static UnityTrackMetadata *trackMetadata = NULL;
static GFile* coverFile = NULL;

void onPlayPause (GtkWidget *window,
                   gpointer data)
{
	UnityPlaybackState playbackState = unity_music_player_get_playback_state (musicPlayer);
	if (playbackState == UNITY_PLAYBACK_STATE_PLAYING) {
		observerService->NotifyObservers (NULL, "sound-menu-pause", NULL);
	}
	else {
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

NS_IMPL_ISUPPORTS1(UnityProxy, IUnityProxy)

UnityProxy::UnityProxy()
{	
	observerService = do_GetService ("@mozilla.org/observer-service;1");
	
	trackMetadata = unity_track_metadata_new ();
}

UnityProxy::~UnityProxy()
{
	unity_music_player_unexport (musicPlayer);
}

NS_IMETHODIMP UnityProxy::InitializeFor(const char* desktopFileName, const char* title)
{
	musicPlayer = unity_music_player_new (desktopFileName);
	if (!musicPlayer) return NS_ERROR_NOT_INITIALIZED;
	
	unity_music_player_set_title (musicPlayer, title);
	unity_music_player_export (musicPlayer);
	
	unity_music_player_set_can_go_next (musicPlayer, false);
	unity_music_player_set_can_play (musicPlayer, true);
	
	g_signal_connect (G_OBJECT (musicPlayer), "play_pause", G_CALLBACK (onPlayPause), NULL);
	g_signal_connect (G_OBJECT (musicPlayer), "next", G_CALLBACK (onNext), NULL);
	g_signal_connect (G_OBJECT (musicPlayer), "previous", G_CALLBACK (onPrevious), NULL);
	
	return NS_OK;
}

NS_IMETHODIMP UnityProxy::SoundMenuSetTrackInfo(const char *artist, const char *album, const char *title, const char *coverFilePath)
{
	if (!musicPlayer) return NS_ERROR_NOT_INITIALIZED;
	
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
	if (!musicPlayer) return NS_ERROR_NOT_INITIALIZED;
	
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
