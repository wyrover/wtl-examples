#pragma once

#include "notify.h"
#include "resource.h"

// CMailAlert dialog
class CMailAlert : public CAlertDialog<CMailAlert>
{
public:
    BEGIN_MSG_MAP(CMailAlert)
    MSG_WM_INITDIALOG(OnInitDialog)
    COMMAND_ID_HANDLER(IDCANCEL, OnButtonClicked)
    COMMAND_ID_HANDLER(IDC_STATIC_CONTENT, OnContentClicked)
    CHAIN_MSG_MAP(CAlertDialog<CMailAlert>)
    REFLECT_NOTIFICATIONS();
    END_MSG_MAP()


private:
    CFont m_fontFrom;
    CAlertLabel m_ctrlFrom;
    CAlertLabel m_ctrlTitle;
    CAlertPictureCtrl m_ctrlIcon;
    CAlertButton m_btnFlag;
    CAlertButton m_btnDelete;
    CAlertButtonClose m_btnClose;
    CAlertHyperLink m_ctrlContent;
    CStatic m_message;

public:

    // standard constructor
    CMailAlert(CWindow* pParent = NULL) :
        CAlertDialog<CMailAlert>(CMailAlert::IDD, pParent) {}

    virtual ~CMailAlert() {}

// Dialog Data
    enum { IDD = IDD_MAIL_ALERT };

protected:
    //virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    BOOL OnInitDialog(CWindow wndFocus, LPARAM lInitParam);

    LRESULT OnContentClicked(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

    LRESULT OnButtonClicked(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

    virtual void OnInvalidate();
};
