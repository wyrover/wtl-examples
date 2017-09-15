// mylistboxDlg.h : header file
//

#if !defined(AFX_MYLISTBOXDLG_H__07F2E0EB_DC5B_4216_B13C_C636A0635980__INCLUDED_)
#define AFX_MYLISTBOXDLG_H__07F2E0EB_DC5B_4216_B13C_C636A0635980__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMylistboxDlg dialog
#include "MyListBox1.h"

class CMylistboxDlg : public CDialog
{
// Construction
public:
	CMylistboxDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMylistboxDlg)
	enum { IDD = IDD_MYLISTBOX_DIALOG };
	CString	m_item;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMylistboxDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

public:
	HBITMAP GetSizeBITMAP(HBITMAP hBitmap, int w, int h);
	RECT	size1, size2, size3;	

protected:
	HICON m_hIcon;
	CMyListBox	m_listbox;
	CBitmap bmp;
	HBITMAP hbmp;
	HBITMAP hbmp2;
	int iStatus;
	void Refresh();
	int iSelect;
	// Generated message map functions
	//{{AFX_MSG(CMylistboxDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYLISTBOXDLG_H__07F2E0EB_DC5B_4216_B13C_C636A0635980__INCLUDED_)
