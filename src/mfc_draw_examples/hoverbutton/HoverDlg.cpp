// HoverDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Hover.h"
#include "HoverDlg.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHoverDlg dialog

CHoverDlg::CHoverDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CHoverDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CHoverDlg)
    // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHoverDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CHoverDlg)
    DDX_Control(pDX, IDC_HOVERBUTTON, m_HoverButton);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHoverDlg, CDialog)
    //{{AFX_MSG_MAP(CHoverDlg)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_HOVERBUTTON, OnHoverbutton)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHoverDlg message handlers

BOOL CHoverDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
    SetIcon(m_hIcon, TRUE);         // Set big icon
    SetIcon(m_hIcon, FALSE);        // Set small icon
    // TODO: Add extra initialization here
    m_HoverButton.LoadBitmap(IDB_HOVERBUTTON);
    CString text = _T("Click me!");
    m_HoverButton.SetToolTipText(&text);
    return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CHoverDlg::OnPaint()
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

HCURSOR CHoverDlg::OnQueryDragIcon()
{
    return (HCURSOR) m_hIcon;
}

void CHoverDlg::OnHoverbutton()
{
    // TODO: Add your control notification handler code here
    AfxMessageBox(TEXT("Hello Hello.\n"));
}
