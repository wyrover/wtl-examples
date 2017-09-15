///////////////////////////////////////////////////////////////////////////
// TreeTestDlg.h : Definition of Class TreeTestDlg
///////////////////////////////////////////////////////////////////////////
//
// Copyright(C) 2005 Jim Alsup  All rights reserved
//              email: ja.alsup@gmail.com
//
// License: This code is provided "as is" with no expressed or implied
//          warranty. You may use, or derive works from this file without
//          any restrictions except those listed below.
//
//        - This original header must be kept in the derived work.
//
//        - If your derived work is distributed in any form, you must
//          notify the author via the email address above and provide a
//          short description of the product and intended audience.
//
//        - You may not sell this code or a derived version of it as part of
//          a comercial code library.
//
//        - Offering the author a free licensed copy of any end product
//          using this code is not required, but does endear you with a
//          bounty of good karma.
//
///////////////////////////////////////////////////////////////////////////


#pragma once
#include "afxcmn.h"


// CTreeTestDlg dialog
class CTreeTestDlg : public CDialog
{
// Construction
public:
    CTreeTestDlg(CWnd* pParent = NULL); // standard constructor

// Dialog Data
    enum { IDD = IDD_TREETEST_DIALOG };

private:
    VividTree::BkMode m_background_mode;
    VividTree         m_tree;
    HICON             m_icon;

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
    afx_msg void OnSize(UINT nType, int cx, int cy);
    DECLARE_MESSAGE_MAP()
public:
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};
