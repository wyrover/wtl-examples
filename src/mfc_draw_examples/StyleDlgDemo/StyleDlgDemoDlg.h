// StyleDlgDemoDlg.h : header file
//

#pragma once

#include "./src/StyleDialog.h"

#include "./src/style.h"

// CStyleDlgDemoDlg dialog
class CStyleDlgDemoDlg : public StyleDialog
{
// Construction
public:
    CStyleDlgDemoDlg(CWnd* pParent = NULL); // standard constructor

    void CreateFrame();
    void CreateButtons();



// Dialog Data
    enum { IDD = IDD_STYLEDLGDEMO_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
    HICON m_hIcon;

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()

public:
    CStatic m_cInnerFrame;
    afx_msg void OnBnClickedDialog3();
    StyleButton m_cDlg2Btn;
    StyleButton m_cDlg3Btn;
    afx_msg void OnBnClickedDialog2();
};
