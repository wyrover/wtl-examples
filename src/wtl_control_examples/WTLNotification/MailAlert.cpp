#include "stdafx.h"
#include "MailAlert.h"

BOOL CMailAlert::OnInitDialog(CWindow wndFocus, LPARAM lInitParam)
{
    CAlertDialog::OnInitDialog(wndFocus, lInitParam);
    m_message = GetDlgItem(IDC_STATIC_MSG2);
    m_ctrlFrom.SubclassWindow(GetDlgItem(IDC_STATIC_FROM));
    m_ctrlTitle.SubclassWindow(GetDlgItem(IDC_STATIC_TITLE));
    m_ctrlIcon.SubclassWindow(GetDlgItem(IDC_STATIC_ICON));
    m_btnFlag.SubclassWindow(GetDlgItem(IDC_BUTTON_FLAG));
    m_btnDelete.SubclassWindow(GetDlgItem(IDC_BUTTON_DELETE));
    m_btnClose.SubclassWindow(GetDlgItem((IDCANCEL)));
    m_ctrlContent.SubclassWindow(GetDlgItem(IDC_STATIC_CONTENT));
    LOGFONT lf;
    CFontHandle f = m_ctrlFrom.GetFont();
    f.GetLogFont(&lf);
    lf.lfWeight = FW_BOLD;
    m_fontFrom.CreateFontIndirect(&lf);
    m_ctrlFrom.SetFont(m_fontFrom);
    m_ctrlFrom.SetWindowText(_T("Marius Bancila"));
    m_ctrlTitle.SetWindowText(_T("This is a test mail"));
    m_ctrlContent.SetWindowText(_T("This is a notification window that should apear on top of the tray window."));
    m_ctrlIcon.SetIcon(IDI_MAIL, 32, 32);
    m_ctrlIcon.SetTransparentColor(RGB(0, 0, 0));
    m_btnFlag.SetBitmap(IDB_BITMAP_FLAG);
    m_btnFlag.SetTransparentColor(RGB(192, 192, 192));
    m_btnFlag.SetHighlightColor(RGB(200, 200, 100));
    m_btnDelete.SetBitmap(IDB_BITMAP_DELETE);
    m_btnDelete.SetTransparentColor(RGB(192, 192, 192));
    m_btnDelete.SetHighlightBackground(FALSE);
    return true;
}

LRESULT CMailAlert::OnContentClicked(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    Hide();
    return 0;
}

void CMailAlert::OnInvalidate()
{
    m_ctrlIcon.InvalidateCachedBitmap();
    m_ctrlFrom.InvalidateCachedBitmap();
    m_ctrlTitle.InvalidateCachedBitmap();
    m_ctrlContent.InvalidateCachedBitmap();
    m_btnFlag.InvalidateCachedBitmap();
    m_btnDelete.InvalidateCachedBitmap();
    m_btnClose.InvalidateCachedBitmap();
}

LRESULT CMailAlert::OnButtonClicked(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    Hide();
    return 0;
}

