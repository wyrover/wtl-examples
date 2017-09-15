// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__846BA7EE_847B_11D6_B650_0020780D200B__INCLUDED_)
#define AFX_MAINFRM_H__846BA7EE_847B_11D6_B650_0020780D200B__INCLUDED_

#if _MSC_VER >= 1000
    #pragma once
#endif // _MSC_VER >= 1000

#include "DemoTabViewCtrl.h"
#include "StylesDlg.h"


//==============================================================================
/**
 *      @class CMainFrame   The main frame window for the demo application
 *
 *      This class manages the menus for the main frame.
 */
//==============================================================================
class CMainFrame :
    public CFrameWindowImpl<CMainFrame>,
    public CUpdateUI<CMainFrame>,
    public CMessageFilter,
    public CIdleHandler,
    public CStylesDlg::CStylesBridge
{
    //==============================================================================
    //  Fields
    //==============================================================================

protected:

    CDemoTabViewCtrl    m_TabViewDemo;      ///< The demonstration window
    CCommandBarCtrl     m_CmdBar;
    CImageList          m_ImageList;        ///< The image list to associate with the tab ctrl
    LONG                m_TotalTabCount;    ///< The count of total tabs created


    //==============================================================================
    //  WTL
    //==============================================================================

public:

    DECLARE_FRAME_WND_CLASS(NULL, IDR_MAINFRAME)

    virtual BOOL PreTranslateMessage(MSG* pMsg)
    {
        if (CFrameWindowImpl<CMainFrame>::PreTranslateMessage(pMsg))
            return TRUE;

        return m_TabViewDemo.PreTranslateMessage(pMsg);
    }

    virtual BOOL OnIdle()
    {
        UIUpdateToolBar();
        return FALSE;
    }

    BEGIN_MSG_MAP(CMainFrame)
    MESSAGE_HANDLER(WM_CREATE, OnCreate)
    COMMAND_ID_HANDLER(ID_APP_EXIT, OnFileExit)
    COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
    COMMAND_ID_HANDLER(ID_DEMO_REMOVETAB, OnDemoRemoveTab)
    COMMAND_ID_HANDLER(ID_DEMO_REMOVEALLTABS, OnDemoRemoveAllTabs)
    COMMAND_ID_HANDLER(ID_DEMO_STYLES, OnStylesDlg)
    COMMAND_RANGE_HANDLER(ID_DEMO_ADDTAB, ID_DEMO_ADDTAB2, OnDemoAddTab)
    REFLECT_NOTIFICATIONS()
    CHAIN_MSG_MAP(CUpdateUI<CMainFrame>)
    CHAIN_MSG_MAP(CFrameWindowImpl<CMainFrame>)
    END_MSG_MAP()

    BEGIN_UPDATE_UI_MAP(CMainFrame)
    UPDATE_ELEMENT(ID_VIEW_TOOLBAR, UPDUI_MENUPOPUP)
    UPDATE_ELEMENT(ID_VIEW_STATUS_BAR, UPDUI_MENUPOPUP)
    END_UPDATE_UI_MAP()

    //==============================================================================
    //  Methods
    //==============================================================================

public:

    CMainFrame() : m_TotalTabCount(1)
    {
    }

    LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        // create command bar window
        HWND hWndCmdBar = m_CmdBar.Create(m_hWnd, rcDefault, NULL, ATL_SIMPLE_CMDBAR_PANE_STYLE);
        // attach menu
        m_CmdBar.AttachMenu(GetMenu());
        // load command bar images
        m_CmdBar.LoadImages(IDR_MAINFRAME);
        // remove old menu
        SetMenu(NULL);
        CreateSimpleReBar(ATL_SIMPLE_REBAR_NOBORDER_STYLE);
        AddSimpleReBarBand(hWndCmdBar);
        CreateSimpleStatusBar();
        //TODO: Replace with a URL of your choice
        m_hWndClient = m_TabViewDemo.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE, WS_EX_STATICEDGE);
        m_ImageList.Create(IDB_TABBITMAP, 16, 1, RGB(0, 255, 0));
        m_TabViewDemo.SetImageList(m_ImageList);
        m_TabViewDemo.AddHelpTab();
        // register object for message filtering and idle updates
        CMessageLoop* pLoop = _Module.GetMessageLoop();
        ATLASSERT(pLoop != NULL);
        pLoop->AddMessageFilter(this);
        pLoop->AddIdleHandler(this);
        return 0;
    }

    LRESULT OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        PostMessage(WM_CLOSE);
        return 0;
    }

    LRESULT OnDemoAddTab(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        CString theTabName;
        theTabName.Format("Tab %ld", m_TotalTabCount++);

        switch (wID) {
        case ID_DEMO_ADDTAB: {
            m_TabViewDemo.AddDemoView1Tab(theTabName);
            break;
        }

        case ID_DEMO_ADDTAB2: {
            m_TabViewDemo.AddDemoView2Tab(theTabName);
            break;
        }
        };

        return 0;
    }

    LRESULT OnDemoRemoveTab(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        m_TabViewDemo.RemoveTab(m_TabViewDemo.GetActiveTabIndex());
        return 0;
    }

    LRESULT OnDemoRemoveAllTabs(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        m_TabViewDemo.RemoveAllTabs();
        return 0;
    }

    LRESULT OnStylesDlg(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        CStylesDlg dlg(m_TabViewDemo.GetStyle(), this);
        dlg.DoModal();
        return 0;
    }

    LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        CAboutDlg dlg;
        dlg.DoModal();
        return 0;
    }

    virtual void OnStyleApply(ULONG inAddStyleBits, ULONG inRemoveStyleBits, ULONG* outNewStyleBits)
    {
        m_TabViewDemo.ModifyTabStyle(inRemoveStyleBits, inAddStyleBits, SWP_NOACTIVATE);
        *outNewStyleBits = m_TabViewDemo.GetStyle();
    }
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__846BA7EE_847B_11D6_B650_0020780D200B__INCLUDED_)
