// CustomListBox.h : main header file for the CUSTOMLISTBOX application
//

#if !defined(AFX_CUSTOMLISTBOX_H__37CA1077_B0A7_486B_A263_2DFF206F5AB0__INCLUDED_)
#define AFX_CUSTOMLISTBOX_H__37CA1077_B0A7_486B_A263_2DFF206F5AB0__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

// Eye candy

#define DLG_COLOR_BACKGROUND        RGB(232,255,255)

/////////////////////////////////////////////////////////////////////////////
// CCustomListBoxApp:
// See CustomListBox.cpp for the implementation of this class
//

class CCustomListBoxApp : public CWinApp
{
public:
    CCustomListBoxApp();

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CCustomListBoxApp)
public:
    virtual BOOL InitInstance();
    //}}AFX_VIRTUAL

// Implementation

    //{{AFX_MSG(CCustomListBoxApp)
    // NOTE - the ClassWizard will add and remove member functions here.
    //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMLISTBOX_H__37CA1077_B0A7_486B_A263_2DFF206F5AB0__INCLUDED_)
