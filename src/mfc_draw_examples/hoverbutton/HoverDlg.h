// HoverDlg.h : header file
//

#if !defined(AFX_HOVERDLG_H__D274D732_3D5E_43C3_8B62_3E70565E7277__INCLUDED_)
#define AFX_HOVERDLG_H__D274D732_3D5E_43C3_8B62_3E70565E7277__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000
#include "HoverButton.h"

/////////////////////////////////////////////////////////////////////////////
// CHoverDlg dialog

class CHoverDlg : public CDialog
{
// Construction
public:
    CHoverDlg(CWnd* pParent = NULL);    // standard constructor

// Dialog Data
    //{{AFX_DATA(CHoverDlg)
    enum { IDD = IDD_HOVER_DIALOG };
    CHoverButton    m_HoverButton;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CHoverDlg)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    HICON m_hIcon;

    // Generated message map functions
    //{{AFX_MSG(CHoverDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnHoverbutton();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOVERDLG_H__D274D732_3D5E_43C3_8B62_3E70565E7277__INCLUDED_)
