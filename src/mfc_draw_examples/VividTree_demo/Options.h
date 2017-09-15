///////////////////////////////////////////////////////////////////////////
// Options.h : Definition of Class Options
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
#include "afxwin.h"


// Options dialog

class Options : public CDialog
{
    DECLARE_DYNAMIC(Options)

public:
    Options(CWnd* pParent = NULL);   // standard constructor
    virtual ~Options();

// Dialog Data
    enum { IDD = IDD_OPTIONS };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
protected:
    virtual void OnOK();
public:
    BOOL m_bkground_mode;
    BOOL m_tiled;
    BOOL m_horz;
    afx_msg void OnBnClickedBkBitmap();
    afx_msg void OnBnClickedBkGradient();
    afx_msg void OnBnClickedBkNormal();
};
