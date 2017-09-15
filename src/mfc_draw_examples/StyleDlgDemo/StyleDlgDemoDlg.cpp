// StyleDlgDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StyleDlgDemo.h"
#include "StyleDlgDemoDlg.h"

#include "./src/Templates.h"

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


// CStyleDlgDemoDlg dialog

CStyleDlgDemoDlg::CStyleDlgDemoDlg(CWnd* pParent /*=NULL*/)
    : StyleDialog(CStyleDlgDemoDlg::IDD, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStyleDlgDemoDlg::DoDataExchange(CDataExchange* pDX)
{
    StyleDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_INNERFRAME, m_cInnerFrame);
    DDX_Control(pDX, IDC_DIALOG2, m_cDlg2Btn);
    DDX_Control(pDX, IDC_DIALOG3, m_cDlg3Btn);
}

BEGIN_MESSAGE_MAP(CStyleDlgDemoDlg, StyleDialog)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    //}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_DIALOG3, &CStyleDlgDemoDlg::OnBnClickedDialog3)
    ON_BN_CLICKED(IDC_DIALOG2, &CStyleDlgDemoDlg::OnBnClickedDialog2)
END_MESSAGE_MAP()


// CStyleDlgDemoDlg message handlers

BOOL CStyleDlgDemoDlg::OnInitDialog()
{
    // configure StyleDialog before calling the init function
    SetTransparent(TRUE);
    SetControls(ALL_CONTROLS);
    SetTitle(_T("Style Dialog Demo"));
    StyleDialog::OnInitDialog();
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
    CreateFrame();
    CreateButtons();
    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CStyleDlgDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX) {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    } else {
        StyleDialog::OnSysCommand(nID, lParam);
    }
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CStyleDlgDemoDlg::OnPaint()
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
        StyleDialog::OnPaint();
    }
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CStyleDlgDemoDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

void CStyleDlgDemoDlg::CreateFrame()
{
    CRect drect;
    GetFrameRect(drect);
    CRect crect;
    GetClientRect(crect);
    // the RaisedDlgFrame looks best with an odd sized border
    int width = 13;
    // the resource editor is at a lower dpi so set up things manually
    crect.top++;
    crect.left = drect.left + width;
    crect.right = drect.right - width;
    crect.bottom = drect.bottom - width;
    SetClientRect(crect);
    COLORREF base = RGB(14, 58, 145);
    COLORREF hlt = RGB(36, 225, 228);
    COLORREF bkgnd = RGB(0, 128, 128);
    CRect trect;
    GetTitleRect(trect);
    Stack Title(trect);
    Title.FillSolid(bkgnd);
    CString str(_T("Style Dialog"));
    Title.AddEffectString(str, CPoint(16, 11), OUTLINE, 28, FONT_BOLD, L"Old English Text MT",
                          base, Clr(140, hlt), 1);
    CRect xrect = crect;
    xrect.InflateRect(1, 1); // push anti-alias effect under the border
    Stack Client(xrect);
    // this will be the transparent region
    CRect irect;
    m_cInnerFrame.GetWindowRect(irect);
    irect.DeflateRect(width, width);
    Color shade = Clr(120, Black).value;
    int size = 24;
    Client.FillGrad3(irect, DIAGF, Clr(120, White), Clr(50, White), Clr(50, Black));
    Client.FillBar(irect, TOP_EDGE_BEVEL, size, shade, CLEAR);
    Client.FillBar(irect, LEFT_EDGE_BEVEL, size, shade, CLEAR);
    Client.FillBar(irect, RIGHT_EDGE_BEVEL, size, CLEAR, shade);
    Client.FillBar(irect, BOTTOM_EDGE_BEVEL, size, CLEAR, shade);
    int outer = Client.CreateRgn(xrect);
    int inner = Client.CreateRgn(irect);
    Client.CombineRgnModify(outer, inner, EXCLUDE);
    // fill all but inner frame
    Client.ApplyClipRgn(outer);
    Client.FillSolid(bkgnd);
    Client.RestoreClipRgn();
    RaisedFrame RF(irect, base, hlt, width);
    Client += RF.RFrame;
    // this supresses flashing associated with painting the
    // background on the non transparent regions
    SetTransparentRect(irect);
    RaisedDlgFrame RDF(drect, crect,  base, hlt, width);
    Style BackStyle;
    BackStyle.AddStack(Title);
    BackStyle.AddStack(Client);
    BackStyle.AddStack(RDF.DlgFrame);
    AddBackGroundStyle(BackStyle);
}

void CStyleDlgDemoDlg::CreateButtons()
{
    COLORREF bkgnd = RGB(14, 58, 145);
    COLORREF hlt = RGB(0x1f, 0xb8, 0xcf);
    COLORREF txt = RGB(36, 225, 228);
    CRect dlg2brc;
    m_cDlg2Btn.GetClientRect(dlg2brc);
    dlg2brc.right--;
    dlg2brc.bottom--;  // allow room for pressed state
    Stack dlg2btn(dlg2brc);
    dlg2btn.FillSolid(bkgnd);
    dlg2btn.SetOuterBorder(1, bkgnd);
    dlg2btn.SetShape(ROUNDRECT, 5);
    dlg2btn.FillBar(TOP_EDGE, 26, Clr(160, hlt), CLEAR);
    CString str1(_T("Dialog 2"));
    dlg2btn.AddAlignString(str1, ALIGN_CENTER, CPoint(0, 0), txt, 16, FONT_REG, L"Swiss");
    Style D2Btn;
    D2Btn.AddStack(dlg2btn);
    m_cDlg2Btn.LoadStdStyle(D2Btn);
    CRect dlg3brc;
    m_cDlg3Btn.GetClientRect(dlg3brc);
    dlg3brc.right--;
    dlg3brc.bottom--;  // allow room for pressed state
    Stack dlg3btn(dlg3brc);
    dlg3btn.FillSolid(bkgnd);
    dlg3btn.SetOuterBorder(1, bkgnd);
    dlg3btn.SetShape(ROUNDRECT, 5);
    dlg3btn.FillBar(TOP_EDGE, 26, Clr(160, hlt), CLEAR);
    CString str2(_T("Dialog 3"));
    dlg3btn.AddAlignString(str2, ALIGN_CENTER, CPoint(0, 0), txt, 16, FONT_REG, L"Swiss");
    Style D3Btn;
    D3Btn.AddStack(dlg3btn);
    m_cDlg3Btn.LoadStdStyle(D3Btn);
}

void CStyleDlgDemoDlg::OnBnClickedDialog3()
{
    // disable the parent transparency or it will burn through
    SetTransparent(FALSE);
    StyleDialog dlg(IDD_DIALOG3);
    dlg.SetTransparent(TRUE);
    dlg.SetTitle(_T("Standard Frame"));
    dlg.DoModal();
    // re-enable parent transparency
    SetTransparent(TRUE);
}

void CStyleDlgDemoDlg::OnBnClickedDialog2()
{
    // disable the parent transparency or it will burn through
    SetTransparent(FALSE);
    StyleDialog dlg(IDD_DIALOG2);
    dlg.SetControls(CTRL_CLIENT);
    dlg.SetTransparent(TRUE);
    dlg.SetTitle(_T("Transparent Frame"));
    dlg.SetOpaqueColor(Yellow);
    // if you don't want to bother deriving the dialog, just measure
    // the frame size and put it here
    CRect rect(0, 0, 419, 301);
    Stack Back(rect);
    Back.AddImage(CPoint(0, 0), IDR_DLG2TRANS, _T("PNG"));
    CString str(_T("Transparent Dialog"));
    Back.AddEffectString(str, CPoint(10, 10), OUTLINE, 24, FONT_BOLD, L"Old English Text MT",
                         Blue, Clr(15, White), 3);
    Style BackStyle;
    BackStyle.AddStack(Back);
    dlg.AddBackGroundStyle(BackStyle);
    Stack Opaque(rect);
    Opaque.AddImage(CPoint(0, 0), IDR_DLG2OPAQUE, _T("PNG"));
    Style OpaqueStyle;
    OpaqueStyle.AddStack(Opaque);
    dlg.AddOpaqueStyle(OpaqueStyle);
    dlg.DoModal();
    // re-enable parent transparency
    SetTransparent(TRUE);
    SetActiveWindow();
}
