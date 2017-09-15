// DownloadFileDlg.cpp: implementation of the CDownloadFileDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "kibbles.h"
#include "DownloadFileDlg.h"
#include "MyDialogs.h"

//////////////////////////////////////////////////////////////////////
// Construction

CDownloadFileDlg::CDownloadFileDlg()
{
}


//////////////////////////////////////////////////////////////////////
// Message handlers

BOOL CDownloadFileDlg::OnInitDialog(HWND hwndFocus, LPARAM lParam)
{
    DoDataExchange();
    CenterWindow();
    return TRUE;
}


//////////////////////////////////////////////////////////////////////
// Command handlers

void CDownloadFileDlg::OnBrowse(UINT uCode, int nID, HWND hwndCtrl)
{
    CMyFileDialog fd(true);

    if (IDOK == fd.DoModal(*this))
        SetDlgItemText(IDC_LOCAL_FILENAME, fd.m_szFileName);
}

void CDownloadFileDlg::OnOK(UINT uCode, int nID, HWND hwndCtrl)
{
    if (!DoDataExchange(true))
        return;

    EndDialog(nID);
}

void CDownloadFileDlg::OnCancel(UINT uCode, int nID, HWND hwndCtrl)
{
    EndDialog(nID);
}
