// CIconBtn_DemoDlg.h : header file
//

#pragma once
#include "iconbtn.h"


// CCIconBtn_DemoDlg dialog
class CCIconBtn_DemoDlg : public CDialog
{
// Construction
public:
    CCIconBtn_DemoDlg(CWnd* pParent = NULL);    // standard constructor

// Dialog Data
    enum { IDD = IDD_CICONBTN_DEMO_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


// Implementation
protected:
    HICON m_hIcon;

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
public:
    CIconBtn m_btn1;
    CIconBtn m_btn2;
    CIconBtn m_btn3;
    CIconBtn m_btn4;
    afx_msg void OnBnClickedButton5();
};
