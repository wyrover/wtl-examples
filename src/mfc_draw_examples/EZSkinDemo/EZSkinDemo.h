// EZSkinDemo.h : main header file for the EZSKINDEMO application
//

#if !defined(AFX_EZSKINDEMO_H__CB769AD2_0AA9_4F50_8746_60CE4B3F7C6F__INCLUDED_)
#define AFX_EZSKINDEMO_H__CB769AD2_0AA9_4F50_8746_60CE4B3F7C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEZSkinDemoApp:
// See EZSkinDemo.cpp for the implementation of this class
//
#include "EZSkinManager.h"
class CEZSkinDemoApp : public CWinApp,public CEZSkinManager
{
public:
	CEZSkinDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEZSkinDemoApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEZSkinDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:

};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EZSKINDEMO_H__CB769AD2_0AA9_4F50_8746_60CE4B3F7C6F__INCLUDED_)
