///////////////////////////////////////////////////////////////////////////
// TreeTestDlg.cpp : Implementation of Class TreeTestDlg
///////////////////////////////////////////////////////////////////////////
//
// Copyright(C) 2005 Jim Alsup  All rights reserved
//              email: ja.alsup@gmail.com
//
// License: This code is provided "as is" with no expressed or implied
//         warranty. You may use, or derive works from this file without
//          any restrictions except those listed below.
//
//        - This original header must be kept in the derived work.
//
//        - If your derived work is distributed in any form, you must
//          notify the author via the email address above and provide a
//          short description of the product and intended audience.
//
//        - You may not sell this code or a derived version of it as part of
//          a comercial code library.
//
//        - Offering the author a free licensed copy of any end product
//          using this code is not required, but does endear you with a
//          bounty of good karma.
//
///////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "VividTree.h"
#include "TreeTest.h"
#include "TreeTestDlg.h"
#include "Options.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
    CAboutDlg();

// Dialog Data
    enum { IDD = IDD_ABOUTBOX };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CTreeTestDlg dialog



CTreeTestDlg::CTreeTestDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CTreeTestDlg::IDD, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTreeTestDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TREETEST, m_tree);
}

BEGIN_MESSAGE_MAP(CTreeTestDlg, CDialog)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_WM_SIZE()
    //}}AFX_MSG_MAP
    ON_WM_ERASEBKGND()
    ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()


// CTreeTestDlg message handlers

BOOL CTreeTestDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
    // Add "About..." menu item to system menu.
    // IDM_ABOUTBOX must be in the system command range.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);
    CMenu* pSysMenu = GetSystemMenu(FALSE);

    if (pSysMenu != NULL) {
        CString strAboutMenu;
        strAboutMenu.LoadString(IDS_ABOUTBOX);

        if (!strAboutMenu.IsEmpty()) {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // Set the icon for this dialog.  The framework does this automatically
    // when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);         // Set big icon
    SetIcon(m_hIcon, FALSE);        // Set small icon
    // Setup VividTree BackGround bitmap (bitmap resource id)
    m_tree.SetBitmapID(IDB_CODE_PROJECT);
    // Override the default background mode to use a bitmap
    m_background_mode = VividTree::BK_MODE_BMP;
    m_tree.SetBkMode(m_background_mode);
    // Add a couple of pixels to the height (optional)
    // m_tree.SetItemHeight( m_tree.GetItemHeight() + 2 );
    // Setup a default tree leaf icon - in this case the code project alien is used
    m_icon = (HICON)LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_CODE_PROJECT),
                              IMAGE_ICON, 16, 16, LR_VGACOLOR);
    m_tree.SetItemIcon(m_icon);
    // Create the Tree content (fill in some dummy data).
    TV_INSERTSTRUCT TreeItem;
    TV_INSERTSTRUCT curTreeItem;
    HTREEITEM hParent;
    TreeItem.hParent = NULL;
    TreeItem.hInsertAfter = TVI_LAST ;
    TreeItem.itemex.mask = TVIF_TEXT | TVIF_CHILDREN;
    TreeItem.itemex.pszText = "Root Node 1";
    TreeItem.itemex.cChildren = 1;
    TreeItem.hParent = m_tree.InsertItem(&TreeItem);
    curTreeItem.hParent = TreeItem.hParent;
    curTreeItem.itemex.mask = TVIF_TEXT;
    curTreeItem.itemex.cChildren = 0;
    curTreeItem.hInsertAfter = TVI_FIRST;
    curTreeItem.itemex.pszText = "Child 1";
    m_tree.InsertItem(&curTreeItem);
    curTreeItem.itemex.pszText = "Child 2";
    m_tree.InsertItem(&curTreeItem);
    curTreeItem.itemex.pszText = "Parent A";
    curTreeItem.itemex.cChildren = 1;
    hParent = m_tree.InsertItem(&curTreeItem);
    curTreeItem.itemex.cChildren = 0;
    curTreeItem.hParent = hParent;
    curTreeItem.itemex.pszText = "Child A - with a long long name";
    m_tree.InsertItem(&curTreeItem);
    m_tree.Expand(TreeItem.hParent, TVE_EXPAND);
    m_tree.Expand(hParent, TVE_EXPAND);
    TreeItem.hParent = NULL;
    TreeItem.hInsertAfter = TVI_LAST;
    TreeItem.itemex.mask = TVIF_TEXT | TVIF_CHILDREN;
    TreeItem.itemex.pszText = "Root Node 2";
    TreeItem.itemex.cChildren = 1;
    TreeItem.hParent = m_tree.InsertItem(&TreeItem);
    curTreeItem.hParent = TreeItem.hParent;
    curTreeItem.itemex.pszText = "Child 1";
    m_tree.InsertItem(&curTreeItem);
    m_tree.Expand(TreeItem.hParent, TVE_EXPAND);
    // Cover the client area with the tree
    CRect rect;
    GetClientRect(rect);
    m_tree.MoveWindow(0, 0, rect.Width(), rect.Height());
    return TRUE;  // return TRUE  unless you set the focus to a control
}


void CTreeTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX) {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    } else {
        CDialog::OnSysCommand(nID, lParam);
    }
}


// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void CTreeTestDlg::OnPaint()
{
    if (IsIconic()) {
        CPaintDC dc(this); // device context for painting
        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;
        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    } else {
        CDialog::OnPaint();
    }
}


// The system calls this function to obtain the cursor to display while the user drags
// the minimized window.
HCURSOR CTreeTestDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}


void CTreeTestDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);

    if (!IsWindowVisible())
        return;

    // Size the tree to fit the whole window
    m_tree.MoveWindow(0, 0, cx, cy, TRUE);
}


BOOL CTreeTestDlg::OnEraseBkgnd(CDC* pDC)
{
    // Override to prevent flicker from drawing background
    return TRUE; // CDialog::OnEraseBkgnd(pDC);
}

void CTreeTestDlg::OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/)
{
    bool redraw_it = false;
    Options options;
    // WARNING: dialog radio buttons must in the same order as values defined
    // in the enum VividTree::BkMode.
    options.m_bkground_mode = (int)(m_tree.GetBkMode()) - (int)(m_tree.BK_MODE_BMP);
    options.m_tiled = m_tree.GetBitmapTiledMode();
    options.m_horz = m_tree.GetGradientHorz();

    if (options.DoModal() == IDOK) {
        // If any settings are different than they were, record the
        // new settings and redraw (invalidate).
        VividTree::BkMode new_mode = (VividTree::BkMode)(
                                         (int)(m_tree.BK_MODE_BMP) + options.m_bkground_mode);

        if (m_tree.GetBkMode() != new_mode) {
            m_tree.SetBkMode(new_mode);
            redraw_it = true;
        }

        if (m_tree.GetBitmapTiledMode() != (options.m_tiled ? true : false)) {
            m_tree.SetBitmapTiledMode((options.m_tiled ? true : false));
            redraw_it = true;
        }

        if (m_tree.GetGradientHorz() != (options.m_horz ? true : false)) {
            m_tree.SetGradientHorz((options.m_horz ? true : false));
            redraw_it = true;
        }

        if (redraw_it)
            Invalidate();  // redraw
    }
}
