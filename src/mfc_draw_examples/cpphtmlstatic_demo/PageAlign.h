#if !defined(AFX_PAGEALIGN_H__FCAF3297_5460_44D4_A70A_2E401FB38D36__INCLUDED_)
#define AFX_PAGEALIGN_H__FCAF3297_5460_44D4_A70A_2E401FB38D36__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageAlign.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageAlign dialog

class CPageAlign : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageAlign)

// Construction
public:
	CPageAlign();
	~CPageAlign();

// Dialog Data
	//{{AFX_DATA(CPageAlign)
	enum { IDD = IDD_PAGE_ALIGN };
	int		m_horz_align;
	int		m_vert_align;
	BOOL	m_word_wrap;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageAlign)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageAlign)
	afx_msg void OnChangeWordWrapping();
	afx_msg void OnChangeAlign();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEALIGN_H__FCAF3297_5460_44D4_A70A_2E401FB38D36__INCLUDED_)
