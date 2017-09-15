// CPPHtmlStatic_demoDlg.h : header file
//

#if !defined(AFX_CPPHTMLSTATIC_DEMODLG_H__90C8EB1F_9D65_41D2_AA46_14FC470FAD3A__INCLUDED_)
#define AFX_CPPHTMLSTATIC_DEMODLG_H__90C8EB1F_9D65_41D2_AA46_14FC470FAD3A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PPHtmlStatic.h"
#include "ColourPicker.h"

#include "PageColors.h"
#include "PageBorder.h"
#include "PageAlign.h"
#include "PageMiscellaneous.h"
#include "PageImages.h"
#include "PageStyles.h"

/////////////////////////////////////////////////////////////////////////////
// CPPHtmlStatic_demoDlg dialog

class CPPHtmlStatic_demoDlg : public CDialog
{
// Construction
public:
	CPropertySheet m_sheet;
	CPageColors m_page_colors;
	CPageBorder m_page_border;
	CPageAlign m_page_align;
	CPageImages m_page_images;
	CPageMiscellaneous m_page_misc;
	CPageStyles m_page_styles;
	CPPHtmlStatic_demoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPPHtmlStatic_demoDlg)
	enum { IDD = IDD_CPPHTMLSTATIC_DEMO_DIALOG };
	CPPHtmlStatic	m_info;
	CColourPicker	m_mask_color;
	CButton	m_mask_ctrl;
	CEdit	m_comments_ctrl;
	CStatic	m_url_label;
	CPPHtmlStatic	m_static;
	CStatic	m_link_label;
	CStatic	m_id_label;
	CStatic	m_framerate_label;
	CEdit	m_url_ctrl;
	CEdit	m_link_ctrl;
	CEdit	m_framerate_ctrl;
	CComboBox	m_idres_ctrl;
	int		m_type_static;
	CString	m_comments;
	BOOL	m_mask;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPPHtmlStatic_demoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	enum {
		TYPE_ICON = 0,
		TYPE_BITMAP,
		TYPE_IMAGELIST,
		TYPE_ANIMATION,
		TYPE_HYPERLINK,
		TYPE_TEXT,
		TYPE_CUSTOMTEXT
		};
	HICON m_hIcon;
	COLORREF m_crMaskColor;

	void SetInfoText(CString str);

	// Generated message map functions
	//{{AFX_MSG(CPPHtmlStatic_demoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChangeTypeStatic();
	afx_msg void OnApplyBtn();
	//}}AFX_MSG
	afx_msg LONG OnChangeMaskColor(UINT lParam = 0, LONG wParam = 0);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CPPHTMLSTATIC_DEMODLG_H__90C8EB1F_9D65_41D2_AA46_14FC470FAD3A__INCLUDED_)
