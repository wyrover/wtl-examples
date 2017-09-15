#pragma once

#include "resource.h"
#include "stdafx.h"
#include "notify.h"

class CTestDlg : public CDialogImpl<CTestDlg>
{
public:
    enum { IDD = IDD_TESTDLG };

    BEGIN_MSG_MAP(CAboutDlg)
    MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
    MESSAGE_HANDLER(WMA_HYPERLINKCLICKED, OnLinkClicked)
    COMMAND_ID_HANDLER(IDC_ALERT_BUTTON, OnButtonClicked)
    COMMAND_ID_HANDLER(IDC_ALERT_BUTTON_CLOSE, OnButtonClicked)
    COMMAND_ID_HANDLER(IDOK, OnOkCmd)
    COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
    COMMAND_ID_HANDLER(IDC_SET_LABEL_COLOR, OnSetLabelColor)
    COMMAND_ID_HANDLER(IDC_SET_LINK_COLOR, OnSetLinkColor)
    COMMAND_ID_HANDLER(IDC_SET_PICTURE1, OnSetPicture)
    COMMAND_ID_HANDLER(IDC_SET_PICTURE2, OnSetPicture)
    COMMAND_ID_HANDLER(IDC_SET_PICTURE3, OnSetPicture)
    REFLECT_NOTIFICATIONS();
    END_MSG_MAP()

private:
    LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

    LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

    LRESULT OnOkCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

    LRESULT OnSetLabelColor(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

    LRESULT OnSetLinkColor(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

    LRESULT OnLinkClicked(UINT uMsg, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/);

    LRESULT OnSetPicture(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

    LRESULT OnButtonClicked(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

private:
    CAlertLabel m_label;
    CAlertHyperLink m_link;
    CAlertPictureCtrl m_picture;
    CAlertButton m_button;
    CAlertButtonClose m_button_close;
    CStatic m_message;
};