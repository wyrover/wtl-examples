// MFCDlgDemo.h : main header file for the MFCDLGDEMO application
//

#if !defined(AFX_MFCDLGDEMO_H__BF2E13F1_0337_49A7_BA4C_4CB08AB647BE__INCLUDED_)
#define AFX_MFCDLGDEMO_H__BF2E13F1_0337_49A7_BA4C_4CB08AB647BE__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMFCDlgDemoApp:
// See MFCDlgDemo.cpp for the implementation of this class
//

class CMFCDlgDemoApp : public CWinApp
{
public:
    CMFCDlgDemoApp();

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CMFCDlgDemoApp)
public:
    virtual BOOL InitInstance();
    //}}AFX_VIRTUAL

// Implementation

    //{{AFX_MSG(CMFCDlgDemoApp)
    // NOTE - the ClassWizard will add and remove member functions here.
    //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCDLGDEMO_H__BF2E13F1_0337_49A7_BA4C_4CB08AB647BE__INCLUDED_)
