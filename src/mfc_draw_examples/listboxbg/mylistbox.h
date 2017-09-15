// mylistbox.h : main header file for the MYLISTBOX application
//

#if !defined(AFX_MYLISTBOX_H__5177D2E6_8BD8_4408_AF50_FA0D90421DE9__INCLUDED_)
#define AFX_MYLISTBOX_H__5177D2E6_8BD8_4408_AF50_FA0D90421DE9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMylistboxApp:
// See mylistbox.cpp for the implementation of this class
//

class CMylistboxApp : public CWinApp
{
public:
	CMylistboxApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMylistboxApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMylistboxApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYLISTBOX_H__5177D2E6_8BD8_4408_AF50_FA0D90421DE9__INCLUDED_)
