// MainFrm.h : interface of the CMainFrame class
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__0B69D438_E080_420F_AD25_5F114C19B0D9__INCLUDED_)
#define AFX_MAINFRM_H__0B69D438_E080_420F_AD25_5F114C19B0D9__INCLUDED_

#if _MSC_VER >= 1000
    #pragma once
#endif // _MSC_VER >= 1000

class CMainFrame : public CFrameWindowImpl<CMainFrame>,
    public CUpdateUI<CMainFrame>,
    public CMessageFilter, public CIdleHandler
{
public:
    DECLARE_FRAME_WND_CLASS(NULL, IDR_MAINFRAME)

    // Construction
    CMainFrame();

    // Maps
    BEGIN_MSG_MAP(CMainFrame)
    MSG_WM_CREATE(OnCreate)
    MSG_WM_CLOSE(OnClose)
    MSG_WM_GETMINMAXINFO(OnGetMinmaxinfo)
    COMMAND_ID_HANDLER_EX(ID_APP_EXIT, OnFileExit)
    COMMAND_ID_HANDLER_EX(ID_VIEW_TOOLBAR, OnViewToolBar)
    COMMAND_ID_HANDLER_EX(ID_VIEW_STATUS_BAR, OnViewStatusBar)
    COMMAND_ID_HANDLER_EX(ID_APP_ABOUT, OnAppAbout)
    NOTIFY_CODE_HANDLER_EX(TBN_DROPDOWN, OnToolbarDropdown)
    CHAIN_CLIENT_COMMANDS()
    CHAIN_MSG_MAP(CUpdateUI<CMainFrame>)
    CHAIN_MSG_MAP(CFrameWindowImpl<CMainFrame>)
    END_MSG_MAP()

    BEGIN_UPDATE_UI_MAP(CMainFrame)
    UPDATE_ELEMENT(ID_VIEW_TOOLBAR, UPDUI_MENUPOPUP)
    UPDATE_ELEMENT(ID_VIEW_STATUS_BAR, UPDUI_MENUPOPUP)
    END_UPDATE_UI_MAP()

    // Message handlers
    BOOL    PreTranslateMessage(MSG* pMsg);
    BOOL    OnIdle();

    LRESULT OnCreate(LPCREATESTRUCT lpcs);
    void    OnClose();
    void    OnGetMinmaxinfo(LPMINMAXINFO lpmmi);

    // Command handlers
    void    OnFileExit(UINT uCode, int nID, HWND hwndCtrl);
    void    OnViewToolBar(UINT uCode, int nID, HWND hwndCtrl);
    void    OnViewStatusBar(UINT uCode, int nID, HWND hwndCtrl);
    void    OnAppAbout(UINT uCode, int nID, HWND hwndCtrl);

    // Notify handlers
    LRESULT OnToolbarDropdown(NMHDR* phdr);

protected:
    CKibblesView m_view;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__0B69D438_E080_420F_AD25_5F114C19B0D9__INCLUDED_)
