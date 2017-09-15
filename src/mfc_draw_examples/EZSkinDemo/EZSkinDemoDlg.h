// EZSkinDemoDlg.h : header file
//

#if !defined(AFX_EZSKINDEMODLG_H__23934AEF_A4B7_4C2A_AB0D_76246961A5F6__INCLUDED_)
#define AFX_EZSKINDEMODLG_H__23934AEF_A4B7_4C2A_AB0D_76246961A5F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CEZSkinDemoDlg dialog
#include "EZDialog.h"

class CEZSkinDemoDlg : public CEZDialog
{
// Construction
public:
	CEZSkinDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CEZSkinDemoDlg)
	enum { IDD = IDD_EZSKINDEMO_DIALOG };
	CListBox	m_wndListBox;
	CString	m_strCurSkin;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEZSkinDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	CEZSkinManager* GetSkinManager();
	void LoadListBox();
	
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CEZSkinDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeList1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EZSKINDEMODLG_H__23934AEF_A4B7_4C2A_AB0D_76246961A5F6__INCLUDED_)
