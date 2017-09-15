// Hover.h : main header file for the HOVER application
//

#if !defined(AFX_HOVER_H__316252EB_A435_4A4F_BE98_524DFB50066F__INCLUDED_)
#define AFX_HOVER_H__316252EB_A435_4A4F_BE98_524DFB50066F__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CHoverApp:
// See Hover.cpp for the implementation of this class
//

class CHoverApp : public CWinApp
{
public:
    CHoverApp();

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CHoverApp)
public:
    virtual BOOL InitInstance();
    //}}AFX_VIRTUAL

// Implementation

    //{{AFX_MSG(CHoverApp)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOVER_H__316252EB_A435_4A4F_BE98_524DFB50066F__INCLUDED_)
