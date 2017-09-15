#if !defined(AFX_PAGESTYLES_H__E0CE5AB5_835D_4826_8678_02C516FA158B__INCLUDED_)
#define AFX_PAGESTYLES_H__E0CE5AB5_835D_4826_8678_02C516FA158B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageStyles.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageStyles dialog

class CPageStyles : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageStyles)

// Construction
public:
	CPageStyles();
	~CPageStyles();

// Dialog Data
	//{{AFX_DATA(CPageStyles)
	enum { IDD = IDD_PAGE_STYLES };
	BOOL	m_border;
	BOOL	m_client_edge;
	BOOL	m_static_edge;
	BOOL	m_modal_frame;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageStyles)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageStyles)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeStyles();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGESTYLES_H__E0CE5AB5_835D_4826_8678_02C516FA158B__INCLUDED_)
