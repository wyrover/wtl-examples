#if !defined(AFX_PAGEMISCELLANEOUS_H__40959565_8340_4C7A_AF47_CF72CB5EF25D__INCLUDED_)
#define AFX_PAGEMISCELLANEOUS_H__40959565_8340_4C7A_AF47_CF72CB5EF25D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageMiscellaneous.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageMiscellaneous dialog

class CPageMiscellaneous : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageMiscellaneous)

// Construction
public:
	CPageMiscellaneous();
	~CPageMiscellaneous();

// Dialog Data
	//{{AFX_DATA(CPageMiscellaneous)
	enum { IDD = IDD_PAGE_MISC };
	BOOL	m_enable_ctrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageMiscellaneous)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL m_bOrgSizes;
	CRect m_rcOrg;
	CRect m_rcSmall;
	// Generated message map functions
	//{{AFX_MSG(CPageMiscellaneous)
	virtual BOOL OnInitDialog();
	afx_msg void OnEnableControl();
	afx_msg void OnToggleSizes();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEMISCELLANEOUS_H__40959565_8340_4C7A_AF47_CF72CB5EF25D__INCLUDED_)
