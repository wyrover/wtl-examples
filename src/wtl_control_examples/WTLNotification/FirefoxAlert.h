#pragma once

#include "notify.h"
#include "resource.h"


// CFirefoxAlert dialog
class CFirefoxAlert : public CAlertDialog<CFirefoxAlert>
{
public:
    BEGIN_MSG_MAP(CMailAlert)
    MSG_WM_INITDIALOG(OnInitDialog)
    COMMAND_ID_HANDLER(IDC_STATIC_CONTENT, OnContentClicked)
    CHAIN_MSG_MAP(CAlertDialog<CFirefoxAlert>)
    REFLECT_NOTIFICATIONS();
    END_MSG_MAP()

    // standard constructor
    CFirefoxAlert(CWindow* pParent = NULL);
    virtual ~CFirefoxAlert();

    // Dialog Data
    enum { IDD = IDD_FIREFOX_ALERT };

protected:
    BOOL OnInitDialog(CWindow wndFocus, LPARAM lInitParam);

    LRESULT OnContentClicked(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

private:
    CFont m_fontTitle;

    CAlertLabel m_ctrlTitle;
    CAlertHyperLink m_ctrlContent;
    CAlertPictureCtrl m_ctrlImage;
};
