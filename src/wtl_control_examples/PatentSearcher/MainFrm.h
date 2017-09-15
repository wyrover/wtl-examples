// MainFrm.h : interface of the CMainFrame class
//
// author: luckey_sun
// email : sunlaibing88@gmail.com
// date  : 2011.12.31
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <map>
#include <set>
using namespace std;

// #include "MySplitterWindowT.h"
// //#include "ClipSpyListCtrl.h"
// #include "MyPaneContainer.h"
// #include "TreeCtrl.h"
// #include "controls.h"
#include "downloadlistdlg.h"
#include "infolistdlg.h"
#include "searchlistdlg.h"
#include "myfunction.h"


class CMainFrame : public CFrameWindowImpl<CMainFrame>, public CUpdateUI<CMainFrame>,
    public CMessageFilter, public CIdleHandler
{
public:
    DECLARE_FRAME_WND_CLASS(NULL, IDR_MAINFRAME)

    virtual BOOL PreTranslateMessage(MSG* pMsg);
    virtual BOOL OnIdle();

    BEGIN_UPDATE_UI_MAP(CMainFrame)
    UPDATE_ELEMENT(ID_VIEW_TOOLBAR, UPDUI_MENUPOPUP)
    UPDATE_ELEMENT(ID_VIEW_STATUS_BAR, UPDUI_MENUPOPUP)
    UPDATE_ELEMENT(1, UPDUI_STATUSBAR)  // defaut status
    UPDATE_ELEMENT(2, UPDUI_STATUSBAR)  // datasource indicator
    UPDATE_ELEMENT(3, UPDUI_STATUSBAR)  // search time
    UPDATE_ELEMENT(4, UPDUI_STATUSBAR)  // status indicator
    END_UPDATE_UI_MAP()

    BEGIN_MSG_MAP(CMainFrame)
    MESSAGE_HANDLER(WM_CREATE, OnCreate)
    MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
    NOTIFY_CODE_HANDLER(TVN_SELCHANGED, OnSelChanged)
    NOTIFY_CODE_HANDLER(NM_RCLICK, OnNMRClickList)
    NOTIFY_HANDLER(IDC_LEFT_TREEVIEW, TVN_BEGINLABELEDIT, OnTvnBeginlabeleditTree)
    NOTIFY_HANDLER(IDC_LEFT_TREEVIEW, TVN_ENDLABELEDIT, OnTvnEndlabeleditTree)
    COMMAND_ID_HANDLER(ID_APP_EXIT, OnFileExit)
    COMMAND_ID_HANDLER(ID_FILE_NEW, OnFileNew)
    COMMAND_ID_HANDLER(ID_VIEW_TOOLBAR, OnViewToolBar)
    COMMAND_ID_HANDLER(ID_VIEW_STATUS_BAR, OnViewStatusBar)
    COMMAND_ID_HANDLER(ID_VIEW_TREE, OnViewTree)
    COMMAND_ID_HANDLER(ID_VIEW_DOWNLOAD, OnViewDownLoad)
    COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
    COMMAND_ID_HANDLER(ID_NET_SEARCH, OnNetSearch)
    COMMAND_ID_HANDLER(ID_LOCAL_SEARCH, OnLocalSearch)


//         COMMAND_ID_HANDLER(ID_SEARCH_PREV, OnSearchPrev)
//         COMMAND_ID_HANDLER(ID_SEARCH_NEXT, OnSearchNext)

    MESSAGE_HANDLER(WM_SEARCH_PREVPAGE, OnSearchPrev)                           //上一页
    MESSAGE_HANDLER(WM_SEARCH_NEXTPAGE, OnSearchNext)                           //下一页
    MESSAGE_HANDLER(WM_SEARCH_FIRSTPAGE, OnSearchFirst)                         //下一页

    COMMAND_ID_HANDLER(ID_TREE_CRAETE, OnCreateLabel)                           //创建标签
    COMMAND_ID_HANDLER(ID_TREE_DEL, OnDeleteLabel)                              //删除标签
    COMMAND_ID_HANDLER(ID_TREE_EDIT, OnEditLabel)                               //修改标签名称


    CHAIN_MSG_MAP(CUpdateUI<CMainFrame>)
    CHAIN_MSG_MAP(CFrameWindowImpl<CMainFrame>)
    REFLECT_NOTIFICATIONS()             /*handle TVN_SELCHANGED etc.*/
//      DEFAULT_REFLECTION_HANDLER()
    END_MSG_MAP()
    /************************************************************************/
    /* 在父窗口中定义了REFLECT_NOTIFICATIONS(),
    则必须在子控件的消息映射到最后加上 DEFAULT_REFLECTION_HANDLER();否则会出错。
    */
    /************************************************************************/
    CMainFrame();

// Handler prototypes (uncomment arguments if needed):
//  LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//  LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//  LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

    LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);
    LRESULT OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnFileNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnViewToolBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnViewStatusBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnViewTree(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnViewDownLoad(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnNetSearch(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnLocalSearch(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

    LRESULT OnDownloadPdf(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnOpenPdf(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnDeletePdf(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnInfoReloadPdf(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnSelChanged(int idCtrl, LPNMHDR pNMHDR, BOOL& bHandled);
    LRESULT OnNMRClickList(int idCtrl, LPNMHDR pNMHDR, BOOL& bHandled);

    void InitLeftTreeView(CTreeViewCtrlEx *m_pTreeView);
    void FindNode(CTreeItem h_parent, CString str);
    LRESULT OnTvnBeginlabeleditTree(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/);
    LRESULT OnTvnEndlabeleditTree(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/);
    void InitListView(CListViewCtrl *m_pListView, int nType);


//  LRESULT OnSearchPrev(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
//  LRESULT OnSearchNext(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

    LRESULT OnSearchFirst(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

    LRESULT OnSearchPrev(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnSearchNext(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);


    LRESULT OnCreateLabel(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        return 0;
    }
    LRESULT OnDeleteLabel(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        return 0;
    }
    LRESULT OnEditLabel(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        return 0;
    }

protected:
    //先垂直分割，后水平分割
    CSplitterWindow m_wndVertSplitter;
    CHorSplitterWindow m_wndHorzSplitter;
    CSplitterWindow m_TopVertSplitter;
    CSplitterWindow m_BottomVertSplitter;
    CHorSplitterWindow m_TopHorzSplitter;

//  CMySplitterWindowT<true> m_wndVertSplitter;
//  CMySplitterWindowT<false> m_wndHorzSplitter;

//  CMyPaneContainer m_wndTreeContainer;
//  CMyPaneContainer m_wndIEContainer;


    CImageList m_LeftTreeImageList;
    CImageList m_StatusListImageList;

    CTreeViewCtrlEx m_MenuTree;         //左边树形菜单
    CAxWindow m_MainWebBrowser;                 //初始介绍界面
    CAxWindow m_InfoWebBrowser;                 //专利详细信息介绍
    CAxWindow testdlg;

    CListViewCtrl m_InfoListView;
    CListViewCtrl m_DownloadListView;
    CListViewCtrl m_SearchListView;
    CDownloadListDlg m_downloadListDlg;
    CSearchListDlg m_searchListDlg;
    CInfoListDlg m_infoListDlg;

    CMultiPaneStatusBarCtrl m_wndStatusBar;

    CString currentPath;
    LRunSql m_runsql;
};
