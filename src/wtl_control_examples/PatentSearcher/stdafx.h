// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//
// author: luckey_sun
// email : sunlaibing88@gmail.com
// date  : 2011.12.31

#pragma once

// Change these values to use different versions
#define WINVER      0x0500
#define _WIN32_WINNT    0x0501
#define _WIN32_IE   0x0501
#define _RICHEDIT_VER   0x0200

#include "winsock2.h"

#include <atlbase.h>
// 修正CString 定义不明确的错误
#include <atlstr.h>
#define _WTL_NO_CSTRING
#include <atlapp.h>

extern CAppModule _Module;

//显示浏览器
#include <atlcom.h>
#include <atlhost.h>
#include <atlwin.h>
#include <atlctl.h>

//Tiff
#include "tiffio.h"

#include <atltime.h>

#include <atlcrack.h>
#include <atlframe.h>
#include <atlmisc.h>
#include <atldlgs.h>
#include <atlsplit.h>           //WTL的分隔窗口类
#include <atlctrls.h>
#include <atlctrlx.h>
#include <atlctrlw.h>
#include <atlddx.h>

#define _WTL_NO_CSTRING

/************************************************************************/
/* 添加的全部变量*/
/************************************************************************/
extern CString global_Search_str;
extern CString global_CheckBox_str;


const int INFOLISTVIEW = 1;
const int DOWNLOADLISTVIEW = 2;
const int SEARCHLISTVIEW = 4;

#define WM_SEARCH_LOADSELECT         100001
#define WM_SEARCH_RELOADSELECT       100002
#define WM_SEARCH_FIRSTPAGE          100003
#define WM_SEARCH_PREVPAGE           100004
#define WM_SEARCH_NEXTPAGE           100005
#define WM_SEARCH_LASTPAGE           100006
#define WM_SEARCH_GO                 100007

#pragma warning (disable:4146)
#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace \
    rename("EOF","adoEOF")rename("BOF","adoBOF")
//#include <boost/thread.hpp>

//
// #include <shlobj.h>
// #include <shlguid.h>
//
// #include <vector>
// #include <map>
#if defined _M_IX86
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
