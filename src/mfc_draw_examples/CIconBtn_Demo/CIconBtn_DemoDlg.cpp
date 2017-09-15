// CIconBtn_DemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CIconBtn_Demo.h"
#include "CIconBtn_DemoDlg.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
#endif


// CCIconBtn_DemoDlg dialog




CCIconBtn_DemoDlg::CCIconBtn_DemoDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CCIconBtn_DemoDlg::IDD, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCIconBtn_DemoDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_BUTTON1, m_btn1);
    DDX_Control(pDX, IDC_BUTTON2, m_btn2);
    DDX_Control(pDX, IDC_BUTTON3, m_btn3);
    DDX_Control(pDX, IDC_BUTTON4, m_btn4);
}

BEGIN_MESSAGE_MAP(CCIconBtn_DemoDlg, CDialog)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    //}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BUTTON5, &CCIconBtn_DemoDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CCIconBtn_DemoDlg message handlers

BOOL CCIconBtn_DemoDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);         // Set big icon
    SetIcon(m_hIcon, FALSE);        // Set small icon
    // TODO: Add extra initialization here
    m_btn1.SetIcon(IDI_ICON_TEST);
    m_btn1.SetAlign(CIconBtn::IBTN_ICON_LEFT_TEXT_RIGHT);
    m_btn2.SetIcon(IDI_ICON_TEST);
    m_btn2.SetAlign(CIconBtn::IBTN_ICON_RIGHT_TEXT_LEFT);
    m_btn3.SetIcon(IDI_ICON_TEST);
    m_btn3.SetAlign(CIconBtn::IBTN_ICON_TOP_TEXT_BOTTOM);
    m_btn4.SetIcon(IDI_ICON_TEST);
    m_btn4.SetAlign(CIconBtn::IBTN_ICON_BOTTOM_TEXT_TOP);
    return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCIconBtn_DemoDlg::OnPaint()
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
//  the minimized window.
HCURSOR CCIconBtn_DemoDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}


void CCIconBtn_DemoDlg::OnBnClickedButton5()
{
    // TODO: Add your control notification handler code here
    m_btn4.SetIcon(IDI_ICON1, 48, 48);
    m_btn4.Invalidate();
}
