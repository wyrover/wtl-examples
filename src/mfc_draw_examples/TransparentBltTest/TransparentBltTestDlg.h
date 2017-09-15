// TransparentBltTestDlg.h : header file
//

#if !defined(AFX_TRANSPARENTBLTTESTDLG_H__E385FF5F_365C_4F48_8E4F_EE9A30F68A3D__INCLUDED_)
#define AFX_TRANSPARENTBLTTESTDLG_H__E385FF5F_365C_4F48_8E4F_EE9A30F68A3D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTransparentBltTestDlg dialog

class CTransparentBltTestDlg : public CDialog
{
// Construction
public:
	CTransparentBltTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTransparentBltTestDlg)
	enum { IDD = IDD_TRANSPARENTBLTTEST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransparentBltTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CBitmap m_bmpBackground;
	CBitmap m_bmpFootball;
	
	// Generated message map functions
	//{{AFX_MSG(CTransparentBltTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSPARENTBLTTESTDLG_H__E385FF5F_365C_4F48_8E4F_EE9A30F68A3D__INCLUDED_)
