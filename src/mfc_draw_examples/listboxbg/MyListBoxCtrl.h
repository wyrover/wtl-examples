#if !defined(AFX_MYLISTBOXCTRL_H__1DA1D47C_CCA8_4963_A177_13EDEC853E80__INCLUDED_)
#define AFX_MYLISTBOXCTRL_H__1DA1D47C_CCA8_4963_A177_13EDEC853E80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyListBoxCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyListBoxCtrl window

class CMyListBoxCtrl : public CListBox
{
// Construction
public:
	CMyListBoxCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyListBoxCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyListBoxCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyListBoxCtrl)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYLISTBOXCTRL_H__1DA1D47C_CCA8_4963_A177_13EDEC853E80__INCLUDED_)
