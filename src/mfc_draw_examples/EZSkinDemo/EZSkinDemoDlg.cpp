// EZSkinDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EZSkinDemo.h"
#include "EZSkinDemoDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEZSkinDemoDlg dialog

CEZSkinDemoDlg::CEZSkinDemoDlg(CWnd* pParent /*=NULL*/)
	: CEZDialog(CEZSkinDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEZSkinDemoDlg)
	m_strCurSkin = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEZSkinDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CEZDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEZSkinDemoDlg)
	DDX_Control(pDX, IDC_LIST1, m_wndListBox);
	DDX_LBString(pDX, IDC_LIST1, m_strCurSkin);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEZSkinDemoDlg, CEZDialog)
	//{{AFX_MSG_MAP(CEZSkinDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelchangeList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEZSkinDemoDlg message handlers

BOOL CEZSkinDemoDlg::OnInitDialog()
{
	CEZDialog::OnInitDialog();

	m_Caption.SetIcon(m_hIcon);	

	LoadListBox();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CEZSkinDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
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
	}
	else
	{
		CEZDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CEZSkinDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CEZSkinDemoDlg::LoadListBox()
{

	m_wndListBox.AddString(_T("<Default>"));
	CEZSkinManager* pMan = GetSkinManager();
	CStringArray strar;
	int nSkins = pMan->EnumerateSkins(&strar);
	for(int nSkin = 0 ;nSkin < nSkins; nSkin++)
	 	m_wndListBox.AddString(strar[nSkin]);
	
	


}

CEZSkinManager* CEZSkinDemoDlg::GetSkinManager()
{

	return (CEZSkinManager*)((CEZSkinDemoApp*)AfxGetApp());
}

void CEZSkinDemoDlg::OnSelchangeList1() 
{

	UpdateData();
	CString strSkin;
	strSkin=m_strCurSkin == _T("<Default>")?_T(""):m_strCurSkin;
	GetSkinManager()->LoadSkin(strSkin);
	InvalidateRect(NULL);
	m_Caption.Refresh();
	m_Border.Refresh();
}
