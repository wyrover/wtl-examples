#ifndef __WTL_WINDOWS_TEMPLATE_WTL_COMMON_H__
#define __WTL_WINDOWS_TEMPLATE_WTL_COMMON_H__

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
#include <atltypes.h>



#endif // __WTL_WINDOWS_TEMPLATE_WTL_COMMON_H__