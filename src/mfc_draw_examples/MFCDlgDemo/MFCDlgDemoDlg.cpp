// MFCDlgDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCDlgDemo.h"
#include "MFCDlgDemoDlg.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
    CAboutDlg();

// Dialog Data
    //{{AFX_DATA(CAboutDlg)
    enum { IDD = IDD_ABOUTBOX };
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CAboutDlg)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    //{{AFX_MSG(CAboutDlg)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
    //{{AFX_DATA_INIT(CAboutDlg)
    //}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CAboutDlg)
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
    //{{AFX_MSG_MAP(CAboutDlg)
    // No message handlers
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFCDlgDemoDlg dialog

CMFCDlgDemoDlg::CMFCDlgDemoDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CMFCDlgDemoDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CMFCDlgDemoDlg)
    m_nColorB = 0;
    m_nColorG = 0;
    m_nColorR = 0;
    m_nSize = 0;
    m_nSharpness = 5;
    m_nDarkness = 150;
    m_nPosX = 5;
    m_nPosY = 5;
    //}}AFX_DATA_INIT
    // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCDlgDemoDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CMFCDlgDemoDlg)
    DDX_Control(pDX, IDC_COLOR_R, m_ColorRCtrl);
    DDX_Control(pDX, IDC_COLOR_G, m_ColorGCtrl);
    DDX_Control(pDX, IDC_COLOR_B, m_ColorBCtrl);
    DDX_Control(pDX, IDC_SSIZE, m_SizeCtrl);
    DDX_Control(pDX, IDC_SHARPNESS, m_SharpnessCtrl);
    DDX_Control(pDX, IDC_DARKNESS, m_DarknessCtrl);
    DDX_Control(pDX, IDC_POSX, m_PosXCtrl);
    DDX_Control(pDX, IDC_POSY, m_PosYCtrl);
    DDX_Slider(pDX, IDC_COLOR_B, m_nColorB);
    DDX_Slider(pDX, IDC_COLOR_G, m_nColorG);
    DDX_Slider(pDX, IDC_COLOR_R, m_nColorR);
    DDX_Slider(pDX, IDC_SSIZE, m_nSize);
    DDX_Slider(pDX, IDC_SHARPNESS, m_nSharpness);
    DDX_Slider(pDX, IDC_DARKNESS, m_nDarkness);
    DDX_Slider(pDX, IDC_POSX, m_nPosX);
    DDX_Slider(pDX, IDC_POSY, m_nPosY);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMFCDlgDemoDlg, CDialog)
    //{{AFX_MSG_MAP(CMFCDlgDemoDlg)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_WM_HSCROLL()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFCDlgDemoDlg message handlers

BOOL CMFCDlgDemoDlg::OnInitDialog()
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
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);         // Set big icon
    SetIcon(m_hIcon, FALSE);        // Set small icon
    // TODO: Add extra initialization here
    m_ColorRCtrl.SetRange(0, 255, TRUE);
    m_ColorGCtrl.SetRange(0, 255, TRUE);
    m_ColorBCtrl.SetRange(0, 255, TRUE);
    m_SizeCtrl.SetRange(-20, 20, TRUE);
    m_SharpnessCtrl.SetRange(0, 20, TRUE);
    m_DarknessCtrl.SetRange(0, 255, TRUE);
    m_PosXCtrl.SetRange(-20, 20, TRUE);
    m_PosYCtrl.SetRange(-20, 20, TRUE);
    m_Shadow.Create(GetSafeHwnd());
    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCDlgDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCDlgDemoDlg::OnPaint()
{
    if (IsIconic()) {
        CPaintDC dc(this); // device context for painting
        SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCDlgDemoDlg::OnQueryDragIcon()
{
    return (HCURSOR) m_hIcon;
}

void CMFCDlgDemoDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    // TODO: Add your message handler code here and/or call default
    UpdateShadow();
    CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CMFCDlgDemoDlg::UpdateShadow(void)
{
    UpdateData();
    m_Shadow.SetSize(m_nSize);
    m_Shadow.SetSharpness(m_nSharpness);
    m_Shadow.SetDarkness(m_nDarkness);
    m_Shadow.SetPosition(m_nPosX, m_nPosY);
    m_Shadow.SetColor(RGB(m_nColorR, m_nColorG, m_nColorB));
}