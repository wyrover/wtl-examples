// infolistdlg.h : interface of the CInfoListDlg class
//
// author: luckey_sun
// email : sunlaibing88@gmail.com
// date  : 2011.12.31
/////////////////////////////////////////////////////////////////////////////

#pragma once

class CInfoListDlg : public CDialogImpl<CInfoListDlg>
{
public:
    enum { IDD = IDD_DLG_INFO };

    BEGIN_MSG_MAP(CInfoListDlg)
    MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
    COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
    COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
    COMMAND_ID_HANDLER(ID_SEARCH_SELECTALL, OnSelectAll)
    COMMAND_ID_HANDLER(ID_SEARCH_RESELECT, OnReSelect)
    MESSAGE_HANDLER(WM_SIZE, OnSize)
    NOTIFY_HANDLER(IDC_LIST_SEARCH, LVN_ITEMCHANGED, OnLvnItemchangedListDownload)
    NOTIFY_HANDLER(IDC_LIST_SEARCH, NM_RCLICK, OnNMRclickListDownload)
    END_MSG_MAP()

    // Handler prototypes (uncomment arguments if needed):
    //  LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    //  LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    //  LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

    LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnSelectAll(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnReSelect(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnLvnItemchangedListDownload(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/);
    LRESULT OnNMRclickListDownload(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/);
    LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

private:
    CListViewCtrl m_InfoListView;           //ÏÂÔØÁÐ±í¿ò
public:
};
