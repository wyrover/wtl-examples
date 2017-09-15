#if !defined(AFX_PAGEIMAGES_H__C062F1FE_DBCB_4375_81AB_B183247A6599__INCLUDED_)
#define AFX_PAGEIMAGES_H__C062F1FE_DBCB_4375_81AB_B183247A6599__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageImages.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageImages dialog

class CPageImages : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageImages)

// Construction
public:
	CPageImages();
	~CPageImages();

// Dialog Data
	//{{AFX_DATA(CPageImages)
	enum { IDD = IDD_PAGE_IMAGES };
	int		m_width;
	int		m_height;
	int		m_width_per;
	int		m_height_per;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageImages)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageImages)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeWidth();
	afx_msg void OnChangeHeight();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEIMAGES_H__C062F1FE_DBCB_4375_81AB_B183247A6599__INCLUDED_)
