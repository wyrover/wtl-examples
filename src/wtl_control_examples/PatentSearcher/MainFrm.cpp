// MainFrm.cpp : implmentation of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "aboutdlg.h"
#include "MainFrm.h"

#include <string>
#include <fstream>
#include <list>

using namespace std;

#include <stdio.h>
#include<io.h>
#define MAXBLOCKSIZE 1024*16

CString global_Search_str;
CString global_CheckBox_str;


CMainFrame::CMainFrame()
{
}

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
    return CFrameWindowImpl<CMainFrame>::PreTranslateMessage(pMsg);
}

BOOL CMainFrame::OnIdle()
{
    UIUpdateToolBar();
    UIUpdateStatusBar();
    return FALSE;
}

LRESULT CMainFrame::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    CreateSimpleToolBar();
    //  CreateSimpleStatusBar();
    // Create the multipane status bar and pass its handle to CUpdateUI.
    m_hWndStatusBar = m_wndStatusBar.Create(*this);
    UIAddStatusBar(m_hWndStatusBar);
    // Create the status bar panes.
    int anPanes[] = { ID_DEFAULT_PANE, IDPANE_SOURCE, IDPANE_SEARCH_TIME, IDPANE_DOWNLOADLIST, IDPANE_STATUS };
    m_wndStatusBar.SetPanes(anPanes, 5, false);
    // Set the initial text for the status pane.
    UISetText(1, _T("数据源：SIPO主服务器"));
    UISetText(2, _T("检索时间：--"));
    //第三段要从数据库中读取
    UISetText(4, _T(" 就绪 "));
    UIAddToolBar(m_hWndToolBar);
    UISetCheck(ID_VIEW_TOOLBAR, 1);
    UISetCheck(ID_VIEW_STATUS_BAR, 1);

    // 数据库初始化
    if (LRunSql::InitConnectPtr() == false)     //初始化COM环境，进行数据库连接
        return false;

    const DWORD dwSplitStyle = WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
                dwSplitExStyle = WS_EX_CLIENTEDGE;
    GetClientRect(&rcDefault);
    m_hWndClient = m_wndVertSplitter.Create(m_hWnd, rcDefault, NULL, dwSplitStyle, dwSplitExStyle);
    m_wndVertSplitter.m_bFullDrag = true;
    /************************************************************************/
    /* 树形结构                                                             */
    /************************************************************************/
    m_wndVertSplitter.GetClientRect(&rcDefault);
    m_MenuTree.Create(m_wndVertSplitter, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | TVS_HASLINES | TVS_LINESATROOT | TVS_SHOWSELALWAYS | TVS_HASBUTTONS | TVS_EDITLABELS | WS_EX_CLIENTEDGE, 0, (HMENU)IDC_LEFT_TREEVIEW);
    InitLeftTreeView(&m_MenuTree);
    m_wndHorzSplitter.Create(m_wndVertSplitter, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
    m_wndHorzSplitter.m_bFullDrag = true;
    m_wndVertSplitter.SetSplitterPanes(m_MenuTree, m_wndHorzSplitter);
    m_TopVertSplitter.Create(m_wndHorzSplitter, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
    m_wndHorzSplitter.m_bFullDrag = true;
    m_BottomVertSplitter.Create(m_wndHorzSplitter, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
    m_wndHorzSplitter.SetSplitterPanes(m_TopVertSplitter, m_BottomVertSplitter);
    m_wndHorzSplitter.SetSinglePaneMode(SPLIT_PANE_BOTTOM);
    /************************************************************************/
    /* 浏览器窗口                                                           */
    /************************************************************************/
    //Create the bottom pane(browser)
    const DWORD dwIEStyle = WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_HSCROLL | WS_HSCROLL,
                dwIEExStyle = WS_EX_CLIENTEDGE;
    // 获得当前路径
    TCHAR szFilePath[MAX_PATH + 1];
    GetModuleFileName(NULL, szFilePath, MAX_PATH);
    (_tcsrchr(szFilePath, _T('\\')))[1] = 0;
    currentPath = szFilePath;
    CString mainWebPath = currentPath + "home.htm";
    m_MainWebBrowser.Create(m_BottomVertSplitter, rcDefault, mainWebPath, dwIEStyle, dwIEExStyle);
    m_InfoWebBrowser.Create(m_BottomVertSplitter, rcDefault, L"http://www.baidu.com", dwIEStyle, dwIEExStyle);
    m_BottomVertSplitter.SetSplitterPanes(m_MainWebBrowser, m_InfoWebBrowser);
    m_BottomVertSplitter.SetSinglePaneMode(SPLIT_PANE_LEFT);
    m_infoListDlg.Create(m_TopVertSplitter, rcDefault);
    m_TopHorzSplitter.Create(m_TopVertSplitter, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
    m_TopVertSplitter.SetSplitterPanes(m_infoListDlg, m_TopHorzSplitter);
    m_downloadListDlg.Create(m_TopHorzSplitter, rcDefault);
    m_searchListDlg.Create(m_TopHorzSplitter, rcDefault);
    m_TopHorzSplitter.SetSplitterPanes(m_downloadListDlg, m_searchListDlg);
    // register object for message filtering and idle updates
    CMessageLoop* pLoop = _Module.GetMessageLoop();
    ATLASSERT(pLoop != NULL);
    pLoop->AddMessageFilter(this);
    pLoop->AddIdleHandler(this);
    UpdateLayout();
    m_wndVertSplitter.m_cxyMin = 150;
    m_wndVertSplitter.SetSplitterPos(200);
    m_wndHorzSplitter.SetSplitterPos(200);
    m_TopVertSplitter.SetSplitterPos(200);
    m_TopHorzSplitter.SetSplitterPos(100);
//  logfile.open("mylog.txt");
//  DeleteDirectory(L"D:\\My\ Documents\\Visual\ Studio\ 2008\\PatentSearcher\\PatentSearcher\\Debug\\TempFolder\\CN03113273.1\\");
//  DeleteDirectory(L"C:\\test\\");
    return 0;
}

LRESULT CMainFrame::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
    LRunSql::Close();       //断开数据库连接
    // unregister message filtering and idle updates
    CMessageLoop* pLoop = _Module.GetMessageLoop();
    ATLASSERT(pLoop != NULL);
    pLoop->RemoveMessageFilter(this);
    pLoop->RemoveIdleHandler(this);
    bHandled = FALSE;
    return 1;
}

LRESULT CMainFrame::OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    PostMessage(WM_CLOSE);
    return 0;
}

LRESULT CMainFrame::OnFileNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    // TODO: add code to initialize document
    return 0;
}

LRESULT CMainFrame::OnViewToolBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    BOOL bVisible = !::IsWindowVisible(m_hWndToolBar);
    ::ShowWindow(m_hWndToolBar, bVisible ? SW_SHOWNOACTIVATE : SW_HIDE);
    UISetCheck(ID_VIEW_TOOLBAR, bVisible);
    UpdateLayout();
    return 0;
}

LRESULT CMainFrame::OnViewStatusBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    BOOL bVisible = !::IsWindowVisible(m_hWndStatusBar);
    ::ShowWindow(m_hWndStatusBar, bVisible ? SW_SHOWNOACTIVATE : SW_HIDE);
    UISetCheck(ID_VIEW_STATUS_BAR, bVisible);
    UpdateLayout();
    return 0;
}

LRESULT CMainFrame::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    CAboutDlg dlg;
    dlg.DoModal();
    return 0;
}

LRESULT CMainFrame::OnNetSearch(WORD , WORD , HWND , BOOL&)
{
    //将焦点定位到树节点 “搜索结果”
    HTREEITEM   treeItem;
    treeItem = m_MenuTree.GetRootItem();
    HTREEITEM hChildItem = m_MenuTree.GetChildItem(treeItem);
    HTREEITEM hNextItem = m_MenuTree.GetNextSiblingItem(hChildItem);
    m_MenuTree.Select(hNextItem, TVGN_CARET);
    return 0;
}

LRESULT CMainFrame::OnLocalSearch(WORD , WORD , HWND , BOOL&)
{
    //将焦点定位到树节点 “数据查询结果”
    HTREEITEM   treeItem;
    treeItem = m_MenuTree.GetRootItem();
    m_MenuTree.Select(treeItem, TVGN_CARET);
    HTREEITEM hChildItem = m_MenuTree.GetChildItem(treeItem);
    HTREEITEM hNextItem = m_MenuTree.GetNextSiblingItem(hChildItem);
    hNextItem = m_MenuTree.GetNextSiblingItem(hNextItem);
    HTREEITEM hChildItem2 = m_MenuTree.GetChildItem(hNextItem);
    m_MenuTree.Select(hChildItem2, TVGN_CARET);
    //m_MenuTree.SelectItem(hNextItem);
    return 0;
}


void CMainFrame::InitLeftTreeView(CTreeViewCtrlEx *m_pTreeView)
{
    int nIconIndexNormal = -1, nIconIndexSelected = -1;
    HICON hIcon = NULL;
    // NOTE: Don't Load using the LR_LOADTRANSPARENT bit, because the icon
    //  already properly deals with transparency (setting it causes problems).
    //  We will load this as LR_SHARED so that we don't have to do a DeleteIcon.
    m_LeftTreeImageList.Create(16, 16, ILC_COLOR32 | ILC_MASK, 10, 30);
    hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(),
                               MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, LR_SHARED);
    nIconIndexNormal = m_LeftTreeImageList.AddIcon(hIcon);
    nIconIndexSelected = nIconIndexNormal;
    int nIconFolderIndexNormal = -1, nIconFolderIndexSelected = -1;
    hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(),
                               MAKEINTRESOURCE(IDI_ICON2), IMAGE_ICON, 16, 16, LR_SHARED);
    nIconFolderIndexNormal = m_LeftTreeImageList.AddIcon(hIcon);
    hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(),
                               MAKEINTRESOURCE(IDI_ICON3), IMAGE_ICON, 16, 16, LR_SHARED);
    nIconFolderIndexSelected = m_LeftTreeImageList.AddIcon(hIcon);
    hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(),
                               MAKEINTRESOURCE(IDI_ICON4), IMAGE_ICON, 16, 16, LR_SHARED);
    nIconFolderIndexSelected = m_LeftTreeImageList.AddIcon(hIcon);
    hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(),
                               MAKEINTRESOURCE(IDI_ICON5), IMAGE_ICON, 16, 16, LR_SHARED);
    nIconFolderIndexSelected = m_LeftTreeImageList.AddIcon(hIcon);
    hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(),
                               MAKEINTRESOURCE(IDI_ICON6), IMAGE_ICON, 16, 16, LR_SHARED);
    nIconFolderIndexSelected = m_LeftTreeImageList.AddIcon(hIcon);
    // Hook up the image list to the tree view
    m_pTreeView->SetImageList(m_LeftTreeImageList, TVSIL_NORMAL);
    CTreeItem tiRoot = m_pTreeView->InsertItem(_T("专利信息平台"), 0, 0, TVI_ROOT, NULL);
    CTreeItem tiFolder1 = m_pTreeView->InsertItem(_T("正在下载"), 1, 1, tiRoot, NULL);
    CTreeItem tiFolder2 = m_pTreeView->InsertItem(_T("搜索结果"), 2, 2, tiRoot, NULL);
    CTreeItem tiFolder3 = m_pTreeView->InsertItem(_T("全部本地数据"), 3, 3, tiRoot, NULL);
    //  m_pTreeView->InsertItem(_T("今日下载"), nIconIndexNormal, nIconIndexSelected, tiFolder3, NULL);
    //  m_pTreeView->InsertItem(_T("昨日下载"), nIconIndexNormal, nIconIndexSelected, tiFolder3, NULL);
    m_pTreeView->InsertItem(_T("数据查询结果"), 4, 4, tiFolder3, NULL);
    CTreeItem tiFolder4 = m_pTreeView->InsertItem(_T("自定义分类"), 5, 5, tiRoot, NULL);
    FindNode(tiFolder4, "0");
    tiRoot.Expand();
    tiFolder1.Expand();
    tiFolder3.Expand();
    tiFolder4.Expand();
}

void CMainFrame::FindNode(CTreeItem h_parent, CString str)
{
    _ConnectionPtr tempconn;
    _RecordsetPtr temprecord;
    tempconn.CreateInstance(__uuidof(Connection));
    temprecord.CreateInstance(__uuidof(Recordset));
    tempconn->ConnectionString = m_runsql.m_database->ConnectionString;
    tempconn->Open("", "", "", -1);
    CString sql;
    sql.Format(L"select id, parent_class, class_name from custom_class where parent_class=%s", str);
    temprecord = tempconn->Execute((_bstr_t)sql, 0, adCmdText);
    CString name, parent_class;
    CTreeItem h_temp;

    while (!temprecord->adoEOF) {
        parent_class = (LPCTSTR)(_bstr_t)temprecord->GetCollect("id");
        name = (LPCTSTR)(_bstr_t)temprecord->GetCollect("class_name");
        h_temp = m_MenuTree.InsertItem(name, 5, 5, h_parent, NULL);
        FindNode(h_temp, parent_class);
        temprecord->MoveNext();
    }

    h_parent.Expand();
}

LRESULT CMainFrame::OnTvnBeginlabeleditTree(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/)
{
    LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
    // TODO: 在此添加控件通知处理程序代码
    //AtlMessageBox(NULL, L"edit label!");
    return 0;
}

LRESULT CMainFrame::OnTvnEndlabeleditTree(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/)
{
    LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
    // TODO: 在此添加控件通知处理程序代码
    //AtlMessageBox(NULL, L"edit label!");
    return 0;
}



void CMainFrame::InitListView(CListViewCtrl *m_pListView, int nType)
{
    if (nType == INFOLISTVIEW) {
        m_pListView->InsertColumn(0, L"序号", LVCFMT_LEFT, 50, 0);
        m_pListView->InsertColumn(1, L"专利号", LVCFMT_LEFT, 100, 0);
        m_pListView->InsertColumn(2, L"专利名称", LVCFMT_LEFT, 240, 0);
        m_pListView->InsertColumn(3, L"来源", LVCFMT_LEFT, 50, 0);
        m_pListView->InsertColumn(4, L"页数", LVCFMT_LEFT, 50, 0);
        m_pListView->InsertColumn(5, L"全文", LVCFMT_LEFT, 50, 0);
        m_pListView->InsertColumn(6, L"法律状态", LVCFMT_LEFT, 80, 2);
        m_pListView->InsertColumn(7, L"下载时间", LVCFMT_LEFT, 100, 2);
    } else if (nType == DOWNLOADLISTVIEW) {
        m_pListView->InsertColumn(0, L"状态", LVCFMT_LEFT, 100, 0);
        m_pListView->InsertColumn(1, L"专利号", LVCFMT_LEFT, 100, 0);
        m_pListView->InsertColumn(2, L"专利名称", LVCFMT_LEFT, 200, 0);
        m_pListView->InsertColumn(3, L"进度", LVCFMT_LEFT, 100, 0);
        m_pListView->InsertColumn(4, L"来源", LVCFMT_LEFT, 50, 0);
        m_pListView->InsertColumn(5, L"页数", LVCFMT_LEFT, 50, 0);
        m_pListView->InsertColumn(6, L"申请日", LVCFMT_LEFT, 100, 0);
        m_pListView->InsertColumn(7, L"发明人", LVCFMT_LEFT, 100, 0);
        m_pListView->InsertColumn(8, L"申请人", LVCFMT_LEFT, 100, 0);
    } else if (nType == SEARCHLISTVIEW) {
        m_pListView->InsertColumn(0, L"序号", LVCFMT_LEFT, 50, 0);
        m_pListView->InsertColumn(1, L"专利号", LVCFMT_LEFT, 100, 0);
        m_pListView->InsertColumn(2, L"专利名称", LVCFMT_LEFT, 240, 0);
        m_pListView->InsertColumn(3, L"来源", LVCFMT_LEFT, 50, 0);
    }

    DWORD dwStyle = m_pListView->GetExtendedListViewStyle();
    dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
    m_pListView->SetExtendedListViewStyle(dwStyle);
}

LRESULT CMainFrame::OnSelChanged(int idCtrl, LPNMHDR pNMHDR, BOOL& bHandled)
{
    if (idCtrl == IDC_LEFT_TREEVIEW) {
        CTreeItem m_SelectItem;
        CString m_ItemText;
        NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
        TVITEM item = pNMTreeView->itemNew;
        m_SelectItem = m_MenuTree.GetSelectedItem();
        m_SelectItem.GetText(m_ItemText);

        if (m_ItemText == _T("专利信息平台")) {
            m_wndHorzSplitter.SetSinglePaneMode(SPLIT_PANE_BOTTOM);
            m_BottomVertSplitter.SetSinglePaneMode(SPLIT_PANE_LEFT);
        } else if (m_ItemText == _T("正在下载")) {
            m_wndHorzSplitter.SetSinglePaneMode(SPLIT_PANE_TOP);
            m_TopVertSplitter.SetSinglePaneMode(SPLIT_PANE_RIGHT);
            m_TopHorzSplitter.SetSinglePaneMode(SPLIT_PANE_TOP);
        } else if (m_ItemText == _T("搜索结果")) {
            m_wndHorzSplitter.SetSinglePaneMode(SPLIT_PANE_TOP);
            m_TopVertSplitter.SetSinglePaneMode(SPLIT_PANE_RIGHT);
            m_TopHorzSplitter.SetSinglePaneMode(SPLIT_PANE_BOTTOM);
        } else if (m_ItemText == _T("今日下载")  || m_ItemText == _T("昨日下载")
                   || m_ItemText == _T("自定义分类")) {
            m_wndHorzSplitter.SetSinglePaneMode(SPLIT_PANE_TOP);
            m_TopVertSplitter.SetSinglePaneMode(SPLIT_PANE_LEFT);
            m_BottomVertSplitter.SetSinglePaneMode(SPLIT_PANE_RIGHT);
        } else if (m_ItemText == _T("数据查询结果")) {
            m_wndHorzSplitter.SetSinglePaneMode(SPLIT_PANE_TOP);
            m_TopVertSplitter.SetSinglePaneMode(SPLIT_PANE_LEFT);
            m_BottomVertSplitter.SetSinglePaneMode(SPLIT_PANE_RIGHT);
        } else if (m_ItemText == _T("全部本地数据")) {
            //m_wndHorzSplitter.SetSinglePaneMode( SPLIT_PANE_NONE );
            m_wndHorzSplitter.SetSinglePaneMode(SPLIT_PANE_TOP);
            m_TopVertSplitter.SetSinglePaneMode(SPLIT_PANE_LEFT);
            m_BottomVertSplitter.SetSinglePaneMode(SPLIT_PANE_RIGHT);
        }
    }

    return 0;
}

LRESULT CMainFrame::OnNMRClickList(int idCtrl, LPNMHDR pNMHDR, BOOL& bHandled)
{
    CMenu obMenu ;
    HMENU m_hMenu = NULL;
    CString m_ItemText;
    CPoint obCursorPoint = (0, 0);
    GetCursorPos(&obCursorPoint);

    if (idCtrl == IDC_LEFT_TREEVIEW) {
        CTreeItem m_RSelectItem;            //右击树形条目
        NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
        TVITEM item = pNMTreeView->itemNew;
        m_RSelectItem = m_MenuTree.GetDropHilightItem();
        m_MenuTree.SelectItem(m_RSelectItem);
        m_RSelectItem.GetText(m_ItemText);

        if (m_ItemText == _T("专利信息平台") || m_ItemText == _T("正在下载") || m_ItemText == _T("搜索结果") || \
            m_ItemText == _T("全部本地数据") || m_ItemText == _T("今日下载") || m_ItemText == _T("昨日下载") || m_ItemText == _T("数据查询结果")) {
        } else if (m_ItemText != L"") {
            obMenu.LoadMenu(IDR_TREE_POP);
            m_hMenu = obMenu.GetSubMenu(0);

            if (m_ItemText == _T("自定义分类")) {
                EnableMenuItem(m_hMenu, ID_TREE_DEL, MF_BYCOMMAND | MF_GRAYED | MF_DISABLED);
                EnableMenuItem(m_hMenu, ID_TREE_EDIT, MF_BYCOMMAND | MF_GRAYED | MF_DISABLED);
            } else {
                EnableMenuItem(m_hMenu, ID_TREE_CREATE, MF_BYCOMMAND | MF_GRAYED | MF_DISABLED);
                EnableMenuItem(m_hMenu, ID_TREE_DEL, MF_BYCOMMAND | MF_ENABLED);
                EnableMenuItem(m_hMenu, ID_TREE_EDIT, MF_BYCOMMAND | MF_ENABLED);
            }
        }
    }

    if (idCtrl == IDC_DOWNLOAD_LISTVIEW) {
        obMenu.LoadMenu(IDR_DOWNLOAD_POP);
        m_hMenu = obMenu.GetSubMenu(0);

        // Get the cursor position
        if (0 >= m_DownloadListView.GetSelectedCount()) {
            EnableMenuItem(m_hMenu, ID_DOWNLOAD_START, MF_BYCOMMAND | MF_GRAYED | MF_DISABLED);
            EnableMenuItem(m_hMenu, ID_DOWNLOAD_STOP, MF_BYCOMMAND | MF_GRAYED | MF_DISABLED);
            EnableMenuItem(m_hMenu, ID_DOWNLOAD_DEL, MF_BYCOMMAND | MF_GRAYED | MF_DISABLED);
        } else if (1 == m_DownloadListView.GetSelectedCount()) {
            CString status_name;
            //int nItemSelected=m_InfoListView.GetSelectedCount();//所选表项数
            int nItemCount = m_DownloadListView.GetItemCount(); //表项总数

            //if(nItemSelected<1) return 0;
            for (int i = nItemCount - 1; i >= 0; i--) {
                int iState = m_DownloadListView.GetItemState(i, LVIS_SELECTED);

                if (iState != 0) {
                    m_DownloadListView.GetItemText(i, 0, status_name);

                    if (status_name == _T("已停止")) {
                        EnableMenuItem(m_hMenu, ID_DOWNLOAD_START, MF_BYCOMMAND | MF_ENABLED);
                        EnableMenuItem(m_hMenu, ID_DOWNLOAD_STOP, MF_BYCOMMAND | MF_GRAYED | MF_DISABLED);
                    } else if (status_name == _T("正在下载")) {
                        EnableMenuItem(m_hMenu, ID_DOWNLOAD_START, MF_BYCOMMAND | MF_GRAYED | MF_DISABLED);
                        EnableMenuItem(m_hMenu, ID_DOWNLOAD_STOP, MF_BYCOMMAND | MF_ENABLED);
                    } else {
                        EnableMenuItem(m_hMenu, ID_DOWNLOAD_START, MF_BYCOMMAND | MF_GRAYED | MF_DISABLED);
                        EnableMenuItem(m_hMenu, ID_DOWNLOAD_STOP, MF_BYCOMMAND | MF_GRAYED | MF_DISABLED);
                    }
                }
            }

            EnableMenuItem(m_hMenu, ID_DOWNLOAD_DEL, MF_BYCOMMAND | MF_ENABLED);
        } else {
            EnableMenuItem(m_hMenu, ID_DOWNLOAD_START, MF_BYCOMMAND | MF_ENABLED);
            EnableMenuItem(m_hMenu, ID_DOWNLOAD_STOP, MF_BYCOMMAND | MF_ENABLED);
            EnableMenuItem(m_hMenu, ID_DOWNLOAD_DEL, MF_BYCOMMAND | MF_ENABLED);
        }
    } else if (idCtrl == IDC_INFO_LISTVIEW) {
        obMenu.LoadMenu(IDR_INFO_POP);
        m_hMenu = obMenu.GetSubMenu(0);
        // Get the cursor position
        CPoint obCursorPoint = (0, 0);
        GetCursorPos(&obCursorPoint);

        if (0 >= m_InfoListView.GetSelectedCount()) {
            EnableMenuItem(m_hMenu, ID_INFO_OPEN, MF_BYCOMMAND | MF_GRAYED | MF_DISABLED);
            EnableMenuItem(m_hMenu, ID_INFO_RELOAD, MF_BYCOMMAND | MF_GRAYED | MF_DISABLED);
        } else {
            EnableMenuItem(m_hMenu, ID_INFO_OPEN, MF_BYCOMMAND | MF_ENABLED);
            EnableMenuItem(m_hMenu, ID_INFO_RELOAD, MF_BYCOMMAND | MF_ENABLED);
        }
    } else if (idCtrl == IDC_SEARCH_LISTVIEW) {
        obMenu.LoadMenu(IDR_SEARCH_POP);
        m_hMenu = obMenu.GetSubMenu(0);
        // Get the cursor position
        CPoint obCursorPoint = (0, 0);
        GetCursorPos(&obCursorPoint);

        if (0 >= m_SearchListView.GetSelectedCount()) {
            EnableMenuItem(m_hMenu, ID_SEARCH_LOADSELECT, MF_BYCOMMAND | MF_GRAYED | MF_DISABLED);
            EnableMenuItem(m_hMenu, ID_SEARCH_RELOAD, MF_BYCOMMAND | MF_GRAYED | MF_DISABLED);
        } else {
            EnableMenuItem(m_hMenu, ID_SEARCH_LOADSELECT, MF_BYCOMMAND | MF_ENABLED);
            EnableMenuItem(m_hMenu, ID_SEARCH_RELOAD, MF_BYCOMMAND | MF_ENABLED);
        }
    }

    // Track the popup menu
    if (m_hMenu != NULL)
        TrackPopupMenu(m_hMenu, TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON, obCursorPoint.x, obCursorPoint.y, 0, this->m_hWnd, &rcDefault);

    return 0;
}


LRESULT CMainFrame::OnSearchFirst(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    return 0;
}


LRESULT CMainFrame::OnSearchPrev(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    return 0;
}

LRESULT CMainFrame::OnSearchNext(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    return 0;
}



LRESULT CMainFrame::OnViewTree(WORD , WORD , HWND , BOOL&)
{
    static bool b_hide = false;

    if (!b_hide) {      //如果为已经显示，改为隐藏
        m_wndVertSplitter.SetSinglePaneMode(SPLIT_PANE_RIGHT);
        b_hide = true;
    } else {
        m_wndVertSplitter.SetSinglePaneMode(SPLIT_PANE_NONE);
        b_hide = false;
    }

    return 0;
}

LRESULT CMainFrame::OnViewDownLoad(WORD , WORD , HWND , BOOL&)
{
    //将焦点定位到树节点 “搜索结果”
    HTREEITEM   treeItem;
    treeItem = m_MenuTree.GetRootItem();
    HTREEITEM hChildItem = m_MenuTree.GetChildItem(treeItem);
    m_MenuTree.Select(hChildItem, TVGN_CARET);
    return 0;
}
