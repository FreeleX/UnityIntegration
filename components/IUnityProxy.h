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

  /* long Add (in long a, in long b); */
  NS_SCRIPTABLE NS_IMETHOD Add(PRInt32 a, PRInt32 b, PRInt32 *_retval NS_OUTPARAM) = 0;

  /* void SoundMenuSetName (in string title); */
  NS_SCRIPTABLE NS_IMETHOD SoundMenuSetName(const char *title) = 0;

  /* void SoundMenuSetTrackInfo (in string artist, in string album, in string title, in string coverFilePath); */
  NS_SCRIPTABLE NS_IMETHOD SoundMenuSetTrackInfo(const char *artist, const char *album, const char *title, const char *coverFilePath) = 0;

  /* void SoundMenuSetPlayingState (in PRBool playing); */
  NS_SCRIPTABLE NS_IMETHOD SoundMenuSetPlayingState(PRBool playing) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IUnityProxy, IUNITYPROXY_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IUNITYPROXY \
  NS_SCRIPTABLE NS_IMETHOD Add(PRInt32 a, PRInt32 b, PRInt32 *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD SoundMenuSetName(const char *title); \
  NS_SCRIPTABLE NS_IMETHOD SoundMenuSetTrackInfo(const char *artist, const char *album, const char *title, const char *coverFilePath); \
  NS_SCRIPTABLE NS_IMETHOD SoundMenuSetPlayingState(PRBool playing); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IUNITYPROXY(_to) \
  NS_SCRIPTABLE NS_IMETHOD Add(PRInt32 a, PRInt32 b, PRInt32 *_retval NS_OUTPARAM) { return _to Add(a, b, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD SoundMenuSetName(const char *title) { return _to SoundMenuSetName(title); } \
  NS_SCRIPTABLE NS_IMETHOD SoundMenuSetTrackInfo(const char *artist, const char *album, const char *title, const char *coverFilePath) { return _to SoundMenuSetTrackInfo(artist, album, title, coverFilePath); } \
  NS_SCRIPTABLE NS_IMETHOD SoundMenuSetPlayingState(PRBool playing) { return _to SoundMenuSetPlayingState(playing); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IUNITYPROXY(_to) \
  NS_SCRIPTABLE NS_IMETHOD Add(PRInt32 a, PRInt32 b, PRInt32 *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->Add(a, b, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD SoundMenuSetName(const char *title) { return !_to ? NS_ERROR_NULL_POINTER : _to->SoundMenuSetName(title); } \
  NS_SCRIPTABLE NS_IMETHOD SoundMenuSetTrackInfo(const char *artist, const char *album, const char *title, const char *coverFilePath) { return !_to ? NS_ERROR_NULL_POINTER : _to->SoundMenuSetTrackInfo(artist, album, title, coverFilePath); } \
  NS_SCRIPTABLE NS_IMETHOD SoundMenuSetPlayingState(PRBool playing) { return !_to ? NS_ERROR_NULL_POINTER : _to->SoundMenuSetPlayingState(playing); } 

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

/* long Add (in long a, in long b); */
NS_IMETHODIMP _MYCLASS_::Add(PRInt32 a, PRInt32 b, PRInt32 *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SoundMenuSetName (in string title); */
NS_IMETHODIMP _MYCLASS_::SoundMenuSetName(const char *title)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SoundMenuSetTrackInfo (in string artist, in string album, in string title, in string coverFilePath); */
NS_IMETHODIMP _MYCLASS_::SoundMenuSetTrackInfo(const char *artist, const char *album, const char *title, const char *coverFilePath)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SoundMenuSetPlayingState (in PRBool playing); */
NS_IMETHODIMP _MYCLASS_::SoundMenuSetPlayingState(PRBool playing)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_IUnityProxy_h__ */
