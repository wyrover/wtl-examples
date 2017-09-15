
#include "stdafx.h"
#include "redrawListDemo.h"
#include "redrawListDemoDlg.h"

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


// CredrawListDemoDlg dialog




CredrawListDemoDlg::CredrawListDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CredrawListDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_first_list_selected = INIT_NUMBER;
	m_timer = DEFAULT_TIME;

	m_first_change_list_select = INIT_NUMBER;
}

void CredrawListDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PATIENT_LIST_CONTROL, m_pat_list);
	DDX_Control(pDX, IDC_LIST1, m_test_list);
}

BEGIN_MESSAGE_MAP(CredrawListDemoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CredrawListDemoDlg::OnBnClickedButton1)
	ON_NOTIFY(NM_CLICK, IDC_PATIENT_LIST_CONTROL, &CredrawListDemoDlg::OnNMClickPatientListControl)
	ON_NOTIFY(NM_RCLICK, IDC_PATIENT_LIST_CONTROL, &CredrawListDemoDlg::OnNMClickPatientListControl)
	ON_NOTIFY(NM_CUSTOMDRAW,IDC_PATIENT_LIST_CONTROL, OnCustomdrawList)
	ON_NOTIFY(LVN_MARQUEEBEGIN, IDC_PATIENT_LIST_CONTROL, &CredrawListDemoDlg::OnLvnMarqueeBegin)
	ON_NOTIFY(LVN_ITEMCHANGING, IDC_PATIENT_LIST_CONTROL, &CredrawListDemoDlg::OnLvnItemChangingList)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_PATIENT_LIST_CONTROL, &CredrawListDemoDlg::OnLvnItemChangeList)
	ON_NOTIFY(LVN_BEGINDRAG, IDC_PATIENT_LIST_CONTROL, &CredrawListDemoDlg::OnLvnBeginDragList)
	ON_NOTIFY(LVN_BEGINRDRAG, IDC_PATIENT_LIST_CONTROL, &CredrawListDemoDlg::OnLvnBeginRDragList)
	ON_WM_TIMER()
	ON_NOTIFY(NM_SETFOCUS, IDC_PATIENT_LIST_CONTROL, &CredrawListDemoDlg::OnNMSetfocusList)
	ON_NOTIFY(NM_KILLFOCUS, IDC_PATIENT_LIST_CONTROL, &CredrawListDemoDlg::OnNMKillfocusList)
	ON_NOTIFY(HDN_ITEMCHANGINGW, 0, &CredrawListDemoDlg::OnHdnItemchangingList)
    ON_NOTIFY(HDN_ITEMCHANGED, 0, &CredrawListDemoDlg::OnHdnItemchangList)
	ON_NOTIFY(LVN_KEYDOWN, IDC_PATIENT_LIST_CONTROL, &CredrawListDemoDlg::OnLvnKeyDown)
END_MESSAGE_MAP()

BOOL CredrawListDemoDlg::OnInitDialog()
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


    DWORD dw_style = m_pat_list.GetExtendedStyle();
    dw_style |= LVS_EX_FULLROWSELECT;
    m_pat_list.SetExtendedStyle(dw_style);//设置 选择为 行选择
	m_pat_list.SetExtendedStyle( m_pat_list.GetExtendedStyle() | LVS_EX_DOUBLEBUFFER );  //32位   双缓存




	CBitmap bmp;
    bmp.LoadBitmap(IDB_SCROLLBAR);
    BITMAP bm;
    bmp.GetBitmap(&bm);
    m_bitmap_scrollbar = (HBITMAP)bmp.Detach();//加载 滚动条 bmp 图片

    SkinWndScroll(&m_pat_list, m_bitmap_scrollbar);//替换原先的滚动条

	for(int i = 0; i<5 ; i++)
	{
		m_pat_list.InsertColumn(i, L"test", 0, 100);
		m_test_list.InsertColumn(i, L"test", 0, 100);
	}

	m_pat_list.SetBkColor(RGB(65, 62, 80));//设置控件背景颜色
	m_test_list.SetBkColor(RGB(255, 255, 0));

	OnBnClickedButton1();
	OnBnClickedButton1();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CredrawListDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CredrawListDemoDlg::OnPaint()
{

	CPaintDC dc(this);
	CRect   rect;     
	GetClientRect(rect);   
	dc.FillSolidRect(rect,RGB(49,47,60)); //设置背景颜色
	if (IsIconic())
	{
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
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CredrawListDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CredrawListDemoDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	static int number;
	for(int i = 0; i <10; i++)
	{
		CString temp;
		temp.Format(L"test %d", number++);
		m_pat_list.InsertItem(i, temp);
		m_test_list.InsertItem(i, temp);
		for(int j = 1; j <5; j++)
		{
			CString temp;
			temp.Format(L"test %d", number++);
			m_pat_list.SetItemText(i, j, temp);
			m_test_list.SetItemText(i, j, temp);
		}
	}
}




void CredrawListDemoDlg::OnCustomdrawList (
    NMHDR* pNMHDR, 
    LRESULT* pResult 
) {
    unsigned int item_sts;
    LPNMLVCUSTOMDRAW lcd=(LPNMLVCUSTOMDRAW)pNMHDR;
    int check = (CDIS_SELECTED | CDIS_FOCUS);
    switch (lcd->nmcd.dwDrawStage) {
    case CDDS_PREPAINT:
        *pResult=CDRF_NOTIFYSUBITEMDRAW;
        break;
    case CDDS_ITEMPREPAINT:
        lcd->nmcd.uItemState &= ~CDIS_FOCUS;

        if(IsListItemEmpty(lcd->nmcd.dwItemSpec)==TRUE ) {
            m_pat_list.SetItemState(lcd->nmcd.dwItemSpec, 0, LVIS_SELECTED | LVIS_FOCUSED);
        }

        if (( lcd->nmcd.dwItemSpec%2)==0) {
            lcd->clrText=COLOR_COMMON_TEXT;
            item_sts =  m_pat_list.GetItemState(lcd->nmcd.dwItemSpec,LVIS_SELECTED);
            if ( item_sts == LVIS_SELECTED ) {
                lcd->clrText=COLOR_COMMON_TEXT;
                lcd->clrTextBk=RGB(128,128,0);
                lcd->nmcd.uItemState &= ~CDIS_SELECTED;//选择的高亮 重绘的必须加的代码
            } else {
                lcd->clrText=COLOR_COMMON_TEXT;
                lcd->clrTextBk=RGB(33-8,25-6,42-6);
            }
            *pResult=CDRF_NEWFONT;
        } else {
            lcd->clrText=COLOR_COMMON_TEXT;
            item_sts =  m_pat_list.GetItemState(lcd->nmcd.dwItemSpec,LVIS_SELECTED);
            if ( item_sts == LVIS_SELECTED ) {
                lcd->clrText=COLOR_COMMON_TEXT;
                lcd->clrTextBk=RGB(128,128,0);
                lcd->nmcd.uItemState &= ~CDIS_SELECTED;
            } else {
                lcd->clrText=COLOR_COMMON_TEXT;
                lcd->clrTextBk=RGB(12-6,16-6,24-6);
            }
            *pResult=CDRF_NEWFONT;
        }
        *pResult=CDRF_NOTIFYSUBITEMDRAW;
        break;
    case CDDS_ITEMPREPAINT|CDDS_SUBITEM:
        *pResult=CDRF_DODEFAULT;

        if (lcd->iSubItem==3) {
            *pResult=CDRF_NEWFONT;
        }
        if (lcd->iSubItem != 3) {
            *pResult=CDRF_NEWFONT;
        }
        break;
    default:
        *pResult=CDRF_DODEFAULT;
        break;
    }
}

BOOL CredrawListDemoDlg::IsListItemEmpty(
    int test_number
) {
    if(test_number < NULL || test_number < AllListItemNumber() ) {
        return FALSE;
    }
    return TRUE;
}

UINT CredrawListDemoDlg::AllListItemNumber()
{
	return m_pat_list.GetItemCount();
}

void CredrawListDemoDlg::OnLvnMarqueeBegin(
    NMHDR *pNMHDR, 
    LRESULT *pResult
) {
    *pResult = 1;
	//这里返回 0 就是把第一列的虚线框显示   返回 1 就是 取消 虚线框
}


BOOL CredrawListDemoDlg::PreTranslateMessage(
    MSG* pMsg
) {
    static int shift_key_flag = 0;
    static int ctrl_key_flag = 0;

    if (pMsg-> message == WM_KEYDOWN) {
        switch (pMsg-> wParam) {
        case VK_RETURN:
            return TRUE;
        case VK_ESCAPE:
            return TRUE;
        default:
            break;
        }
    }

    if ( pMsg->message == WM_KEYUP ) {
        if ( pMsg->wParam == VK_SHIFT ) {
            shift_key_flag = 0;
        } else if ( pMsg->wParam == VK_CONTROL ) {
            ctrl_key_flag = 0;
        } else if ( ctrl_key_flag == 1 || shift_key_flag == 1 ) {
            return TRUE;
        }
    } else if ( pMsg->message == WM_KEYDOWN ) {
        if ( pMsg->wParam == VK_SHIFT ) {
            shift_key_flag = 1;
        } else if ( pMsg->wParam == VK_CONTROL ) {
            ctrl_key_flag = 1;
        } else if ( ctrl_key_flag == 1 || shift_key_flag == 1 ) {
            return TRUE;
        } else if( pMsg->wParam<=VK_HOME && pMsg->wParam>=VK_PRIOR) {
            return TRUE;
        }
    }


    if ( m_first_list_selected != INIT_NUMBER && pMsg->message == WM_MOUSEMOVE) {//判断是否是拖动状态
            ListSelectedProc(DEFAULT_MODE);
    } else if ( m_first_list_selected != INIT_NUMBER && (pMsg->message == WM_LBUTTONUP || pMsg->message == WM_RBUTTONUP)) {//判断是否是 多动状态下的弹起鼠标
        ReleaseCapture();
        ListClickedProc();
        m_first_list_selected = INIT_NUMBER;
        OnStopTimer();
        return TRUE;
	}

    return CDialog::PreTranslateMessage(pMsg);
}

void CredrawListDemoDlg::ListClickedProc(
) {
    m_first_change_list_select = m_first_list_selected;
}

void CredrawListDemoDlg::OnStopTimer(
) {
    if ( m_timer != DEFAULT_TIME ) {
        KillTimer(m_timer);
        m_timer = DEFAULT_TIME;
	}
}

void CredrawListDemoDlg::OnLvnItemChangeList(
    NMHDR *pNMHDR, 
    LRESULT *pResult
) {
    DWORD pos = GetMessagePos();
    CPoint point(LOWORD(pos), HIWORD(pos));
    m_pat_list.ScreenToClient(&point);

    LVHITTESTINFO lvinfo;
    lvinfo.pt = point;
    lvinfo.flags = LVHT_ABOVE;

    int item_index = m_pat_list.SubItemHitTest(&lvinfo);
    if (item_index >= AllListItemNumber()) {
        m_pat_list.SetItemState(item_index, 0, LVIS_SELECTED | LVIS_FOCUSED);
    }
    m_first_change_list_select = item_index;
    TRACE("item   change   %d\n", m_first_change_list_select);
    *pResult = 0;
}

void CredrawListDemoDlg::OnLvnItemChangingList(
    NMHDR *rNMHDR, 
    LRESULT *pResult
) {
    if ( m_first_list_selected == INIT_NUMBER ) {
        DWORD pos = GetMessagePos();
        CPoint point(LOWORD(pos), HIWORD(pos));
        m_pat_list.ScreenToClient(&point);

        LVHITTESTINFO lvinfo;
        lvinfo.pt = point;
        lvinfo.flags = LVHT_ABOVE;

        int item_index = m_pat_list.SubItemHitTest(&lvinfo);
        if ( item_index >=0 ) {
            m_first_change_list_select = item_index;
        }
    }
    *pResult = 0;
}

void CredrawListDemoDlg::OnLvnBeginDragList(
    NMHDR *pNMHDR, 
    LRESULT *pResult
) {
    m_first_list_selected = m_first_change_list_select;
    SetCapture();
}

void CredrawListDemoDlg::OnLvnBeginRDragList(
    NMHDR *pNMHDR, 
    LRESULT *pResult
) {
    OnLvnBeginDragList(pNMHDR, pResult);
    *pResult = 0;
}

void CredrawListDemoDlg::OnTimer(
    UINT_PTR nIDEvent
) {
    if ( nIDEvent == 1 ) {
        ListSelectedProc(1);
    }
    CDialog::OnTimer(nIDEvent);
}

void CredrawListDemoDlg::OnNMSetfocusList(
    NMHDR *pNMHDR, 
    LRESULT *pResult
) {
    *pResult = 0;
}

void CredrawListDemoDlg::OnNMKillfocusList(
    NMHDR *pNMHDR, 
    LRESULT *pResult
) {
    *pResult = 0;
}

void CredrawListDemoDlg::ListSelectedProc(
    int mode
) {
    int item;
    RECT rect;
    LVHITTESTINFO lvhti;
    POINT pt;
    int start_item;
    int end_item;
    int m_browse_start_item = m_first_list_selected;
    unsigned int item_sts;
    
    GetCursorPos(&pt);
    CRect r;
    m_pat_list.GetWindowRect(r);

    if (!(r.PtInRect(pt))) {
        item = GetNowItemRow(pt, r, mode);
    } else {
        m_pat_list.ScreenToClient(&pt);
        lvhti.pt = pt;
        item = m_pat_list.SubItemHitTest(&lvhti);
        OnStopTimer();
    }
    TRACE("item number is %d \n", item);
    if ( item != INIT_NUMBER ) {
        if ( item < m_browse_start_item ) {
            start_item = item;
            end_item = m_browse_start_item;
        } else {
            start_item = m_browse_start_item;
            end_item = item;
        }
        TRACE("start_item %d  end_item %d\n", start_item, end_item);
        for (int i = 0 ; i < AllListItemNumber(); i++ ) {
            item_sts = m_pat_list.GetItemState(i, LVIS_SELECTED);
            if ( i >= start_item  && i <= end_item) {//判断是否为选择状态 并把状态改反
                if ( item_sts != LVIS_SELECTED ) {
                    m_pat_list.SetItemState(i, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
                }
            } else {
                if ( item_sts == LVIS_SELECTED ) {
                    m_pat_list.SetItemState(i, 0, LVIS_SELECTED | LVIS_FOCUSED);
                }
            }
        }
    }
}

int CredrawListDemoDlg::GetNowItemRow(
    POINT pt,
    CRect r,
    int mode
) {
    int list_start_select_list;
    int list_stop_select_list;
    int item = 0;
    list_start_select_list = m_pat_list.GetTopIndex();
    list_stop_select_list = (list_start_select_list + m_pat_list.GetCountPerPage()-1);

    if ( pt.y < r.top && ( m_timer == DEFAULT_TIME || mode == 1 ) ) {
        item = list_start_select_list;
    } else if ( pt.y > r.bottom && ( m_timer == DEFAULT_TIME || mode == 1 ) ) {
        item = list_stop_select_list;
    } else {
        item = -1;
    }
    return item;
}

void CredrawListDemoDlg::OnHdnItemchangingList(
    NMHDR *pNMHDR, 
    LRESULT *pResult
) {
    LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);

    char tmp_buf[64];
    HDITEM hdi;
    CSize rsize;
    RECT rrect;

    m_pat_list.Invalidate();
    hdi.mask = HDI_TEXT | HDI_WIDTH | HDI_FORMAT;
    hdi.pszText = (LPWSTR)tmp_buf;
    hdi.cchTextMax = sizeof(tmp_buf);

    m_pat_list.GetHeaderCtrl()->GetItem(phdr->iItem,&hdi);

    rsize = m_pat_list.ApproximateViewRect(CSize(-1,-1),-1);
    m_pat_list.GetClientRect(&rrect);

    if ( (phdr->pitem->mask & HDI_WIDTH) != 0 ) {
        if ( phdr->pitem->cxy < ONE_HEADER_WIDTH ) {
            *pResult = FAILURE;
            return;
        }
        if ( phdr->pitem->cxy < hdi.cxy ) {
            if ( ( rsize.cx - ( hdi.cxy - phdr->pitem->cxy ) ) <= (ALL_HEADER_WIDTH) ) {
                *pResult = FAILURE;
                return;
            }
        }
    }
    *pResult = 0;
}

void CredrawListDemoDlg::OnHdnItemchangList(
    NMHDR *pNMHDR, 
    LRESULT *pResult
) {
    *pResult = 0;
    m_pat_list.GetHeaderCtrl()->Invalidate();
}

void CredrawListDemoDlg::OnLvnKeyDown(
    NMHDR *pNMHDR, 
    LRESULT *pResult
) {
    LPNMLVKEYDOWN lvn_key_dow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
    if(lvn_key_dow->wVKey == VK_DOWN) {
		if(m_pat_list.GetSelectedCount() == 0) {
            m_first_change_list_select = 0;
        }
	}
}

void CredrawListDemoDlg::OnNMClickPatientListControl(
    NMHDR *pNMHDR, 
    LRESULT *pResult
) {
    int select_list_count = 0;
    TRACE("clicked number %d\n", m_first_change_list_select);
    if (m_first_change_list_select >=0) {
        select_list_count = m_pat_list.GetSelectedCount();
        TRACE("clicked select list count %d\n", select_list_count);

        if ( AllListItemNumber() == 0 ) {
            return ;
        }
    }
	//m_first_list_selected = INIT_NUMBER;
	//m_first_change_list_select = INIT_NUMBER;
}