
#ifndef __STDAFX_H__
#define __STDAFX_H__

#if _MSC_VER >= 1000
    #pragma once
#endif // _MSC_VER >= 1000

// Change these values to use different versions
#define WINVER        0x0500
// #define _WIN32_WINNT  0x0501
#define _WIN32_IE     0x0501
#define _RICHEDIT_VER 0x0200


#include <atlstr.h>         // CString
#include <atltypes.h>       // CSize, CPoint, CRect
#include <atlimage.h>
#define _WTL_NO_CSTRING
#define _WTL_NO_WTYPES

#include <atlbase.h>
#include <atlapp.h>



extern CAppModule _Module;

#include <atlwin.h>
#include <atlframe.h>
#include <atlctrls.h>
#include <atldlgs.h>
#include <atlddx.h>


#include <tracetool/tracetool.h>

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


#endif // __STDAFX_H__
