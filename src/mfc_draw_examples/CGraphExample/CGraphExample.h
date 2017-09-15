// CGraphExample.h : main header file for the CGRAPHEXAMPLE application
//

#if !defined(AFX_CGRAPHEXAMPLE_H__DE103DB9_0E6F_4480_BB39_B52154D20349__INCLUDED_)
#define AFX_CGRAPHEXAMPLE_H__DE103DB9_0E6F_4480_BB39_B52154D20349__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCGraphExampleApp:
// See CGraphExample.cpp for the implementation of this class
//

class CCGraphExampleApp : public CWinApp
{
public:
    CCGraphExampleApp();

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CCGraphExampleApp)
public:
    virtual BOOL InitInstance();
    //}}AFX_VIRTUAL

// Implementation
    //{{AFX_MSG(CCGraphExampleApp)
    afx_msg void OnAppAbout();
    // NOTE - the ClassWizard will add and remove member functions here.
    //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CGRAPHEXAMPLE_H__DE103DB9_0E6F_4480_BB39_B52154D20349__INCLUDED_)
