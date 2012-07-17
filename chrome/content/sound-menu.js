try {
Components.utils.import("resource://gre/modules/XPCOMUtils.jsm"); 
Components.utils.import("resource://app/jsmodules/sbProperties.jsm");
}
catch (error) {alert("MLyrics: Unexpected error - module import error\n\n" + error)}

const UNITY_PLAYBACK_STATE_PAUSED = 0;
const UNITY_PLAYBACK_STATE_PLAYING = 1;
const UNITY_PLAYBACK_STATE_STOPED = -1;

if (typeof UnityIntegration == 'undefined') {
  var UnityIntegration = {};
};

UnityIntegration.soundMenu = {
	xulAppInfo: null,
	gMM: null,
	wm: null,
	unityServiceProxy: null,
	observerService: null,
	mainwindow: null,
	
	onLoad: function () {
		//alert("Unity Integration loaded!");
		
		this.xulAppInfo = Components.classes["@mozilla.org/xre/app-info;1"].getService(Components.interfaces.nsIXULAppInfo);
		this.gMM = Components.classes["@songbirdnest.com/Songbird/Mediacore/Manager;1"].getService(Components.interfaces.sbIMediacoreManager);
		this.wm = Components.classes["@mozilla.org/appshell/window-mediator;1"].getService(Components.interfaces.nsIWindowMediator);
		this.mainwindow = this.wm.getMostRecentWindow("Songbird:Main");
		
		this.unityServiceProxy = Components.classes["@LookingMan.org/Songbird-Nightingale/UnityProxy;1"].getService(Components.interfaces.IUnityProxy);
		
		if (this.xulAppInfo.name == "Songbird")
			this.unityServiceProxy.InitializeFor("songbird.desktop", "Songbird");
		else if (this.xulAppInfo.name == "Nightingale")
			this.unityServiceProxy.InitializeFor("nightingale.desktop", "Nightingale");
		else {
			alert("Unity Integration: Unexpected error - your application is not supported")
			return;
		}
		
		var mm = this.gMM;
		var that = this;
		
		var soundMenuObserver = {
				observe : function(subject, topic, data) {
					switch (topic) {
						case "sound-menu-play":
							
							// If we are already playing something just pause/unpause playback
							var sbIMediacoreStatus = Components.interfaces.sbIMediacoreStatus;
							if (mm.status.state == sbIMediacoreStatus.STATUS_PAUSED) {
								mm.playbackControl.play();
							} else if(mm.status.state == sbIMediacoreStatus.STATUS_PLAYING ||
							           mm.status.state == sbIMediacoreStatus.STATUS_BUFFERING) {
								that.unityServiceProxy.SoundMenuSetPlayingState(true);
								// Otherwise dispatch a play event.  Someone should catch this
								// and intelligently initiate playback.  If not, just have
								// the playback service play the default.
							} else {
								var event = document.createEvent("Events");
								event.initEvent("Play", true, true);
								var notHandled = that.mainwindow.dispatchEvent(event);
								if (notHandled) {
									// If we have no context, initiate playback
									// via the root application controller
									var app = Components.classes["@songbirdnest.com/Songbird/ApplicationController;1"]
															.getService(Components.interfaces.sbIApplicationController);
									app.playDefault();
								}
							}
							break;
							
						case "sound-menu-pause":
							songbird.pause();
							break;
							
						case "sound-menu-next":
							songbird.next();
							break;
							
						case "sound-menu-previous":
							songbird.previous();
							break;
					}
				}
			};

		this.observerService = Components.classes["@mozilla.org/observer-service;1"].getService(Components.interfaces.nsIObserverService);
		this.observerService.addObserver(soundMenuObserver, "sound-menu-play", false);
		this.observerService.addObserver(soundMenuObserver, "sound-menu-pause", false);
		this.observerService.addObserver(soundMenuObserver, "sound-menu-next", false);
		this.observerService.addObserver(soundMenuObserver, "sound-menu-previous", false);
		
		this.gMM.addListener({
			onMediacoreEvent : function(event) {
				var item = event.data;
				if (that.gMM.sequencer.view == null) return;
				var list = that.gMM.sequencer.view.mediaList;

				switch (event.type) {
					case Components.interfaces.sbIMediacoreEvent.TRACK_CHANGE:
						var artist = gMM.sequencer.currentItem.getProperty(SBProperties.artistName);
						var album = gMM.sequencer.currentItem.getProperty(SBProperties.albumName);
						var track = gMM.sequencer.currentItem.getProperty(SBProperties.trackName);
						that.unityServiceProxy.SoundMenuSetTrackInfo(artist, album, track, null);
						break;
						
					case Components.interfaces.sbIMediacoreEvent.STREAM_START:
						that.unityServiceProxy.SoundMenuSetPlayingState(UNITY_PLAYBACK_STATE_PLAYING);
						break;
						
					case Components.interfaces.sbIMediacoreEvent.STREAM_PAUSE:
						that.unityServiceProxy.SoundMenuSetPlayingState(UNITY_PLAYBACK_STATE_PAUSED);
						break;
						
					case Components.interfaces.sbIMediacoreEvent.STREAM_STOP:
					case Components.interfaces.sbIMediacoreEvent.STREAM_END:
						that.unityServiceProxy.SoundMenuSetPlayingState(UNITY_PLAYBACK_STATE_STOPED);
						break;
						
					default:
						break;
				}
			}
			});
		
		//this.unityServiceProxy.SoundMenuSetTitle("Nightingale");
		//this.unityServiceProxy.SoundMenuSetTrackInfo("Artist11", "Album12", "Track13", "/home/alex/Temp/Sexy_Girls_22 (70).jpg");

	},
	
	onUnLoad: function () {
	}
};

window.addEventListener("load",   function(e) { UnityIntegration.soundMenu.onLoad(); },   false);
window.addEventListener("unload", function(e) { UnityIntegration.soundMenu.onUnLoad(); }, false);
