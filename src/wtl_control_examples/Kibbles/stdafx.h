// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__78EAF906_217A_4DDD_AAE5_CAF5F9135BB0__INCLUDED_)
#define AFX_STDAFX_H__78EAF906_217A_4DDD_AAE5_CAF5F9135BB0__INCLUDED_

// Change these values to use different versions
#define WIN32_LEAN_AND_MEAN
#define WINVER          0x0501          // Enable XP features
#define _WIN32_WINNT    0x0501          // Enable XP features
#define _WIN32_IE       0x0501          // Target IE 5.01+

#define _ATL_APARTMENT_THREADED
#define _WTL_USE_CSTRING
#define _ATL_USE_CSTRING_FLOAT  // need this so CString::Format() calls _vstprintf() which understands the %I64 prefix
#define _ATL_NO_OPENGL

// ATL/WTL
#include <atlbase.h>
#include <atlapp.h>
extern CAppModule _Module;
#include <atlwin.h>

#include <atlframe.h>
#include <atlcrack.h>
#include <atlmisc.h>
#include <atlddx.h>
#include <atlctrls.h>
#include <atldlgs.h>
#include <atltheme.h>

// Win32
#include <bits.h>
#include <wininet.h>

// STL
#include <map>

// CRT
#include <math.h>

#pragma comment(lib, "Bits.lib")
#pragma comment(lib, "Wininet.lib")

#pragma warning (disable : 4100)

// Global stuff
LPCTSTR JobStateToString(const BG_JOB_STATE state);

const COLORREF g_crDownloadedPartPenDefault = RGB(255, 255, 0),
               g_crRemainingPartPenDefault = RGB(0, 0, 0),
               g_crRemainingPartFillDefault = RGB(128, 128, 128),
               g_crTextDefault = RGB(0, 0, 0),
               g_crBkgndDefault = RGB(255, 255, 255);

// Utility classes::
// Saves/restores the state of a DC
class CSaveDC
{
public:
    CSaveDC() : m_hdc(NULL), m_nSavePos(0)
    { }

    CSaveDC(HDC hdc) : m_hdc(hdc)
    {
        ATLASSERT(NULL != hdc);
        m_nSavePos = SaveDC(hdc);
    }

    ~CSaveDC()
    {
        if (NULL != m_hdc && 0 != m_nSavePos)
            RestoreDC(m_hdc, m_nSavePos);
    }

    void Save(HDC hdc)
    {
        ATLASSERT(NULL != hdc);

        if (NULL != m_hdc && 0 != m_nSavePos)
            RestoreDC(m_hdc, m_nSavePos);

        m_hdc = hdc;
        m_nSavePos = SaveDC(hdc);
    }

protected:
    HDC m_hdc;
    int m_nSavePos;
};

// URL_COMPONENTS wrapper that manages the buffers
struct CUrlComponents : public URL_COMPONENTS {
    CUrlComponents();
    ~CUrlComponents();

    TCHAR szScheme    [INTERNET_MAX_URL_LENGTH];
    TCHAR szHostName  [INTERNET_MAX_URL_LENGTH];
    TCHAR szUserName  [INTERNET_MAX_URL_LENGTH];
    TCHAR szPassword  [INTERNET_MAX_URL_LENGTH];
    TCHAR szUrlPath   [INTERNET_MAX_URL_LENGTH];
    TCHAR szExtraInfo [INTERNET_MAX_URL_LENGTH];
};

// Get an error description
class CErrorDesc
{
public:
    CErrorDesc(DWORD dw = GetLastError(),
               LANGID langid = MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT)) :
        m_dwError(dw), m_langid(langid)
    {
        CommonConstruct();
    }

    CErrorDesc(HRESULT hr,
               LANGID langid = MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT)) :
        m_dwError(hr), m_langid(langid)
    {
        CommonConstruct();
    }

    operator LPCTSTR()
    {
        return m_sDesc;
    }

protected:
    void CommonConstruct();

    DWORD   m_dwError;
    LANGID  m_langid;
    CString m_sDesc;
};

#define _E(hr) ((LPCTSTR) CErrorDesc(hr))   // use with an HRESULT
#define _E2() ((LPCTSTR) CErrorDesc())      // uses value from GetLastError()

// Convenience macros
#define countof(x) (sizeof(x)/sizeof((x)[0]))   // # elements in a statically-allocated array

#if _ATL_VER < 0x0700
    #undef BEGIN_MSG_MAP
    #define BEGIN_MSG_MAP(x) BEGIN_MSG_MAP_EX(x)
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__78EAF906_217A_4DDD_AAE5_CAF5F9135BB0__INCLUDED_)
