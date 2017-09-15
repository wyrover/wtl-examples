// searchlistdlg.h : interface of the CSearchListDlg class
//
// author: luckey_sun
// email : sunlaibing88@gmail.com
// date  : 2011.12.31
/////////////////////////////////////////////////////////////////////////////

#pragma once
#include <atlstr.h>
#include <atlmisc.h>
#include <atlddx.h>

class CSearchListDlg : public CDialogImpl<CSearchListDlg>,
    public CWinDataExchange<CSearchListDlg>
{
public:
    enum { IDD = IDD_DLG_SEARCH };

    BEGIN_MSG_MAP(CSearchListDlg)
    MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
    COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
    COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
    MESSAGE_HANDLER(WM_SIZE, OnSize)
    NOTIFY_HANDLER(IDC_LIST_SEARCH, LVN_ITEMCHANGED, OnLvnItemchangedListDownload)
    NOTIFY_HANDLER(IDC_LIST_SEARCH, NM_RCLICK, OnNMRclickListDownload)
    COMMAND_HANDLER(ID_SEARCH_RELOAD, BN_CLICKED, OnBnClickedSearchReload)
    COMMAND_HANDLER(IDC_BTN_FIRSTPAGE, BN_CLICKED, OnBnClickedBtnFirstpage)
    COMMAND_HANDLER(IDC_BTN_PREVPAGE, BN_CLICKED, OnBnClickedBtnPrevpage)
    COMMAND_HANDLER(IDC_BTN_NEXTPAGE, BN_CLICKED, OnBnClickedBtnNextpage)
    COMMAND_HANDLER(IDC_BTN_LASTPAGE, BN_CLICKED, OnBnClickedBtnLastpage)
    COMMAND_HANDLER(IDC_BTN_GO, BN_CLICKED, OnBnClickedBtnGo)

    /************************************************************************/
    /* 以下为右击菜单响应                                                   */
    /************************************************************************/
    COMMAND_ID_HANDLER(ID_SEARCH_SELECTALL, OnSelectAll)
    COMMAND_ID_HANDLER(ID_SEARCH_RESELECT, OnReSelect)
    COMMAND_ID_HANDLER(ID_SEARCH_PREV, OnBnClickedBtnPrevpage)
    COMMAND_ID_HANDLER(ID_SEARCH_NEXT, OnBnClickedBtnNextpage)
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


public:
    CListViewCtrl m_searchListView;         //下载列表框

    HWND mainWnd;

public:
    //The utility model patent   实用新型专利
    //Patent of invention  发明专利
    //Appearance patent 外观专利
    bool CheckLocalDatabase(CString search_str, int page_index);
    void EnableAllPageControls();
    void UpdatePageInfo(int currentPage);
    void UpdatePatentInfo(int invent_num, int application_num, int appearance_num);

    LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnBnClickedSearchReload(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnBnClickedBtnFirstpage(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnBnClickedBtnPrevpage(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnBnClickedBtnNextpage(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnBnClickedBtnLastpage(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnBnClickedBtnGo(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};
