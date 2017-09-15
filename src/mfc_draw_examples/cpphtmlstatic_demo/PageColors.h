#if !defined(AFX_PAGECOLORS_H__108569B3_D6A1_4DDD_AB3E_C0BB6A18F74C__INCLUDED_)
#define AFX_PAGECOLORS_H__108569B3_D6A1_4DDD_AB3E_C0BB6A18F74C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageColors.h : header file
//

#include "ColourPicker.h"

/////////////////////////////////////////////////////////////////////////////
// CPageColors dialog

class CPageColors : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageColors)

// Construction
public:
	CPageColors();
	~CPageColors();

// Dialog Data
	//{{AFX_DATA(CPageColors)
	enum { IDD = IDD_PAGE_COLORS };
	CColourPicker	m_text_color;
	CColourPicker	m_end_color;
	CColourPicker	m_mid_color;
	CColourPicker	m_start_color;
	BYTE	m_granularity;
	int		m_effect_bk;
	int		m_theme_bk_color;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageColors)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageColors)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeThemeBkColor();
	afx_msg void OnChangeEffectBk();
	//}}AFX_MSG
	afx_msg LRESULT OnChangeBkColor(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGECOLORS_H__108569B3_D6A1_4DDD_AB3E_C0BB6A18F74C__INCLUDED_)
