// CIconListBox_DemoDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "IconListBox.h"


// CCIconListBox_DemoDlg dialog
class CCIconListBox_DemoDlg : public CDialog
{
// Construction
public:
    CCIconListBox_DemoDlg(CWnd* pParent = NULL);    // standard constructor

// Dialog Data
    enum { IDD = IDD_CICONLISTBOX_DEMO_DIALOG };

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
    //CListBox m_listbox;
    CIconListBox m_listbox;
    afx_msg void OnBnClickedButton3();
};
