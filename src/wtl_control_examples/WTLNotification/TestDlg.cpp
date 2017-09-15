#include "stdafx.h"
#include "TestDlg.h"

LRESULT CTestDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    CenterWindow(GetParent());
    m_message = GetDlgItem(IDC_STATIC_MSG);
    m_label.SubclassWindow(GetDlgItem(IDC_ALERT_LABEL));
    m_link.SubclassWindow(GetDlgItem(IDC_ALERT_HYPER_LINK));
    m_picture.SubclassWindow(GetDlgItem(IDC_ALERT_PICTURE));
    m_button.SubclassWindow(GetDlgItem(IDC_ALERT_BUTTON));
    m_button.SetBitmap(IDB_BITMAP_DOWNLOAD, true);
    m_button.SetHighlightColor(RGB(192, 255, 192));
    m_button_close.SubclassWindow(GetDlgItem(IDC_ALERT_BUTTON_CLOSE));
    m_button_close.SetHighlightColor(RGB(0, 255, 0));
    return 0;
}

LRESULT CTestDlg::OnOkCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    MessageBox(_T("OKボタン"), _T("メッセージ"));
    return 0;
}

LRESULT CTestDlg::OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    EndDialog(wID);
    return 0;
}

LRESULT CTestDlg::OnSetLabelColor(WORD , WORD wID, HWND , BOOL&)
{
    m_label.SetWindowText(_T("OnSetLabelColor"));
    m_label.SetTextColor(RGB(255, 1, 1), true);
    return 0;
}

LRESULT CTestDlg::OnSetLinkColor(WORD , WORD wID, HWND , BOOL&)
{
    m_link.SetTextColor(RGB(255, 1, 1), true);
    m_link.SetColors(RGB(0, 255, 0), RGB(0, 255, 255), true);
    return 0;
}

LRESULT CTestDlg::OnLinkClicked(UINT uMsg, WPARAM wParam, LPARAM , BOOL&)
{
    INT nId = (INT)wParam;
    TCHAR msg[128];
    _stprintf_s(msg, 128, _T("AlertHyperLink %d が押されました。"), nId);
    m_message.SetWindowText(msg);
    return 0;
}


LRESULT CTestDlg::OnSetPicture(WORD , WORD wID, HWND , BOOL&)
{
    if (wID == IDC_SET_PICTURE1) {
        m_picture.SetBitmap(IDB_BITMAP_DOWNLOAD, true);
    } else if (wID == IDC_SET_PICTURE2) {
        m_picture.SetIcon(IDI_MAIL, 32, 32, true);
    } else if (wID == IDC_SET_PICTURE3) {
        m_picture.SetBitmap(IDB_BITMAP_FLAG, true);
        //m_picture.SetTransparentColor(RGB(255, 0, 0));
    }

    return 0;
}

LRESULT CTestDlg::OnButtonClicked(WORD , WORD wID, HWND , BOOL&)
{
    TCHAR msg[128];

    if (wID == IDC_ALERT_BUTTON) {
        _stprintf_s(msg, 128, _T("AlertButton %d が押されました。"), wID);
    } else if (wID == IDC_ALERT_BUTTON_CLOSE) {
        _stprintf_s(msg, 128, _T("AlertButtonClose %d が押されました。"), wID);
    } else {
        _stprintf_s(msg, 128, _T("Unknown %d が押されました。"), wID);
    }

    m_message.SetWindowText(msg);
    return 0;
}