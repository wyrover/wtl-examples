// mylistboxDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mylistbox.h"
#include "mylistboxDlg.h"

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
// CMylistboxDlg dialog

CMylistboxDlg::CMylistboxDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMylistboxDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMylistboxDlg)
	m_item = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMylistboxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMylistboxDlg)
	DDX_Control(pDX, IDC_LIST1, m_listbox);
	DDX_Text(pDX, IDC_EDIT1, m_item);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMylistboxDlg, CDialog)
	//{{AFX_MSG_MAP(CMylistboxDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMylistboxDlg message handlers

BOOL CMylistboxDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here


	m_listbox.AddString("I like shanghai");
	m_listbox.AddString("I like VCKBASE");
	m_listbox.AddString("I like china");
	m_listbox.AddString("I like c++");
	m_listbox.AddString("I like VC++");
	m_listbox.AddString("I like shanghai");
	m_listbox.AddString("I like VCKBASE");
	m_listbox.AddString("I like china");
	m_listbox.AddString("I like c++");
	m_listbox.AddString("I like VC++");
	m_listbox.AddString("I like shanghai");	
	m_listbox.AddString("I like VCKBASE");
	m_listbox.AddString("I like china");
	m_listbox.AddString("I like c++");
	m_listbox.AddString("I like xml");
	m_listbox.AddString("I like shanghai");
	m_listbox.AddString("who u r");
	m_listbox.AddString("who am I");

	iStatus = 0 ; // µÚÒ»·ùÍ¼£»
	m_listbox.GetClientRect(&size1);
	
	size2.right = size3.right= size1.right;
	size2.bottom = size3.bottom = size1.bottom;
	HBITMAP htempbmp;
	m_listbox.m_bmp.LoadBitmap(IDB_BITMAP2);

	
	hbmp = (HBITMAP )m_listbox.m_bmp.Detach();
	htempbmp = GetSizeBITMAP(hbmp , size1.right,size1.bottom);
	m_listbox.m_bmp.Attach(htempbmp); 

	bmp.LoadBitmap(IDB_BITMAP1);
	hbmp2 =(HBITMAP ) bmp.Detach();
	hbmp2 = GetSizeBITMAP(hbmp2 , size1.right,size1.bottom);

	m_listbox.Invalidate();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMylistboxDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}



void CMylistboxDlg::OnPaint() 
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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMylistboxDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMylistboxDlg::OnButton1() 
{
	iStatus = 1 - iStatus;
	if(iStatus==0)
	{
	m_listbox.GetClientRect(&size2);
	HBITMAP htempbmp;
	htempbmp = GetSizeBITMAP(hbmp , size2.right ,size2.bottom);
	m_listbox.m_bmp.Detach();
	m_listbox.m_bmp.Attach(htempbmp); 

	size1.right = size2.right;
	size1.bottom = size2.bottom;

	Invalidate(TRUE);
	}
else
{	
	m_listbox.GetClientRect(&size3);
	HBITMAP htempbmp;
	htempbmp = GetSizeBITMAP(hbmp2 , size3.right ,size3.bottom);
	m_listbox.m_bmp.Detach();
	m_listbox.m_bmp.Attach(htempbmp); 

	size1.right = size3.right;
	size1.bottom = size3.bottom;
	Invalidate(TRUE);
}
}

void CMylistboxDlg::OnButton2() 
{

	UpdateData(TRUE);
	if(!strlen(m_item))
		return;
	m_listbox.AddString(m_item);
	Refresh();
}

void CMylistboxDlg::OnButton3() 
{

   for (int i=0;i < m_listbox.GetCount();i++)
   {
     if(m_listbox.GetSel( i ))
		m_listbox.DeleteString(i);
   }
	Refresh();
}

void CMylistboxDlg::OnButton4() 
{
   for (int i=m_listbox.GetCount()-1; i >=0 ; i--)
   {
		m_listbox.DeleteString(i);
   }
	Refresh();	
}

void CMylistboxDlg::Refresh()
{

	if(iStatus==0)
	{
	m_listbox.GetClientRect(&size2);
	if(size2.right==size1.right& size2.bottom==size1.bottom)
	return;
	else

	{	
	HBITMAP htempbmp;
	htempbmp = GetSizeBITMAP(hbmp , size2.right ,size2.bottom);
	m_listbox.m_bmp.Detach();
	m_listbox.m_bmp.Attach(htempbmp); 

	size1.right = size2.right;
	size1.bottom = size2.bottom;

	Invalidate(TRUE);
	}
}
else
{	


	m_listbox.GetClientRect(&size3);
	if(size3.right==size1.right& size3.bottom==size1.bottom)
	return;
	else
	{	
	HBITMAP htempbmp;
	htempbmp = GetSizeBITMAP(hbmp2 , size3.right ,size3.bottom);
	m_listbox.m_bmp.Detach();
	m_listbox.m_bmp.Attach(htempbmp); 

	size1.right = size3.right;
	size1.bottom = size3.bottom;
	Invalidate(TRUE);
	}
}

}











HBITMAP CMylistboxDlg::GetSizeBITMAP(HBITMAP hBitmap, int w, int h)
{
	CDC sourceDC, destDC;
	sourceDC.CreateCompatibleDC( NULL );
	destDC.CreateCompatibleDC( NULL );
	BITMAP bm;
	::GetObject( hBitmap, sizeof( bm ), &bm );
	HBITMAP hbmResult = ::CreateCompatibleBitmap(CClientDC(NULL), w, h);
	HBITMAP hbmOldSource = (HBITMAP)::SelectObject( sourceDC.m_hDC, hBitmap );
	HBITMAP hbmOldDest = (HBITMAP)::SelectObject( destDC.m_hDC, hbmResult );
	destDC.BitBlt(0, 0, w, h, &sourceDC, 0, 0, SRCCOPY );
	::SelectObject( sourceDC.m_hDC, hbmOldSource );
	::SelectObject( destDC.m_hDC, hbmOldDest );
	return hbmResult;
}


