Components.utils.import("resource://gre/modules/XPCOMUtils.jsm"); 

if (typeof UnityIntegration == 'undefined') {
  var UnityIntegration = {};
};

UnityIntegration.soundMenu = {
	gMM: null,
	wm: null,
	unityServiceProxy: null,
	observerService: null,
	mainwindow: null,
	
	onLoad: function () {
		//alert("Unity Integration loaded!");
		
		this.gMM = Components.classes["@songbirdnest.com/Songbird/Mediacore/Manager;1"].getService(Components.interfaces.sbIMediacoreManager);
		this.wm = Components.classes["@mozilla.org/appshell/window-mediator;1"].getService(Components.interfaces.nsIWindowMediator);
		this.mainwindow = this.wm.getMostRecentWindow("Songbird:Main");
		
		this.unityServiceProxy = Components.classes["@LookingMan.org/Songbird-Nightingale/UnityProxy;1"].createInstance();
		this.unityServiceProxy = this.unityServiceProxy.QueryInterface(Components.interfaces.IUnityProxy);
		
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
								that.unityServiceProxy.SoundMenuSetPlayingState(true);
							} else if(mm.status.state == sbIMediacoreStatus.STATUS_PLAYING ||
							           mm.status.state == sbIMediacoreStatus.STATUS_BUFFERING) {
								//mm.playbackControl.pause();
								that.unityServiceProxy.SoundMenuSetPlayingState(false);
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
								that.unityServiceProxy.SoundMenuSetPlayingState(true);
							}
							break;
							
						case "sound-menu-pause":
							songbird.pause();
							that.unityServiceProxy.SoundMenuSetPlayingState(false);
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
		
		//this.unityServiceProxy.SoundMenuSetTitle("Nightingale");
		this.unityServiceProxy.SoundMenuSetTrackInfo("Artist11", "Album12", "Track13", "/home/alex/Temp/Sexy_Girls_22 (70).jpg");

	},
	
	onUnLoad: function () {
	}
};

window.addEventListener("load",   function(e) { UnityIntegration.soundMenu.onLoad(); },   false);
window.addEventListener("unload", function(e) { UnityIntegration.soundMenu.onUnLoad(); }, false);
