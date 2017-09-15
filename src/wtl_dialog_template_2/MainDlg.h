#ifndef __MAINDLG_H__
#define __MAINDLG_H__

#include "wtl_dialog_template_2/ctrls/datalist_t.h"


class CMainDlg : public CDialogImpl<CMainDlg>
    , public CWinDataExchange<CMainDlg>
{
public:
    enum { IDD = IDD_MAINDLG };

    BEGIN_MSG_MAP(CMainDlg)
    COMMAND_HANDLER(IDC_BUTTON1, BN_CLICKED, OnBnClickedButton1)
    MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
    COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
    COMMAND_ID_HANDLER(IDOK, OnOK)
    COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
    END_MSG_MAP()

    BEGIN_DDX_MAP(CMainDlg)
    DDX_CONTROL(IDC_LIST1, owner_draw_listbox1_)
    END_DDX_MAP();

// Handler prototypes (uncomment arguments if needed):
//  LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//  LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//  LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

    LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnBnClickedButton1(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
public:
    CDevListBoxImpl owner_draw_listbox1_;
};

#endif // __MAINDLG_H__
