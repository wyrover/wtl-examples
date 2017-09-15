// downloadlistdlg.cpp : implementation of the CDownloadListDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "downloadlistdlg.h"

LRESULT CDownloadListDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    CenterWindow(GetParent());
    m_DownloadListView.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | LVS_REPORT, LVS_EX_FULLROWSELECT, (HMENU)IDC_DOWNLOAD_LISTVIEW);
//  InitListView( &m_DownloadListView , DOWNLOADLISTVIEW);
//  m_DownloadListView.Attach(GetDlgItem(IDC_LIST_DOWNLOAD));
    m_DownloadListView.InsertColumn(0, L"状态", LVCFMT_LEFT, 100, 0);
    m_DownloadListView.InsertColumn(1, L"专利号", LVCFMT_LEFT, 100, 0);
    m_DownloadListView.InsertColumn(2, L"专利名称", LVCFMT_LEFT, 200, 0);
    m_DownloadListView.InsertColumn(3, L"进度", LVCFMT_LEFT, 100, 0);
    m_DownloadListView.InsertColumn(4, L"来源", LVCFMT_LEFT, 50, 0);
    m_DownloadListView.InsertColumn(5, L"页数", LVCFMT_LEFT, 50, 0);
    m_DownloadListView.InsertColumn(6, L"申请日", LVCFMT_LEFT, 100, 0);
    m_DownloadListView.InsertColumn(7, L"发明人", LVCFMT_LEFT, 100, 0);
    m_DownloadListView.InsertColumn(8, L"申请人", LVCFMT_LEFT, 100, 0);
    DWORD dwStyle = m_DownloadListView.GetExtendedListViewStyle();
    dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
    m_DownloadListView.SetExtendedListViewStyle(dwStyle);
    m_DownloadListView.InsertItem(0, L"");
    m_DownloadListView.SetItemText(0, 1, L"hello");
    m_DownloadListView.SetItemText(0, 2, L"world");
    return TRUE;
}

LRESULT CDownloadListDlg::OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    //EndDialog(wID);
    AtlMessageBox(NULL, L"hello");
    return 0;
}

LRESULT CDownloadListDlg::OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    RECT rect;
    //  GetClientRect(&rect);
    GetWindowRect(&rect);
    int height = rect.bottom - rect.top;
    int width = rect.right - rect.left;
    //GetDlgItem(IDC_SEARCH_LISTVIEW).MoveWindow(0, 50, 2800, height-100);
    GetDlgItem(IDC_DOWNLOAD_LISTVIEW).MoveWindow(0, 50, 2800, height);
    return 0;
}

LRESULT CDownloadListDlg::OnLvnItemchangedListDownload(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/)
{
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
    // TODO: 在此添加控件通知处理程序代码
    /*
    判断：
    如果有任务被选中， 删除按钮显示
        如果有正在下载的 停止按钮 显示
        如果有已停止的任务，开始按钮 显示
    如没有任务被选中，三个按钮都为false

    */
    CString status_name;

    if (m_DownloadListView.GetSelectedCount()) {
        int nItemCount = m_DownloadListView.GetItemCount(); //表项总数

        for (int i = nItemCount - 1; i >= 0; i--) {
            int iState = m_DownloadListView.GetItemState(i, LVIS_SELECTED);

            if (iState != 0) {
                m_DownloadListView.GetItemText(i, 0, status_name);

                if (status_name == _T("已停止")) {
                    GetDlgItem(ID_DOWNLOAD_START).EnableWindow(TRUE);
                } else if (status_name == _T("正在下载")) {
                    GetDlgItem(ID_DOWNLOAD_STOP).EnableWindow(TRUE);
                } else {
                    GetDlgItem(ID_DOWNLOAD_START).EnableWindow(TRUE);
                    GetDlgItem(ID_DOWNLOAD_STOP).EnableWindow(TRUE);
                }
            }
        }

        GetDlgItem(ID_DOWNLOAD_DEL).EnableWindow(TRUE);
    } else {
        GetDlgItem(ID_DOWNLOAD_START).EnableWindow(FALSE);
        GetDlgItem(ID_DOWNLOAD_STOP).EnableWindow(FALSE);
        GetDlgItem(ID_DOWNLOAD_DEL).EnableWindow(FALSE);
    }

    return 0;
}

LRESULT CDownloadListDlg::OnNMRclickListDownload(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/)
{
    // TODO: 在此添加控件通知处理程序代码
    CMenu obMenu ;
    HMENU m_hMenu = NULL;
    CPoint obCursorPoint = (0, 0);
    GetCursorPos(&obCursorPoint);
    obMenu.LoadMenu(IDR_DOWNLOAD_POP);
    m_hMenu = obMenu.GetSubMenu(0);

    // Track the popup menu
    if (m_hMenu != NULL)
        TrackPopupMenu(m_hMenu, TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON, obCursorPoint.x, obCursorPoint.y, 0, this->m_hWnd, &rcDefault);

    return 0;
}

LRESULT CDownloadListDlg::OnSelectAll(WORD , WORD , HWND , BOOL&)
{
    int nItemCount = m_DownloadListView.GetItemCount();//表项总数

    for (int i = nItemCount - 1; i >= 0 ; i--) {
        m_DownloadListView.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
    }

    return 0;
}

LRESULT CDownloadListDlg::OnReSelect(WORD , WORD , HWND , BOOL&)
{
    int nItemCount = m_DownloadListView.GetItemCount();//表项总数

    for (int i = nItemCount - 1; i >= 0 ; i--) {
        int istate = m_DownloadListView.GetItemState(i, LVIS_SELECTED);

        if (0 != istate) {
            // 如果当前选中，则撤销选中
            m_DownloadListView.SetItemState(i, 0, LVIS_SELECTED);
        } else
            m_DownloadListView.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
    }

    return 0;
}
