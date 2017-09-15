// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A85CB0C1_42AE_4CA3_B24D_6924DFD3BF43__INCLUDED_)
#define AFX_STDAFX_H__A85CB0C1_42AE_4CA3_B24D_6924DFD3BF43__INCLUDED_

#define WINVER            0x0500
#define _WIN32_WINNT      0x0501
#define _WIN32_IE         0x0600
#define _RICHEDIT_VER     0x0200
#define _CRT_SECURE_NO_WARNINGS

#include <atlbase.h>
#include <atlapp.h>

extern WTL::CAppModule _Module;

#include <atlwin.h>
#include <atlmisc.h>
#include <atlctrls.h>
#include <atltheme.h>

#include <shlwapi.h>

#include "ImageHelpers.h"

#include "VistaLayer.h"
#include "FadeStateButton.h"

#include "Collect.h"



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A85CB0C1_42AE_4CA3_B24D_6924DFD3BF43__INCLUDED_)
