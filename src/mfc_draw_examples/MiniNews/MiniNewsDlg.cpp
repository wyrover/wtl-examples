
// MiniNewsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MiniNews.h"
#include "MiniNewsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMiniNewsDlg 对话框




CMiniNewsDlg::CMiniNewsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMiniNewsDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMiniNewsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER1, m_webBrowser);
}

BEGIN_MESSAGE_MAP(CMiniNewsDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_NCPAINT()
	ON_WM_ACTIVATE()
	ON_WM_NCMOUSEMOVE()
	ON_WM_SYSCOMMAND()
	ON_WM_NCLBUTTONUP()
	//ON_WM_NCMOUSELEAVE()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_CTLCOLOR()


	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CMiniNewsDlg 消息处理程序
// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMiniNewsDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	CRect   rect;
	GetClientRect(&rect);
	//设置对话框背景颜色
	dc.FillSolidRect(rect,m_bkColor);   //设置为窗口背景
	DrawDialog();
	// 不为绘图消息调用 CDialog::OnPaint()
}
BOOL CMiniNewsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	//ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	//ASSERT(IDM_ABOUTBOX < 0xF000);

	//CMenu* pSysMenu = GetSystemMenu(FALSE);
	//if (pSysMenu != NULL)
	//{
	//	BOOL bNameValid;
	//	CString strAboutMenu;
	//	bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
	//	ASSERT(bNameValid);
	//	if (!strAboutMenu.IsEmpty())
	//	{
	//		pSysMenu->AppendMenu(MF_SEPARATOR);
	//		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	//	}
	//}

	//// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	////  执行此操作
	//SetIcon(m_hIcon, TRUE);			// 设置大图标
	//SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_bkColor = RGB(20,120,200);
	m_bMouseOnMinBtn = FALSE;
	m_bMouseOnCloseBtn =FALSE;
	m_strTitle = "迷你资讯网";
	// TODO: 在此添加额外的初始化代码
	this->SetWindowText("迷你资讯网");
	this->m_webBrowser.Navigate("http://mini.37zone.com/miniportal/client/default/1.2.0.0/",NULL,NULL,NULL,NULL);
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMiniNewsDlg::DrawDialog()
{
	m_nFrameCY = GetSystemMetrics(SM_CYFIXEDFRAME);//获取对话框边框的高度
	m_nFrameCX = GetSystemMetrics(SM_CXDLGFRAME);//获取对话边框的宽度
	if(GetStyle()&WS_BORDER)//获取对话框是否有边框
	{
		m_nBorderCY = GetSystemMetrics(SM_CYBORDER) + m_nFrameCY;
		m_nBorderCX = GetSystemMetrics(SM_CXBORDER) +m_nFrameCX; 
	}
	else
	{		
		m_nBorderCY = m_nFrameCY;
		m_nBorderCX = m_nFrameCX;
	}
	m_nTitleBarCY = GetSystemMetrics(SM_CYCAPTION) + m_nBorderCY;//计算标题栏高度
	m_nTitleBarCX =m_nBorderCX;

	CRect winRect,factRect;
	GetWindowRect(&winRect);
	factRect.CopyRect(CRect(0,0,winRect.Width(),winRect.Height()));
	CWindowDC windowsDC(this);//获取窗口设备上下文
	//获取整个MFC窗口的高度和宽度
	m_nWinWidth = winRect.Width();
	m_nWinHeight = winRect.Height();
	//绘制对话框标题栏位图	
	DisplayBmp(0,0,m_nWinWidth,m_nTitleBarCY,IDB_LEFTTITLE);
	//绘制对话框标题栏左端的logo图标
	DisplayBmp(3,0,26,m_nTitleBarCY,IDB_APPICON);

	//绘制对话框左边框位图
	DisplayBmp(0,m_nTitleBarCY,m_nBorderCX,m_nWinHeight-m_nBorderCY,IDB_LEFTBAR);
	//绘制对话框底边框位图
	DisplayBmp(m_nBorderCX,m_nWinHeight-m_nBorderCX,m_nWinWidth-2*m_nBorderCX,m_nBorderCX,IDB_BOTTOMBAR);
	//绘制对话框左边框位图
	DisplayBmp(m_nWinWidth-m_nBorderCX,m_nTitleBarCY,m_nBorderCX,m_nWinHeight-m_nBorderCY,IDB_RIGHTBAR);
	//给对话框绘制最小化按钮
	DisplayBmp(m_nWinWidth-26*2-5,0,26,26,IDB_MINBTN1);
	//给对话框绘制关闭按钮
	DisplayBmp(m_nWinWidth-26-5,0,26,26,IDB_CLOSEBTN1);

	DrawTitleText();
	ReleaseDC(&windowsDC);
}
//=====================在指定位置显示bmp位图图像
void CMiniNewsDlg::DisplayBmp(int x,int y,int w,int h,int nID)
{
	CRect winRC;
	CDC* pDC=GetWindowDC();
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	BITMAPINFO bmpInfo;
	CBitmap bmp;	
	GetWindowRect(&winRC);
	bmp.LoadBitmap(nID);
	bmp.GetObject(sizeof(BITMAPINFO),&bmpInfo);
	int nBmpCX = bmpInfo.bmiHeader.biWidth;
	int nBmpCY = bmpInfo.bmiHeader.biHeight;
	memDC.SelectObject(bmp);
	pDC->StretchBlt(x,y,w,h,
		&memDC,0,0,nBmpCX,nBmpCY,SRCCOPY);//在窗口中绘制位图
	bmp.DeleteObject();
	ReleaseDC(pDC);
}
void CMiniNewsDlg::SetTitleText(CString strTitle)
{
	this->m_strTitle = strTitle + "-小蔡电脑助手";
}
//绘制标题栏标题文本内容
void CMiniNewsDlg::DrawTitleText()
{

	CDC* pDC= GetWindowDC();
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));
	pDC->SetTextAlign(TA_CENTER);
	CRect rect;
	GetClientRect(&rect);
	CSize szText = pDC->GetTextExtent(m_strTitle);
	CFont* font,*fOldFont;
	font = new CFont;
	font->CreateFont(12,0,0,0,FW_BOLD,FALSE,FALSE,0,ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_SWISS,_T("宋体"));
	fOldFont = pDC->SelectObject(font);
	CRect winRect;
	GetWindowRect(&winRect);
	pDC->TextOut(winRect.Width()/2,6.5,m_strTitle);
	pDC->SelectObject(fOldFont);
	ReleaseDC(pDC);
	delete font;
	delete fOldFont;
	
}

void CMiniNewsDlg::OnNcPaint()
{
	// TODO: 在此处添加消息处理程序代码
	DrawDialog();
	// 不为绘图消息调用 CDialog::OnNcPaint()
}

void CMiniNewsDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialog::OnActivate(nState, pWndOther, bMinimized);
	OnNcPaint();
	// TODO: 在此处添加消息处理程序代码
}

void CMiniNewsDlg::OnNcMouseMove(UINT nHitTest, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect minRC,moreRC,closeRC,winRC,cleanRC,toolkitRC,shoppingRC;
	GetWindowRect(&winRC);
	closeRC.CopyRect(CRect(m_nWinWidth-26,0,m_nWinWidth-26+26,26));		
	minRC.CopyRect(CRect(m_nWinWidth-26*2,0,m_nWinWidth-26*2+26,26));

	point.Offset(-winRC.left,-winRC.top);//由于point为屏幕坐标,这里将其转换为窗口坐标
	if(closeRC.PtInRect(point))//鼠标在关闭按钮上时，更改按钮显示的位图
	{
		m_bMouseOnCloseBtn = TRUE;
		m_bMouseOnMinBtn =FALSE;
		m_bMouseOnMoreBtn = FALSE;
		DisplayBmp(m_nWinWidth-26-5,0,26,26,IDB_CLOSEBTN2);
		DisplayBmp(m_nWinWidth-26*2-5,0,26,26,IDB_MINBTN1);
	}
	else if(minRC.PtInRect(point))//鼠标在最小化按钮上时，更改按钮显示的位图
	{
		m_bMouseOnMinBtn =TRUE;	
		m_bMouseOnCloseBtn = FALSE;
		DisplayBmp(m_nWinWidth-26-5,0,26,26,IDB_CLOSEBTN1);
		DisplayBmp(m_nWinWidth-26*2-5,0,26,26,IDB_MINBTN2);		
	}
	CDialog::OnNcMouseMove(nHitTest, point);
}
void CMiniNewsDlg::OnNcLButtonUp(UINT nHitTest, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_bMouseOnCloseBtn)
	{
		this->SendMessage(WM_CLOSE);
	}
	if(m_bMouseOnMinBtn)
	{
		this->ShowWindow(SW_MINIMIZE);
		m_bMouseOnMinBtn = FALSE;
	}
	CDialog::OnNcLButtonUp(nHitTest, point);
}

void CMiniNewsDlg::OnNcMouseLeave()
{
	// 该功能要求使用 Windows 2000 或更高版本。
	// 符号 _WIN32_WINNT 和 WINVER 必须 >= 0x0500。
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	DisplayBmp(m_nWinWidth-26*2-5,0,26,26,IDB_MINBTN1);
	DisplayBmp(m_nWinWidth-26-5,0,26,26,IDB_CLOSEBTN1);
	m_bMouseOnMinBtn =FALSE;	
	m_bMouseOnCloseBtn = FALSE;
//	CDialog::OnNcMouseLeave();
}

void CMiniNewsDlg::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(!(m_bMouseOnMinBtn||m_bMouseOnCloseBtn))
		CDialog::OnNcLButtonDown(nHitTest, point);
}

HBRUSH CMiniNewsDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性
	HBRUSH brush=CreateSolidBrush(m_bkColor);
	switch(nCtlColor)
	{
	case CTLCOLOR_STATIC:
		pDC->SetBkMode(TRANSPARENT); 
		//设置背景为透明
		pDC->SetTextColor(RGB(255,255,255)); //设置字体颜色
		pDC->SetBkColor(m_bkColor);
		//pWnd->SetFont(cFont); //设置字体
		hbr = (HBRUSH)brush;
		//创建画刷
		break;
	case CTLCOLOR_BTN:
		pDC->SetBkMode(TRANSPARENT); 
		//设置背景为透明
		pDC->SetTextColor(RGB(255,255,255)); //设置字体颜色
		pDC->SetBkColor(m_bkColor);
		//pWnd->SetFont(cFont); //设置字体
		hbr = (HBRUSH)brush;
		//创建画刷
		break;

	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
void CMiniNewsDlg::OnSysCommand(UINT nID, LPARAM lParam)
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



//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMiniNewsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

