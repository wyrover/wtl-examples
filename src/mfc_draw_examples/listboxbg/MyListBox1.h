#if !defined(AFX_MYLISTBOX1_H__0EEA4E69_F748_4264_A991_CFA7AE3A5A07__INCLUDED_)
#define AFX_MYLISTBOX1_H__0EEA4E69_F748_4264_A991_CFA7AE3A5A07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyListBox1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyListBox window

class CMyListBox : public CListBox
{
// Construction
public:
	CMyListBox();

// Attributes
public:
	CBitmap m_bmp;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyListBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyListBox();
protected:
	BOOL iSelectChange;
	// Generated message map functions
protected:
	//{{AFX_MSG(CMyListBox)
	afx_msg void OnSelchange();
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	CBrush m_brHollow;
	CBitmap *m_pbmCurrent;
	
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYLISTBOX1_H__0EEA4E69_F748_4264_A991_CFA7AE3A5A07__INCLUDED_)
