// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(VFC_STDAFX_H__A739FE83_AB9B_4337_ADAB_1DDB14254EF9__INCLUDED_)
#define VFC_STDAFX_H__A739FE83_AB9B_4337_ADAB_1DDB14254EF9__INCLUDED_

#if _MSC_VER >= 1000
    #pragma once
#endif // _MSC_VER >= 1000

// Change these values to use different versions
#define WINVER      0x0500
#if !defined(_WIN32_WINNT)
    #define _WIN32_WINNT    0x0501
#endif
#define _WIN32_IE   0x0501
#define _RICHEDIT_VER   0x0200

#include <atlbase.h>
#include <atlapp.h>

extern CAppModule _Module;

#include <atlwin.h>

#include <atlframe.h>
#include <atlctrls.h>
#include <atldlgs.h>
#include <tracetool/tracetool.h>

#pragma warning (disable : 4100)


#if defined(_MSC_VER) && (_MSC_VER >= 1400)
    #if defined _M_IX86
        #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
    #elif defined _M_IA64
        #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
    #elif defined _M_X64
        #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
    #else
        #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
    #endif
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// VisualFC AppWizard will insert additional declarations immediately before the previous line.

#endif // !defined(VFC_STDAFX_H__A739FE83_AB9B_4337_ADAB_1DDB14254EF9__INCLUDED_)
