#if !defined(AFX_PAGEBORDER_H__41974665_8995_45D9_A604_835B1DB8290C__INCLUDED_)
#define AFX_PAGEBORDER_H__41974665_8995_45D9_A604_835B1DB8290C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageBorder.h : header file
//
#include "ColourPicker.h"
/////////////////////////////////////////////////////////////////////////////
// CPageBorder dialog

class CPageBorder : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageBorder)

// Construction
public:
	CPageBorder();
	~CPageBorder();

// Dialog Data
	//{{AFX_DATA(CPageBorder)
	enum { IDD = IDD_PAGE_BORDER };
	CColourPicker	m_border_color;
	int		m_border;
	int		m_width;
	int		m_height;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageBorder)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageBorder)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeBorder();
	afx_msg void OnChangeSizes();
	//}}AFX_MSG
	afx_msg LRESULT OnChangeBorderColor(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEBORDER_H__41974665_8995_45D9_A604_835B1DB8290C__INCLUDED_)
