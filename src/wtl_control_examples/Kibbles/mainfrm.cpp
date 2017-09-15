// MainFrm.cpp : implmentation of the CMainFrame class
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "kibbles.h"
#include "KibblesView.h"
#include "aboutdlg.h"
#include "MainFrm.h"

//////////////////////////////////////////////////////////////////////
// Construction

CMainFrame::CMainFrame()
{
}


//////////////////////////////////////////////////////////////////////
// Message handlers

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
    if (CFrameWindowImpl<CMainFrame>::PreTranslateMessage(pMsg))
        return TRUE;

    return m_view.PreTranslateMessage(pMsg);
}

BOOL CMainFrame::OnIdle()
{
    UIUpdateToolBar();
    return FALSE;
}

LRESULT CMainFrame::OnCreate(LPCREATESTRUCT lpcs)
{
    CreateSimpleToolBar();
    CreateSimpleStatusBar();
    CToolBarCtrl tb = m_hWndToolBar;
    TBBUTTONINFO tbbi = { sizeof(TBBUTTONINFO), TBIF_STYLE };
    tb.SetButtonStructSize();
    tb.GetButtonInfo(IDC_CHOOSE_BKGND_BMP, &tbbi);
    tbbi.fsStyle |= BTNS_WHOLEDROPDOWN;
    tb.SetButtonInfo(IDC_CHOOSE_BKGND_BMP, &tbbi);
    m_hWndClient = m_view.Create(m_hWnd, rcDefault, NULL,
                                 WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS |
                                 WS_CLIPCHILDREN, WS_EX_CLIENTEDGE);
    UIAddToolBar(m_hWndToolBar);
    UISetCheck(ID_VIEW_TOOLBAR, 1);
    UISetCheck(ID_VIEW_STATUS_BAR, 1);
    // register object for message filtering and idle updates
    CMessageLoop* pLoop = _Module.GetMessageLoop();
    ATLASSERT(pLoop != NULL);
    pLoop->AddMessageFilter(this);
    pLoop->AddIdleHandler(this);
    return 0;
}

void CMainFrame::OnClose()
{
    if (!m_view.AllowClose())
        return;

    SetMsgHandled(false);
}

void CMainFrame::OnGetMinmaxinfo(LPMINMAXINFO lpmmi)
{
    lpmmi->ptMinTrackSize.x = 350;
    lpmmi->ptMinTrackSize.y = 400;
}


//////////////////////////////////////////////////////////////////////
// Command handlers

void CMainFrame::OnFileExit(UINT uCode, int nID, HWND hwndCtrl)
{
    PostMessage(WM_CLOSE);
}

void CMainFrame::OnViewToolBar(UINT uCode, int nID, HWND hwndCtrl)
{
    BOOL bVisible = !::IsWindowVisible(m_hWndToolBar);
    ::ShowWindow(m_hWndToolBar, bVisible ? SW_SHOWNOACTIVATE : SW_HIDE);
    UISetCheck(ID_VIEW_TOOLBAR, bVisible);
    UpdateLayout();
}

void CMainFrame::OnViewStatusBar(UINT uCode, int nID, HWND hwndCtrl)
{
    BOOL bVisible = !::IsWindowVisible(m_hWndStatusBar);
    ::ShowWindow(m_hWndStatusBar, bVisible ? SW_SHOWNOACTIVATE : SW_HIDE);
    UISetCheck(ID_VIEW_STATUS_BAR, bVisible);
    UpdateLayout();
}

void CMainFrame::OnAppAbout(UINT uCode, int nID, HWND hwndCtrl)
{
    CAboutDlg dlg;
    dlg.DoModal();
}


//////////////////////////////////////////////////////////////////////
// Notify handlers

LRESULT CMainFrame::OnToolbarDropdown(NMHDR* phdr)
{
    NMTOOLBAR* pnmtb = (NMTOOLBAR*) phdr;
    HRESULT hr;
    CMenu menu;
    CMenuHandle popup;
    TCHAR szMyPicsDir[MAX_PATH];

    // Verify that this notification is being sent by the button that we expect.
    if (IDC_CHOOSE_BKGND_BMP != pnmtb->iItem) {
        ATLTRACE(_T("Warning: TBN_DROPDOWN received for an unknown button ID: %d\n"), pnmtb->iItem);
        return TBDDRET_DEFAULT;
    }

    // Load the menu that we'll show in response to the button click.
    if (!menu.LoadMenu(IDR_SELECT_PICTURE)) {
        ATLTRACE(_T("Error: LoadMenu() failed in OnToolbarDropdown(), error: %s\n"), _E2());
        return TBDDRET_DEFAULT;
    }

    popup = menu.GetSubMenu(0);

    if (!popup) {
        ATLTRACE(_T("Error: GetSubMenu() failed in OnToolbarDropdown()\n"));
        return TBDDRET_DEFAULT;
    }

    // Get the path to the My Pictures dir.
    hr = SHGetFolderPath(NULL, CSIDL_MYPICTURES, NULL, SHGFP_TYPE_CURRENT, szMyPicsDir);

    if (FAILED(hr)) {
        ATLTRACE(_T("Error: SHGetFolderPath() failed in OnToolbarDropdown(), error: %s\n"), _E(hr));
        return TBDDRET_DEFAULT;
    }

    PathAddBackslash(szMyPicsDir);
    // Find all *.BMP files in the My Pictures dir.
    CFindFile finder;
    UINT uID = 10000;
    CString sPattern = szMyPicsDir;
    sPattern += _T("*.bmp");

    if (finder.FindFile(sPattern)) {
        popup.AppendMenu(MF_SEPARATOR);

        do {
            // Skip any directories we find, as well as "offline" files. Those
            // are files that have been backed up to other storage like tape,
            // and we don't want to fault those back onto the local machine.
            if (!finder.IsDirectory() && !finder.MatchesMask(FILE_ATTRIBUTE_OFFLINE))
                popup.AppendMenu(MF_STRING, uID++, finder.GetFileName());
        } while (finder.FindNextFile());
    }

    // Get the location of the bottom-left corner of the button.
    CPoint pt(pnmtb->rcButton.left, pnmtb->rcButton.bottom);
    ::ClientToScreen(m_hWndToolBar, &pt);
    // Show the popup menu.
    UINT uSelID;
    uSelID = (UINT) popup.TrackPopupMenu(TPM_RETURNCMD, pt.x, pt.y, *this);

    if (0 != uSelID) {
        if (IDC_NO_PICTURE == uSelID) {
            m_view.SetNoBackgroundPicture();
        } else if (IDC_DEFAULT_PICTURE == uSelID) {
            m_view.UseDefaultBackgroundPicture();
        } else if (uSelID >= 10000 && uSelID < uID) {
            CString sBmpName;
            popup.GetMenuString(uSelID, sBmpName, MF_BYCOMMAND);
            sBmpName = szMyPicsDir + sBmpName;
            m_view.SetBackgroundPicture(sBmpName);
        }
    }

    return TBDDRET_DEFAULT;
}
