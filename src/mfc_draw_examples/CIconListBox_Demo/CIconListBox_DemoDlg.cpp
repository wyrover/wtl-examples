// CIconListBox_DemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CIconListBox_Demo.h"
#include "CIconListBox_DemoDlg.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
#endif


// CCIconListBox_DemoDlg dialog




CCIconListBox_DemoDlg::CCIconListBox_DemoDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CCIconListBox_DemoDlg::IDD, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCIconListBox_DemoDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_listbox);
}

BEGIN_MESSAGE_MAP(CCIconListBox_DemoDlg, CDialog)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    //}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BUTTON3, &CCIconListBox_DemoDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CCIconListBox_DemoDlg message handlers

BOOL CCIconListBox_DemoDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);         // Set big icon
    SetIcon(m_hIcon, FALSE);        // Set small icon
    // TODO: Add extra initialization here
    m_listbox.AddString(TEXT("123"), IDI_ICON_1);
    m_listbox.AddString(TEXT("456"), IDI_ICON_2);
    m_listbox.AddString(TEXT("789"), IDI_ICON_1);
    return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCIconListBox_DemoDlg::OnPaint()
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
HCURSOR CCIconListBox_DemoDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}
void CCIconListBox_DemoDlg::OnBnClickedButton3()
{
    // TODO: Add your control notification handler code here
    m_listbox.AddString(TEXT("hisin"), IDI_ICON_1);
}
