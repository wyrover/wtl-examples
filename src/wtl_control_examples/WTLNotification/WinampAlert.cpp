// WinampAlert.cpp : implementation file
//

#include "stdafx.h"
#include "WinampAlert.h"

// CWinampAlert dialog
CWinampAlert::CWinampAlert(CWindow* pParent /*=NULL*/)
    : CAlertDialog(CWinampAlert::IDD, pParent)
{
}

CWinampAlert::~CWinampAlert()
{
}

// CWinampAlert message handlers
BOOL CWinampAlert::OnInitDialog(CWindow wndFocus, LPARAM lInitParam)
{
    CAlertDialog::OnInitDialog(wndFocus, lInitParam);
    m_ctrlTitle.SubclassWindow(GetDlgItem(IDC_STATIC_WINAMP_TITLE));
    m_ctrlAuthor.SubclassWindow(GetDlgItem(IDC_STATIC_WINAMP_AUTHOR));
    m_ctrlAlbum.SubclassWindow(GetDlgItem(IDC_STATIC_WINAMP_ALBUM));
    m_ctrlDesc.SubclassWindow(GetDlgItem(IDC_STATIC_WINAMP_DESC));
    m_ctrlTrackNo.SubclassWindow(GetDlgItem(IDC_STATIC_WINAMP_TRACKNO));
    // change the title font
    LOGFONT lf;
    CFontHandle f = m_ctrlTitle.GetFont();
    f.GetLogFont(&lf);
    lf.lfWeight = FW_BOLD;
    lf.lfHeight -= 1;
    m_fontTitle.CreateFontIndirect(&lf);
    m_ctrlTitle.SetFont(m_fontTitle);
    m_ctrlTitle.SetTextColor(RGB(0xF0, 0xF0, 0xF0));
    m_ctrlAuthor.SetTextColor(RGB(0xF0, 0xF0, 0xF0));
    m_ctrlAlbum.SetTextColor(RGB(0xF0, 0xF0, 0xF0));
    return TRUE;
}

LRESULT CWinampAlert::OnContentClicked(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    Hide();
    return 0;
}

void CWinampAlert::OnLButtonDown(UINT nFlags, CPoint point)
{
    CAlertDialog::OnLButtonDown(nFlags, point);
    Hide();
}
