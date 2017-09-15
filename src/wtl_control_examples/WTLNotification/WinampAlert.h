#pragma once

#include "notify.h"
#include "resource.h"

// CWinampAlert dialog
class CWinampAlert : public CAlertDialog<CWinampAlert>
{
public:
    BEGIN_MSG_MAP(CMailAlert)
    MSG_WM_INITDIALOG(OnInitDialog)
    MSG_WM_LBUTTONDOWN(OnLButtonDown)
    COMMAND_ID_HANDLER(IDC_STATIC_CONTENT, OnContentClicked)
    CHAIN_MSG_MAP(CAlertDialog<CWinampAlert>)
    REFLECT_NOTIFICATIONS();
    END_MSG_MAP()

    CWinampAlert(CWindow* pParent = NULL);   // standard constructor
    virtual ~CWinampAlert();

    // Dialog Data
    enum { IDD = IDD_WINAMP_ALERT };

protected:
    BOOL OnInitDialog(CWindow wndFocus, LPARAM lInitParam);

    void OnLButtonDown(UINT nFlags, CPoint point);

    LRESULT OnContentClicked(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

private:
    CFont m_fontTitle;

    CAlertLabel m_ctrlTrackNo;
    CAlertLabel m_ctrlDesc;
    CAlertLabel m_ctrlTitle;
    CAlertLabel m_ctrlAuthor;
    CAlertLabel m_ctrlAlbum;

};
