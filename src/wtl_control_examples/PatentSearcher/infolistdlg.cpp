// infolistdlg.cpp : implementation of the CInfoListDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "infolistdlg.h"

LRESULT CInfoListDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    CenterWindow(GetParent());
//  m_InfoListView.Create(m_hWnd, rect, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | LVS_REPORT, LVS_EX_FULLROWSELECT,(HMENU)IDC_INFO_LISTVIEW);
//  InitListView( &m_InfoListView , DOWNLOADLISTVIEW);
    m_InfoListView.Attach(GetDlgItem(IDC_LIST_INFO));
    m_InfoListView.InsertColumn(0, L"序号", LVCFMT_LEFT, 50, 0);
    m_InfoListView.InsertColumn(1, L"专利号", LVCFMT_LEFT, 100, 0);
    m_InfoListView.InsertColumn(2, L"专利名称", LVCFMT_LEFT, 240, 0);
    m_InfoListView.InsertColumn(3, L"来源", LVCFMT_LEFT, 50, 0);
    m_InfoListView.InsertColumn(4, L"页数", LVCFMT_LEFT, 50, 0);
    m_InfoListView.InsertColumn(5, L"全文", LVCFMT_LEFT, 50, 0);
    m_InfoListView.InsertColumn(6, L"法律状态", LVCFMT_LEFT, 80, 2);
    m_InfoListView.InsertColumn(7, L"下载时间", LVCFMT_LEFT, 100, 2);
    DWORD dwStyle = m_InfoListView.GetExtendedListViewStyle();
    dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
    m_InfoListView.SetExtendedListViewStyle(dwStyle);
    return TRUE;
}

LRESULT CInfoListDlg::OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    //EndDialog(wID);
    AtlMessageBox(NULL, L"hello");
    return 0;
}

LRESULT CInfoListDlg::OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    RECT rect;
    GetWindowRect(&rect);
    int height = rect.bottom - rect.top;
    int width = rect.right - rect.left;
    GetDlgItem(IDC_LIST_INFO).MoveWindow(0, 50, 2800, height);
    return 0;
}

LRESULT CInfoListDlg::OnLvnItemchangedListDownload(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/)
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

    if (m_InfoListView.GetSelectedCount()) {
        GetDlgItem(ID_INFO_OPEN).EnableWindow(TRUE);
        GetDlgItem(ID_EXPORT).EnableWindow(TRUE);
        GetDlgItem(ID_INFO_DEL).EnableWindow(TRUE);
    } else {
        GetDlgItem(ID_INFO_OPEN).EnableWindow(FALSE);
        GetDlgItem(ID_EXPORT).EnableWindow(FALSE);
        GetDlgItem(ID_INFO_DEL).EnableWindow(FALSE);
    }

    return 0;
}

LRESULT CInfoListDlg::OnNMRclickListDownload(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/)
{
    // TODO: 在此添加控件通知处理程序代码
    CMenu obMenu ;
    HMENU m_hMenu = NULL;
    CPoint obCursorPoint = (0, 0);
    GetCursorPos(&obCursorPoint);
    obMenu.LoadMenu(IDR_INFO_POP);
    m_hMenu = obMenu.GetSubMenu(0);

    // Track the popup menu
    if (m_hMenu != NULL)
        TrackPopupMenu(m_hMenu, TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON, obCursorPoint.x, obCursorPoint.y, 0, this->m_hWnd, &rcDefault);

    return 0;
}

LRESULT CInfoListDlg::OnSelectAll(WORD , WORD , HWND , BOOL&)
{
    int nItemCount = m_InfoListView.GetItemCount();//表项总数

    for (int i = nItemCount - 1; i >= 0 ; i--) {
        m_InfoListView.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
    }

    return 0;
}

LRESULT CInfoListDlg::OnReSelect(WORD , WORD , HWND , BOOL&)
{
    int nItemCount = m_InfoListView.GetItemCount();//表项总数

    for (int i = nItemCount - 1; i >= 0 ; --i) {
        int istate = m_InfoListView.GetItemState(i, LVIS_SELECTED);

        if (0 != istate) {
            // 如果当前选中，则撤销选中
            m_InfoListView.SetItemState(i, 0, LVIS_SELECTED);
        } else
            m_InfoListView.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
    }

    return 0;
}