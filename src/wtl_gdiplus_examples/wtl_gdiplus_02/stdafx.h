#ifndef __STDAFX_H__
#define __STDAFX_H__



// Change these values to use different versions
#define WINVER              0x0500
#define _WIN32_WINNT        0x0501
#define _WIN32_IE           0x0501
#define _RICHEDIT_VER       0x0200

#include <atlbase.h>
#include <atlapp.h>

extern CAppModule _Module;

#include <atlwin.h>

#include <atlframe.h>
#include <atlctrls.h>
#include <atldlgs.h>
#include <atlimage.h>       // CImage

#include "Gdiplus.h"
using namespace Gdiplus ;
#pragma comment (lib, "Gdiplus.lib")

#include "resource.h"

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
