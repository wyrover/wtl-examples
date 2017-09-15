///////////////////////////////////////////////////////////////////////////
// Options.cpp : Implementation of Class Options
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

#include "stdafx.h"
#include "TreeTest.h"
#include "Options.h"

// Options dialog

IMPLEMENT_DYNAMIC(Options, CDialog)
Options::Options(CWnd* pParent /*=NULL*/)
    : CDialog(Options::IDD, pParent)
    , m_bkground_mode(FALSE)
    , m_tiled(FALSE)
    , m_horz(FALSE)
{
}

Options::~Options()
{
}

void Options::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Radio(pDX, IDC_BK_BITMAP, m_bkground_mode);
    DDX_Check(pDX, IDC_TILED, m_tiled);
    DDX_Check(pDX, IDC_HORIZ, m_horz);
}

BEGIN_MESSAGE_MAP(Options, CDialog)
    ON_BN_CLICKED(IDC_BK_BITMAP, OnBnClickedBkBitmap)
    ON_BN_CLICKED(IDC_BK_GRADIENT, OnBnClickedBkGradient)
    ON_BN_CLICKED(IDC_BK_NORMAL, OnBnClickedBkNormal)
END_MESSAGE_MAP()


// Options message handlers

BOOL Options::OnInitDialog()
{
    CDialog::OnInitDialog();
    GetDlgItem(IDC_TILED)->EnableWindow(m_bkground_mode == 0);
    GetDlgItem(IDC_HORIZ)->EnableWindow(m_bkground_mode == 1);
    UpdateData(FALSE);   // initialize
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}


void Options::OnOK()
{
    UpdateData(TRUE);   // retrieve
    CDialog::OnOK();
}


void Options::OnBnClickedBkBitmap()
{
    GetDlgItem(IDC_TILED)->EnableWindow(TRUE);
    GetDlgItem(IDC_HORIZ)->EnableWindow(FALSE);
}

void Options::OnBnClickedBkGradient()
{
    GetDlgItem(IDC_TILED)->EnableWindow(FALSE);
    GetDlgItem(IDC_HORIZ)->EnableWindow(TRUE);
    // TODO: Add your control notification handler code here
}

void Options::OnBnClickedBkNormal()
{
    GetDlgItem(IDC_TILED)->EnableWindow(FALSE);
    GetDlgItem(IDC_HORIZ)->EnableWindow(FALSE);
}
