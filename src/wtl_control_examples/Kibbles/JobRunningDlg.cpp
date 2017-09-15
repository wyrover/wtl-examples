// JobRunningDlg.cpp: implementation of the CJobRunningDlg class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Kibbles.h"
#include "JobRunningDlg.h"

//////////////////////////////////////////////////////////////////////
// Construction

CJobRunningDlg::CJobRunningDlg() : m_nChoice(0)
{
}


//////////////////////////////////////////////////////////////////////
// Message handlers

BOOL CJobRunningDlg::OnInitDialog(HWND hwndFocus, LPARAM lParam)
{
    DoDataExchange();
    CenterWindow();
    return TRUE;
}

void CJobRunningDlg::OnOK(UINT uCode, int nID, HWND hwndCtrl)
{
    if (!DoDataExchange(true))
        return;

    EndDialog(IDOK);
}

void CJobRunningDlg::OnCancel(UINT uCode, int nID, HWND hwndCtrl)
{
    EndDialog(IDCANCEL);
}
