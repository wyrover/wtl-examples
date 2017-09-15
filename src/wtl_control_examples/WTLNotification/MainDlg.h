// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "notify.h"
#include "resource.h"
#include "MailAlert.h"
#include "FirefoxAlert.h"
#include "WinampAlert.h"

class CMainDlg : public CDialogImpl<CMainDlg>, public CUpdateUI<CMainDlg>,
    public CMessageFilter, public CIdleHandler
{
public:
    enum { IDD = IDD_NOTIFICATIONDEMO_DIALOG };

    CMainDlg();
    virtual ~CMainDlg();

    virtual BOOL PreTranslateMessage(MSG* pMsg)
    {
        return CWindow::IsDialogMessage(pMsg);
    }

    virtual BOOL OnIdle()
    {
        return FALSE;
    }

    BEGIN_UPDATE_UI_MAP(CMainDlg)
    END_UPDATE_UI_MAP()

    BEGIN_MSG_MAP(CMainDlg)
    MSG_WM_INITDIALOG(OnInitDialog)
    MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
    COMMAND_ID_HANDLER(IDOK, OnOK)
    COMMAND_ID_HANDLER(IDCANCEL, OnOK)
    COMMAND_ID_HANDLER(IDC_BUTTON_SHOWMAIL, OnBnClickedButtonShowMail)
    COMMAND_ID_HANDLER(IDC_BUTTON_SHOWFIREFOX, OnBnClickedButtonShowFirefox)
    COMMAND_ID_HANDLER(IDC_BUTTON_SHOWWINAMP, OnBnClickedButtonShowWinamp)
    MSG_WM_HSCROLL(OnHScroll)
    END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//  LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//  LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//  LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

private:
    BOOL OnInitDialog(CWindow wndFocus, LPARAM lInitParam);

    LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

    LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

    LRESULT OnBnClickedButtonShowMail(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnBnClickedButtonShowFirefox(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnBnClickedButtonShowWinamp(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

    LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

    void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar pScrollBar);
private:
    void CloseDialog(int nVal);

private:
    CMailAlert* m_pMailAlert;
    CAlertStyle* m_pMailAlertStyle;

    CFirefoxAlert* m_pFirefoxAlert;
    CAlertStyle* m_pFirefoxAlertStyle;

    CWinampAlert* m_pWinampAlert;
    CAlertStyle* m_pWinampAlertStyle;

    CComboBox m_cbStyle;
    CTrackBarCtrl m_slAnimation;
    CTrackBarCtrl m_slVisibility;
    CTrackBarCtrl m_slOpacity;

    CButton m_opaque_button;
};
