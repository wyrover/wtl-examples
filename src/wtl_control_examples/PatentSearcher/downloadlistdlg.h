// downloadlistdlg.h : interface of the CDownloadListDlg class
//
// author: luckey_sun
// email : sunlaibing88@gmail.com
// date  : 2011.12.31
/////////////////////////////////////////////////////////////////////////////

#pragma once

class CDownloadListDlg : public CDialogImpl<CDownloadListDlg>
{
public:
    enum { IDD = IDD_DLG_DOWNLOAD };

    BEGIN_MSG_MAP(CDownloadListDlg)
    MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
    COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
    COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
    COMMAND_ID_HANDLER(ID_DOWNLOAD_SELECTALL, OnSelectAll)
    COMMAND_ID_HANDLER(ID_DOWNLOAD_RESELECT, OnReSelect)
    MESSAGE_HANDLER(WM_SIZE, OnSize)
    NOTIFY_HANDLER(IDC_DOWNLOAD_LISTVIEW, LVN_ITEMCHANGED, OnLvnItemchangedListDownload)
    NOTIFY_HANDLER(IDC_DOWNLOAD_LISTVIEW, NM_RCLICK, OnNMRclickListDownload)
    END_MSG_MAP()

    // Handler prototypes (uncomment arguments if needed):
    //  LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    //  LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    //  LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

    LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnLvnItemchangedListDownload(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/);
    LRESULT OnNMRclickListDownload(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/);
    LRESULT OnSelectAll(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnReSelect(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

private:
    CListViewCtrl m_DownloadListView;           //ÏÂÔØÁÐ±í¿ò
public:
};
