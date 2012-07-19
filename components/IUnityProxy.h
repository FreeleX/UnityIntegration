/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM IUnityProxy.idl
 */

#ifndef __gen_IUnityProxy_h__
#define __gen_IUnityProxy_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

#ifndef __gen_nsIObserverService_h__
#include "nsIObserverService.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    IUnityProxy */
#define IUNITYPROXY_IID_STR "629a9e10-cabf-11e1-9b23-0800200c9a66"

#define IUNITYPROXY_IID \
  {0x629a9e10, 0xcabf, 0x11e1, \
    { 0x9b, 0x23, 0x08, 0x00, 0x20, 0x0c, 0x9a, 0x66 }}

class NS_NO_VTABLE NS_SCRIPTABLE IUnityProxy : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IUNITYPROXY_IID)

  /* void InitializeFor (in string desktopFileName, in string windowTitle); */
  NS_SCRIPTABLE NS_IMETHOD InitializeFor(const char *desktopFileName, const char *windowTitle) = 0;

  /* void SoundMenuSetTrackInfo (in string title, in string artist, in string album, in string coverFilePath); */
  NS_SCRIPTABLE NS_IMETHOD SoundMenuSetTrackInfo(const char *title, const char *artist, const char *album, const char *coverFilePath) = 0;

  /* void SoundMenuSetPlayingState (in PRInt16 playing); */
  NS_SCRIPTABLE NS_IMETHOD SoundMenuSetPlayingState(PRInt16 playing) = 0;

  /* void HideWindow (); */
  NS_SCRIPTABLE NS_IMETHOD HideWindow(void) = 0;

  /* void ShowWindow (); */
  NS_SCRIPTABLE NS_IMETHOD ShowWindow(void) = 0;

  /* void EnableNotifications (in PRBool needEnable); */
  NS_SCRIPTABLE NS_IMETHOD EnableNotifications(PRBool needEnable) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IUnityProxy, IUNITYPROXY_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IUNITYPROXY \
  NS_SCRIPTABLE NS_IMETHOD InitializeFor(const char *desktopFileName, const char *windowTitle); \
  NS_SCRIPTABLE NS_IMETHOD SoundMenuSetTrackInfo(const char *title, const char *artist, const char *album, const char *coverFilePath); \
  NS_SCRIPTABLE NS_IMETHOD SoundMenuSetPlayingState(PRInt16 playing); \
  NS_SCRIPTABLE NS_IMETHOD HideWindow(void); \
  NS_SCRIPTABLE NS_IMETHOD ShowWindow(void); \
  NS_SCRIPTABLE NS_IMETHOD EnableNotifications(PRBool needEnable); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IUNITYPROXY(_to) \
  NS_SCRIPTABLE NS_IMETHOD InitializeFor(const char *desktopFileName, const char *windowTitle) { return _to InitializeFor(desktopFileName, windowTitle); } \
  NS_SCRIPTABLE NS_IMETHOD SoundMenuSetTrackInfo(const char *title, const char *artist, const char *album, const char *coverFilePath) { return _to SoundMenuSetTrackInfo(title, artist, album, coverFilePath); } \
  NS_SCRIPTABLE NS_IMETHOD SoundMenuSetPlayingState(PRInt16 playing) { return _to SoundMenuSetPlayingState(playing); } \
  NS_SCRIPTABLE NS_IMETHOD HideWindow(void) { return _to HideWindow(); } \
  NS_SCRIPTABLE NS_IMETHOD ShowWindow(void) { return _to ShowWindow(); } \
  NS_SCRIPTABLE NS_IMETHOD EnableNotifications(PRBool needEnable) { return _to EnableNotifications(needEnable); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IUNITYPROXY(_to) \
  NS_SCRIPTABLE NS_IMETHOD InitializeFor(const char *desktopFileName, const char *windowTitle) { return !_to ? NS_ERROR_NULL_POINTER : _to->InitializeFor(desktopFileName, windowTitle); } \
  NS_SCRIPTABLE NS_IMETHOD SoundMenuSetTrackInfo(const char *title, const char *artist, const char *album, const char *coverFilePath) { return !_to ? NS_ERROR_NULL_POINTER : _to->SoundMenuSetTrackInfo(title, artist, album, coverFilePath); } \
  NS_SCRIPTABLE NS_IMETHOD SoundMenuSetPlayingState(PRInt16 playing) { return !_to ? NS_ERROR_NULL_POINTER : _to->SoundMenuSetPlayingState(playing); } \
  NS_SCRIPTABLE NS_IMETHOD HideWindow(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->HideWindow(); } \
  NS_SCRIPTABLE NS_IMETHOD ShowWindow(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->ShowWindow(); } \
  NS_SCRIPTABLE NS_IMETHOD EnableNotifications(PRBool needEnable) { return !_to ? NS_ERROR_NULL_POINTER : _to->EnableNotifications(needEnable); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IUnityProxy
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IUNITYPROXY

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IUnityProxy)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* void InitializeFor (in string desktopFileName, in string windowTitle); */
NS_IMETHODIMP _MYCLASS_::InitializeFor(const char *desktopFileName, const char *windowTitle)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SoundMenuSetTrackInfo (in string title, in string artist, in string album, in string coverFilePath); */
NS_IMETHODIMP _MYCLASS_::SoundMenuSetTrackInfo(const char *title, const char *artist, const char *album, const char *coverFilePath)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SoundMenuSetPlayingState (in PRInt16 playing); */
NS_IMETHODIMP _MYCLASS_::SoundMenuSetPlayingState(PRInt16 playing)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void HideWindow (); */
NS_IMETHODIMP _MYCLASS_::HideWindow()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void ShowWindow (); */
NS_IMETHODIMP _MYCLASS_::ShowWindow()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void EnableNotifications (in PRBool needEnable); */
NS_IMETHODIMP _MYCLASS_::EnableNotifications(PRBool needEnable)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_IUnityProxy_h__ */
