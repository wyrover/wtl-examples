// FirefoxAlert.cpp : implementation file
//

#include "stdafx.h"
#include "FirefoxAlert.h"

// CFirefoxAlert dialog
CFirefoxAlert::CFirefoxAlert(CWindow* pParent /*=NULL*/)
    : CAlertDialog(CFirefoxAlert::IDD, pParent)
{
}

CFirefoxAlert::~CFirefoxAlert()
{
}

// CFirefoxAlert message handlers
BOOL CFirefoxAlert::OnInitDialog(CWindow wndFocus, LPARAM lInitParam)
{
    CAlertDialog::OnInitDialog(wndFocus, lInitParam);
    m_ctrlTitle.SubclassWindow(GetDlgItem(IDC_STATIC_TITLE));
    m_ctrlContent.SubclassWindow(GetDlgItem(IDC_STATIC_CONTENT));
    m_ctrlImage.SubclassWindow(GetDlgItem(IDC_STATIC_IMAGE));
    // change the title font
    LOGFONT lf;
    CFontHandle f = m_ctrlTitle.GetFont();
    f.GetLogFont(&lf);
    lf.lfWeight = FW_BOLD;
    m_fontTitle.CreateFontIndirect(&lf);
    m_ctrlTitle.SetFont(m_fontTitle);
    m_ctrlContent.SetUnderline(true, true);
    m_ctrlContent.SetColors(RGB(0, 0, 255), RGB(0, 0, 255));
    m_ctrlImage.SetBitmap(IDB_BITMAP_DOWNLOAD);
    m_ctrlImage.SetTransparentColor(RGB(236, 233, 216));
    return TRUE;
}

LRESULT CFirefoxAlert::OnContentClicked(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    Hide();
    return 0;
}
