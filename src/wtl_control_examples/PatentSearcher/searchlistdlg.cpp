// searchlistdlg.cpp : implementation of the CSearchListDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "searchlistdlg.h"

LRESULT CSearchListDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    CenterWindow(GetParent());
    m_searchListView.Attach(GetDlgItem(IDC_LIST_SEARCH));
    m_searchListView.InsertColumn(0, L"序号", LVCFMT_LEFT, 50, 0);
    m_searchListView.InsertColumn(1, L"专利号", LVCFMT_LEFT, 100, 0);
    m_searchListView.InsertColumn(2, L"专利名称", LVCFMT_LEFT, 240, 0);
    m_searchListView.InsertColumn(3, L"来源", LVCFMT_LEFT, 250, 0);
    DWORD dwStyle = m_searchListView.GetExtendedListViewStyle();
    dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
    m_searchListView.SetExtendedListViewStyle(dwStyle);
    //DoDataExchange(FALSE);
    mainWnd = GetParent().GetParent().GetParent().GetParent().GetParent().m_hWnd;
    return TRUE;
}

LRESULT CSearchListDlg::OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    //EndDialog(wID);
    AtlMessageBox(NULL, L"hello");
    return 0;
}

LRESULT CSearchListDlg::OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    RECT rect;
    //  GetClientRect(&rect);
    GetWindowRect(&rect);
    int height = rect.bottom - rect.top;
    int width = rect.right - rect.left;
    GetDlgItem(IDC_STATIC_PATENTINFO).MoveWindow(width - 400, 22, 400, 20);
    GetDlgItem(IDC_LIST_SEARCH).MoveWindow(0, 50, 2800, height - 90);
    GetDlgItem(IDC_BTN_FIRSTPAGE).MoveWindow(10, height - 30, 40, 20);
    GetDlgItem(IDC_BTN_PREVPAGE).MoveWindow(60, height - 30, 50, 20);
    GetDlgItem(IDC_BTN_NEXTPAGE).MoveWindow(120, height - 30, 50, 20);
    GetDlgItem(IDC_BTN_LASTPAGE).MoveWindow(180, height - 30, 40, 20);
    GetDlgItem(IDC_STATIC1).MoveWindow(250, height - 26, 30, 20);
    GetDlgItem(IDC_EDIT_CURRENTPAGE).MoveWindow(280, height - 30, 40, 20);
    GetDlgItem(IDC_BTN_GO).MoveWindow(326, height - 30, 20, 20);
    GetDlgItem(IDC_STATIC_INFO).MoveWindow(width - 150, height - 30, 150, 20);
    return 0;
}

LRESULT CSearchListDlg::OnLvnItemchangedListDownload(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/)
{
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
    // TODO: 在此添加控件通知处理程序代码
    /*
    判断：
    如果有任务被选中， 下载选中 按钮显示
    如果是第一页， 则 首页和上一页 按钮为FALSE
    如果是尾页， 则 下一页和尾页 按钮为FALSE
    */
    CString status_name;

    if (m_searchListView.GetSelectedCount()) {
        GetDlgItem(ID_SEARCH_LOADSELECT).EnableWindow(TRUE);
        GetDlgItem(ID_SEARCH_RELOAD).EnableWindow(TRUE);
    } else {
        GetDlgItem(ID_SEARCH_LOADSELECT).EnableWindow(FALSE);
        GetDlgItem(ID_SEARCH_RELOAD).EnableWindow(FALSE);
    }

    return 0;
}

LRESULT CSearchListDlg::OnNMRclickListDownload(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/)
{
    // TODO: 在此添加控件通知处理程序代码
    CMenu obMenu ;
    HMENU m_hMenu = NULL;
    CPoint obCursorPoint = (0, 0);
    GetCursorPos(&obCursorPoint);
    obMenu.LoadMenu(IDR_SEARCH_POP);
    m_hMenu = obMenu.GetSubMenu(0);

    if (m_hMenu != NULL)
        TrackPopupMenu(m_hMenu, TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON, obCursorPoint.x, obCursorPoint.y, 0, this->m_hWnd, &rcDefault);

    return 0;
}

LRESULT CSearchListDlg::OnSelectAll(WORD , WORD , HWND , BOOL&)
{
    int nItemCount = m_searchListView.GetItemCount();//表项总数

    for (int i = nItemCount - 1; i >= 0 ; i--) {
        m_searchListView.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
    }

    m_searchListView.SetFocus();
    return 0;
}

LRESULT CSearchListDlg::OnReSelect(WORD , WORD , HWND , BOOL&)
{
    int nItemCount = m_searchListView.GetItemCount();//表项总数

    for (int i = nItemCount - 1; i >= 0 ; i--) {
        int istate = m_searchListView.GetItemState(i, LVIS_SELECTED);

        if (0 != istate) {
            // 如果当前选中，则撤销选中
            m_searchListView.SetItemState(i, 0, LVIS_SELECTED);
        } else
            m_searchListView.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
    }

    m_searchListView.SetFocus();
    return 0;
}

LRESULT CSearchListDlg::OnBnClickedSearchReload(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    // TODO: 在此添加控件通知处理程序代码
    ::SendMessage(mainWnd, WM_SEARCH_RELOADSELECT, 0, 0);
    return 0;
}

LRESULT CSearchListDlg::OnBnClickedBtnFirstpage(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    // TODO: 在此添加控件通知处理程序代码
    ::SendMessage(mainWnd, WM_SEARCH_FIRSTPAGE, 0, 0);
    return 0;
}

LRESULT CSearchListDlg::OnBnClickedBtnPrevpage(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    // TODO: 在此添加控件通知处理程序代码
    ::SendMessage(mainWnd, WM_SEARCH_PREVPAGE, 0, 0);
    return 0;
}

LRESULT CSearchListDlg::OnBnClickedBtnNextpage(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    // TODO: 在此添加控件通知处理程序代码
    ::SendMessage(mainWnd, WM_SEARCH_NEXTPAGE, 0, 0);
    return 0;
}

LRESULT CSearchListDlg::OnBnClickedBtnLastpage(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    // TODO: 在此添加控件通知处理程序代码
    ::SendMessage(mainWnd, WM_SEARCH_LASTPAGE, 0, 0);
    return 0;
}

LRESULT CSearchListDlg::OnBnClickedBtnGo(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    // TODO: 在此添加控件通知处理程序代码
    ::SendMessage(mainWnd, WM_SEARCH_GO, 0, 0);
    return 0;
}

void CSearchListDlg::EnableAllPageControls()
{
    GetDlgItem(IDC_BTN_FIRSTPAGE).EnableWindow(TRUE);
    GetDlgItem(IDC_BTN_PREVPAGE).EnableWindow(TRUE);
    GetDlgItem(IDC_BTN_NEXTPAGE).EnableWindow(TRUE);
    GetDlgItem(IDC_BTN_LASTPAGE).EnableWindow(TRUE);
}

void CSearchListDlg::UpdatePageInfo(int currentPage)
{
    DoDataExchange(FALSE);
}

void CSearchListDlg::UpdatePatentInfo(int invent_num, int application_num, int appearance_num)
{
    DoDataExchange(FALSE);
}