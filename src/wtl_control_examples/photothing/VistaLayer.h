#if !defined(AFX_VISTALAYER_H__20070321_13AC_DF67_33D0_0080AD509054__INCLUDED_)
#define AFX_VISTALAYER_H__20070321_13AC_DF67_33D0_0080AD509054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/**
 * This is a wrapper layer for the DWM and BufferedPaint APIs 
 * available on Windows Vista. You should not use these as the
 * WTL library comes with some fine wrapper classes that you
 * can use. Unfortunately I'm still trapped on Visual Studio 6 
 * (Microsoft IDE from 1998) for some of my projects and it
 * will not load the latest Windows SDK .lib formats - so thus 
 * I need to manually wrap them on my own.
 */


//////////////////////////////////////////////////////////////////////
// DWM wrapper
//

#if WINVER < 0x0600

typedef struct DWM_BLURBEHIND
{
   DWORD dwFlags;
   BOOL fEnable;
   HRGN hRgnBlur;
   BOOL fTransitionOnMaximized;
} DWM_BLURBEHIND;

typedef struct tagDWL_MARGINS {
    int cxLeftWidth;
    int cxRightWidth;
    int cyTopHeight;
    int cyBottomHeight;
} DWM_MARGINS, *PDWM_MARGINS;

#define DWM_BB_ENABLE                 0x00000001
#define DWM_BB_BLURREGION             0x00000002
#define DWM_BB_TRANSITIONONMAXIMIZED  0x00000004

#define DWM_EC_DISABLECOMPOSITION     0x00000000
#define DWM_EC_ENABLECOMPOSITION      0x00000001

#endif // WINVER


class CVistaDwm
{
public:
   typedef HRESULT (WINAPI *FNDWMENABLECOMPOSITION)(UINT);
   typedef HRESULT (WINAPI *FNDWNISCOMPOSITIONENABLED)(LPBOOL);
   typedef HRESULT (WINAPI *FNENABLEBLURBEHINDWINDOW)(HWND, CONST DWM_BLURBEHIND*);
   typedef HRESULT (WINAPI *FNDWMEXTENDFRAMEINTOCLIENTAREA)(HWND, CONST DWM_MARGINS*);

   FNDWMENABLECOMPOSITION fnDwmEnableComposition;
   FNDWNISCOMPOSITIONENABLED fnDwmIsCompositionEnabled;
   FNENABLEBLURBEHINDWINDOW fnDwmEnableBlurBehindWindow;
   FNDWMEXTENDFRAMEINTOCLIENTAREA fnDwmExtendFrameIntoClientArea;

   CVistaDwm()
   {
      static HINSTANCE hDwmInstance = ::LoadLibrary(_T("dwmapi.dll"));
      if( hDwmInstance != NULL ) {
         fnDwmEnableComposition = (FNDWMENABLECOMPOSITION) ::GetProcAddress(hDwmInstance, "DwmEnableComposition");
         fnDwmIsCompositionEnabled = (FNDWNISCOMPOSITIONENABLED) ::GetProcAddress(hDwmInstance, "DwmIsCompositionEnabled");
         fnDwmEnableBlurBehindWindow = (FNENABLEBLURBEHINDWINDOW) ::GetProcAddress(hDwmInstance, "DwmEnableBlurBehindWindow");
         fnDwmExtendFrameIntoClientArea = (FNDWMEXTENDFRAMEINTOCLIENTAREA) ::GetProcAddress(hDwmInstance, "DwmExtendFrameIntoClientArea");
      }
      else {
         fnDwmEnableComposition = NULL;
         fnDwmIsCompositionEnabled = NULL;
         fnDwmEnableBlurBehindWindow = NULL;
         fnDwmExtendFrameIntoClientArea = NULL;
      }
   }

   BOOL IsCompositionEnabled() const
   {
      HRESULT Hr = E_NOTIMPL;
      BOOL bRes = FALSE;
      if( fnDwmIsCompositionEnabled != NULL ) Hr = fnDwmIsCompositionEnabled(&bRes);
      return SUCCEEDED(Hr) && bRes;
   }

   BOOL EnableComposition(UINT fEnable)
   {
      BOOL bRes = FALSE;
      if( fnDwmEnableComposition != NULL ) bRes = SUCCEEDED(fnDwmEnableComposition(fEnable));
      return bRes;
   }

   BOOL EnableBlurBehindWindow(HWND hWnd)
   {
      BOOL bRes = FALSE;
      if( fnDwmEnableBlurBehindWindow != NULL ) {
         DWM_BLURBEHIND bb = { 0 };
         bb.dwFlags = DWM_BB_ENABLE;
         bb.fEnable = TRUE;
         bRes = SUCCEEDED(fnDwmEnableBlurBehindWindow(hWnd, &bb));
      }
      return bRes;
   }

   BOOL EnableBlurBehindWindow(HWND hWnd, CONST DWM_BLURBEHIND& bb)
   {
      BOOL bRes = FALSE;
      if( fnDwmEnableBlurBehindWindow != NULL ) {
         bRes = SUCCEEDED(fnDwmEnableBlurBehindWindow(hWnd, &bb));
      }
      return bRes;
   }

   BOOL ExtendFrameIntoClientArea(HWND hWnd, CONST DWM_MARGINS& Margins)
   {
      BOOL bRes = FALSE;
      if( fnDwmEnableComposition != NULL ) bRes = SUCCEEDED(fnDwmExtendFrameIntoClientArea(hWnd, &Margins));
      return bRes;
   }
};


//////////////////////////////////////////////////////////////////////
// BufferedPaint and BufferedAnimation wrapper
//

#ifndef BPPF_ERASE

typedef HANDLE HANIMATIONBUFFER;
typedef HANDLE HPAINTBUFFER;

#define BPPF_ERASE     0x0001
#define BPPF_NOCLIP    0x0002
#define BPPF_NONCLIENT 0x0004

typedef enum _BP_BUFFERFORMAT {
    BPBF_COMPATIBLEBITMAP,
    BPBF_DIB,
    BPBF_TOPDOWNDIB,
    BPBF_TOPDOWNMONODIB
} BP_BUFFERFORMAT;

typedef enum _BP_ANIMATIONSTYLE {
    BPAS_NONE,
    BPAS_LINEAR,
    BPAS_CUBIC,
    BPAS_SINE
} BP_ANIMATIONSTYLE;

typedef struct _BP_ANIMATIONPARAMS {
    DWORD cbSize;
    DWORD dwFlags;
    BP_ANIMATIONSTYLE style;
    DWORD dwDuration;
} BP_ANIMATIONPARAMS, *PBP_ANIMATIONPARAMS;

typedef struct _BP_PAINTPARAMS {
    DWORD cbSize;
    DWORD dwFlags;
    CONST RECT *prcExclude;
    CONST BLENDFUNCTION *pBlendFunction;
} BP_PAINTPARAMS, *PBP_PAINTPARAMS;

#endif // BPPF_ERASE


class CVistaBufferedPaint
{
public:
   typedef HANIMATIONBUFFER (WINAPI *FNBEGINBUFFEREDANIMATION)(HWND, HDC, CONST RECT*, BP_BUFFERFORMAT, BP_PAINTPARAMS*, BP_ANIMATIONPARAMS*, HDC*, HDC*);
   typedef HPAINTBUFFER (WINAPI *FNBEGINBUFFEREDPAINT)(HDC hdcTarget, CONST RECT *prcTarget, BP_BUFFERFORMAT dwFormat, BP_PAINTPARAMS *pPaintParams, HDC *phdc);
   typedef HRESULT (WINAPI *FNBUFFEREDPAINTCLEAR)(HPAINTBUFFER hBufferedPaint, CONST RECT *prc);
   typedef HRESULT (WINAPI *FNBUFFEREDPAINTINIT)(VOID);
   typedef BOOL (WINAPI *FNBUFFEREDPAINTRENDERANIMATION)(HWND hwnd, HDC hdcTarget);
   typedef HRESULT (WINAPI *FNBUFFEREDPAINTSETALPHA)(HPAINTBUFFER hBufferedPaint, CONST RECT *prc, BYTE alpha);
   typedef HRESULT (WINAPI *FNBUFFEREDPAINTSTOPALLANIMATIONS)(HWND hwnd);
   typedef HRESULT (WINAPI *FNBUFFEREDPAINTUNINIT)(VOID);
   typedef HRESULT (WINAPI *FNENDBUFFEREDANIMATION)(HANIMATIONBUFFER hbpAnimation, BOOL fUpdateTarget);
   typedef BOOL (WINAPI *FNISCOMPOSITIONACTIVE)(VOID);
   typedef HRESULT (WINAPI *FNENDBUFFEREDPAINT)(HPAINTBUFFER hBufferedPaint, BOOL fUpdateTarget);
   typedef HRESULT (WINAPI *FNGETBUFFEREDPAINTBITS)(HPAINTBUFFER hBufferedPaint, RGBQUAD **ppbBuffer, int *pcxRow);
   typedef HDC (WINAPI *FNGETBUFFEREDPAINTDC)(HPAINTBUFFER hBufferedPaint);
   typedef HDC (WINAPI *FNGETBUFFEREDPAINTTARGETDC)(HPAINTBUFFER hBufferedPaint);
   typedef HRESULT (WINAPI *FNGETBUFFEREDPAINTTARGETRECT)(HPAINTBUFFER hBufferedPaint, RECT *prc);

   FNBEGINBUFFEREDANIMATION fnBeginBufferedAnimation;
   FNBEGINBUFFEREDPAINT fnBeginBufferedPaint;
   FNBUFFEREDPAINTCLEAR fnBufferedPaintClear;
   FNBUFFEREDPAINTINIT fnBufferedPaintInit;
   FNBUFFEREDPAINTRENDERANIMATION fnBufferedPaintRenderAnimation;
   FNBUFFEREDPAINTSETALPHA fnBufferedPaintSetAlpha;
   FNBUFFEREDPAINTSTOPALLANIMATIONS fnBufferedPaintStopAllAnimations;
   FNBUFFEREDPAINTUNINIT fnBufferedPaintUnInit;
   FNISCOMPOSITIONACTIVE fnIsCompositionActive;
   FNENDBUFFEREDANIMATION fnEndBufferedAnimation;
   FNENDBUFFEREDPAINT fnEndBufferedPaint;
   FNGETBUFFEREDPAINTBITS fnGetBufferedPaintBits;
   FNGETBUFFEREDPAINTDC fnGetBufferedPaintDC;
   FNGETBUFFEREDPAINTTARGETDC fnGetBufferedPaintTargetDC;
   FNGETBUFFEREDPAINTTARGETRECT fnGetBufferedPaintTargetRect;

   CVistaBufferedPaint()
   {
      static HINSTANCE hUxInstance = ::LoadLibrary(_T("uxtheme.dll"));
      if( hUxInstance != NULL ) {
         fnBeginBufferedAnimation = (FNBEGINBUFFEREDANIMATION) ::GetProcAddress(hUxInstance, "BeginBufferedAnimation");
         fnBeginBufferedPaint = (FNBEGINBUFFEREDPAINT) ::GetProcAddress(hUxInstance, "BeginBufferedPaint");
         fnBufferedPaintClear = (FNBUFFEREDPAINTCLEAR) ::GetProcAddress(hUxInstance, "BufferedPaintClear");
         fnBufferedPaintInit = (FNBUFFEREDPAINTINIT) ::GetProcAddress(hUxInstance, "BufferedPaintInit");
         fnBufferedPaintRenderAnimation = (FNBUFFEREDPAINTRENDERANIMATION) ::GetProcAddress(hUxInstance, "BufferedPaintRenderAnimation");
         fnBufferedPaintSetAlpha = (FNBUFFEREDPAINTSETALPHA) ::GetProcAddress(hUxInstance, "BufferedPaintSetAlpha");
         fnBufferedPaintStopAllAnimations = (FNBUFFEREDPAINTSTOPALLANIMATIONS) ::GetProcAddress(hUxInstance, "BufferedPaintStopAllAnimations");
         fnBufferedPaintUnInit = (FNBUFFEREDPAINTUNINIT) ::GetProcAddress(hUxInstance, "BufferedPaintUnInit");
         fnIsCompositionActive = (FNISCOMPOSITIONACTIVE) ::GetProcAddress(hUxInstance, "IsCompositionActive");
         fnEndBufferedAnimation = (FNENDBUFFEREDANIMATION) ::GetProcAddress(hUxInstance, "EndBufferedAnimation");
         fnEndBufferedPaint = (FNENDBUFFEREDPAINT) ::GetProcAddress(hUxInstance, "EndBufferedPaint");
         fnGetBufferedPaintBits = (FNGETBUFFEREDPAINTBITS) ::GetProcAddress(hUxInstance, "GetBufferedPaintBits");
         fnGetBufferedPaintDC = (FNGETBUFFEREDPAINTDC) ::GetProcAddress(hUxInstance, "GetBufferedPaintDC");
         fnGetBufferedPaintTargetDC = (FNGETBUFFEREDPAINTTARGETDC) ::GetProcAddress(hUxInstance, "GetBufferedPaintTargetDC");
         fnGetBufferedPaintTargetRect = (FNGETBUFFEREDPAINTTARGETRECT) ::GetProcAddress(hUxInstance, "GetBufferedPaintTargetRect");
      }
      else {
         fnBeginBufferedAnimation = NULL;
         fnBeginBufferedPaint = NULL;
         fnBufferedPaintClear = NULL;
         fnBufferedPaintInit = NULL;
         fnBufferedPaintRenderAnimation = NULL;
         fnBufferedPaintSetAlpha = NULL;
         fnBufferedPaintStopAllAnimations = NULL;
         fnBufferedPaintUnInit = NULL;
         fnIsCompositionActive = NULL;
         fnEndBufferedAnimation = NULL;
         fnEndBufferedPaint = NULL;
         fnGetBufferedPaintBits = NULL;
         fnGetBufferedPaintDC = NULL;
         fnGetBufferedPaintTargetDC = NULL;
         fnGetBufferedPaintTargetRect = NULL;
      }
   }

   BOOL IsBufferedPaintAvailable() const
   {
      return (fnBeginBufferedAnimation != NULL);
   }

   HANIMATIONBUFFER BeginBufferedAnimation(HWND hwnd, HDC hdcTarget, CONST RECT *rcTarget, BP_BUFFERFORMAT dwFormat, BP_PAINTPARAMS *pPaintParams, BP_ANIMATIONPARAMS *pAnimationParams, HDC *phdcFrom, HDC *phdcTo)
   {
      if( fnBeginBufferedAnimation == NULL ) return NULL;
      return fnBeginBufferedAnimation(hwnd, hdcTarget, rcTarget, dwFormat, pPaintParams, pAnimationParams, phdcFrom, phdcTo);
   }

   HPAINTBUFFER BeginBufferedPaint(HDC hdcTarget, CONST RECT *prcTarget, BP_BUFFERFORMAT dwFormat, BP_PAINTPARAMS *pPaintParams, HDC *phdc)
   {
      if( fnBeginBufferedPaint == NULL ) return NULL;
      return fnBeginBufferedPaint(hdcTarget, prcTarget, dwFormat, pPaintParams, phdc);
   }

   HRESULT BufferedPaintClear(HPAINTBUFFER hBufferedPaint, CONST RECT *prc)
   {
      if( fnBufferedPaintClear == NULL ) return E_NOTIMPL;
      return BufferedPaintClear(hBufferedPaint, prc);
   }

   HRESULT BufferedPaintInit()
   {
      if( fnBufferedPaintInit == NULL ) return E_NOTIMPL;
      return fnBufferedPaintInit();
   }

   BOOL BufferedPaintRenderAnimation(HWND hwnd, HDC hdcTarget)
   {
      if( fnBufferedPaintRenderAnimation == NULL ) return FALSE;
      return fnBufferedPaintRenderAnimation(hwnd, hdcTarget);
   }  

   HRESULT BufferedPaintSetAlpha(HPAINTBUFFER hBufferedPaint, CONST RECT *prc, BYTE alpha)
   {
      if( fnBufferedPaintSetAlpha == NULL ) return E_NOTIMPL;
      return fnBufferedPaintSetAlpha(hBufferedPaint, prc, alpha);
   }

   HRESULT BufferedPaintStopAllAnimations(HWND hwnd)
   {
      if( fnBufferedPaintStopAllAnimations == NULL ) return E_NOTIMPL;
      return fnBufferedPaintStopAllAnimations(hwnd);
   }

   HRESULT BufferedPaintUnInit()
   {
      if( fnBufferedPaintUnInit == NULL ) return E_NOTIMPL;
      return fnBufferedPaintUnInit();
   }

   HRESULT EndBufferedAnimation(HANIMATIONBUFFER hbpAnimation, BOOL fUpdateTarget)
   {
      if( fnEndBufferedAnimation == NULL ) return E_NOTIMPL;
      return fnEndBufferedAnimation(hbpAnimation, fUpdateTarget);
   }

   HRESULT EndBufferedPaint(HPAINTBUFFER hBufferedPaint, BOOL fUpdateTarget)
   {
      if( fnEndBufferedPaint == NULL ) return E_NOTIMPL;
      return fnEndBufferedPaint(hBufferedPaint, fUpdateTarget);
   }

   HRESULT GetBufferedPaintBits(HPAINTBUFFER hBufferedPaint, RGBQUAD **ppbBuffer, int *pcxRow)
   {
      if( fnGetBufferedPaintBits == NULL ) return E_NOTIMPL;
      return fnGetBufferedPaintBits(hBufferedPaint, ppbBuffer, pcxRow);
   }

   HDC GetBufferedPaintDC(HPAINTBUFFER hBufferedPaint)
   {
      if( fnGetBufferedPaintDC == NULL ) return NULL;
      return fnGetBufferedPaintDC(hBufferedPaint);
   }

   HDC GetBufferedPaintTargetDC(HPAINTBUFFER hBufferedPaint)
   {
      if( fnGetBufferedPaintTargetDC == NULL ) return NULL;
      return fnGetBufferedPaintTargetDC(hBufferedPaint);
   }

   HRESULT GetBufferedPaintTargetRect(HPAINTBUFFER hBufferedPaint, RECT *prc)
   {
      if( fnGetBufferedPaintTargetRect == NULL ) return E_NOTIMPL;
      return fnGetBufferedPaintTargetRect(hBufferedPaint, prc);
   }

   BOOL IsCompositionActive()
   {
      if( fnIsCompositionActive == NULL ) return FALSE;
      return fnIsCompositionActive();
   }
};


#endif // !defined(AFX_VISTALAYER_H__20070321_13AC_DF67_33D0_0080AD509054__INCLUDED_)

