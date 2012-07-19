#include "UnityProxy.h"
#include <nsCOMPtr.h>
#include <nsIObserverService.h>
#include <nsServiceManagerUtils.h>

#define NOTIFY_IGNORE_TIME 10 // seconds

static nsCOMPtr<nsIObserverService> observerService = NULL;
static UnityMusicPlayer *musicPlayer = NULL;
static UnityTrackMetadata *trackMetadata = NULL;
static GtkWindow *playerGtkWindow = NULL;
static gchar *playerName = NULL;
static gchar *playerIcon = NULL;
static GTimer *notifyTimer = NULL;

static gboolean enableNotify = true;

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

void onNext (GtkWidget *window,
              gpointer data)
{
	g_timer_start (notifyTimer);
	observerService->NotifyObservers (NULL, "sound-menu-next", NULL);
}

void onPrevious (GtkWidget *window,
                  gpointer data)
{
	g_timer_start (notifyTimer);
	observerService->NotifyObservers (NULL, "sound-menu-previous", NULL);
}

void onRaise (GtkWidget *window,
               gpointer data)
{	
	gdk_window_show( ((GtkWidget*) playerGtkWindow) -> window );
}

void checkWindowTitle (gpointer data, 
                       gpointer user_data)
{
	const gchar *title = gtk_window_get_title ((GtkWindow*) data);
	
	if (playerGtkWindow || g_strcmp0 (title, (char*) user_data)) return;
	
	playerGtkWindow = (GtkWindow*) data;
}

NS_IMPL_ISUPPORTS1 (UnityProxy, IUnityProxy)

UnityProxy::UnityProxy ()
{	
	observerService = do_GetService ("@mozilla.org/observer-service;1");
	
	trackMetadata = unity_track_metadata_new ();
	
	notifyTimer = g_timer_new ();
}

UnityProxy::~UnityProxy ()
{
	unity_music_player_unexport (musicPlayer);
	notify_uninit ();
}

NS_IMETHODIMP UnityProxy::InitializeFor (const char* desktopFileName, const char* windowTitle)
{
	if (!desktopFileName || !windowTitle) return NS_ERROR_INVALID_ARG;
	
	GList* wlist = gtk_window_list_toplevels ();
	g_list_foreach (wlist, checkWindowTitle, (gpointer) windowTitle);
	g_list_free (wlist);
	
	if (!playerGtkWindow) return NS_ERROR_INVALID_ARG;
	
	GKeyFile *keyFile = g_key_file_new ();
	gchar *desktopFilePath = g_build_filename ("/usr/share/applications", desktopFileName, NULL);
	if (g_key_file_load_from_file (keyFile, desktopFilePath, G_KEY_FILE_NONE, NULL))
	{
		playerName = g_key_file_get_string (keyFile, "Desktop Entry", "Name", NULL);
		playerIcon = g_key_file_get_string (keyFile, "Desktop Entry", "Icon", NULL);
	}
	g_free (keyFile);
	
	if (!playerName || !playerIcon) return NS_ERROR_UNEXPECTED;
	
	notify_init (playerName);
	
	musicPlayer = unity_music_player_new (desktopFileName);
	if (!musicPlayer) return NS_ERROR_INVALID_ARG;
	
	unity_music_player_set_title (musicPlayer, playerName);
	unity_music_player_export (musicPlayer);
	
	unity_music_player_set_can_go_next (musicPlayer, false);
	unity_music_player_set_can_play (musicPlayer, true);
	
	g_signal_connect (G_OBJECT (musicPlayer), "play_pause", G_CALLBACK (onPlayPause), NULL);
	g_signal_connect (G_OBJECT (musicPlayer), "next", G_CALLBACK (onNext), NULL);
	g_signal_connect (G_OBJECT (musicPlayer), "previous", G_CALLBACK (onPrevious), NULL);
	g_signal_connect (G_OBJECT (musicPlayer), "raise", G_CALLBACK (onRaise), NULL);
	
	return NS_OK;
}

NS_IMETHODIMP UnityProxy::SoundMenuSetTrackInfo (const char *title, const char *artist, const char *album, const char *coverFilePath)
{
	if (!musicPlayer) return NS_ERROR_NOT_INITIALIZED;
	
	unity_track_metadata_set_artist (trackMetadata, artist);
	unity_track_metadata_set_album (trackMetadata, album);
	unity_track_metadata_set_title (trackMetadata, title);
	
	GFile *coverFile = g_file_new_for_path (coverFilePath);
	unity_track_metadata_set_art_location (trackMetadata, coverFile);
	
	unity_music_player_set_current_track (musicPlayer, trackMetadata);
	
	g_object_unref (coverFile);
	
	if (enableNotify && !gtk_window_is_active (playerGtkWindow))
	{
		gdouble timElapsedSec = g_timer_elapsed (notifyTimer, NULL);
		if (timElapsedSec > NOTIFY_IGNORE_TIME)
		{
			g_timer_start (notifyTimer);
			
			gchar *summaryStr = g_strdup_printf ("%s", title);
			gchar *bodyStr = g_strdup_printf ("%s - %s", artist, album);
			
			const char *icon;
			if (!coverFilePath) {
				icon = playerIcon;
			}
			else {
				icon = coverFilePath;
			}
			
			NotifyNotification *unityNotification = notify_notification_new (summaryStr, bodyStr, icon);
			notify_notification_show (unityNotification, NULL);
			
			g_object_unref(unityNotification);
			
			g_free (summaryStr);
			g_free (bodyStr);
		}
	}
	
	return NS_OK;
}

NS_IMETHODIMP UnityProxy::SoundMenuSetPlayingState (PRInt16 playing)
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

NS_IMETHODIMP UnityProxy::HideWindow ()
{
	if (!musicPlayer) return NS_ERROR_NOT_INITIALIZED;
	
	gdk_window_hide ( ((GtkWidget*) playerGtkWindow) -> window );
    
	return NS_OK;
}

NS_IMETHODIMP UnityProxy::ShowWindow ()
{
	if (!musicPlayer) return NS_ERROR_NOT_INITIALIZED;
	
	gdk_window_show ( ((GtkWidget*) playerGtkWindow) -> window );
	
	return NS_OK;
}

NS_IMETHODIMP UnityProxy::EnableNotifications (PRBool needEnable)
{
	enableNotify = !!needEnable;
	
	return NS_OK;
}
