// SkinScrollWnd.cpp : implementation file
// 模块：控件滚动条换肤
//		通过对一个控件的子类化实现滚动条换肤，和CSkinScrollBar配合使用。
//	2006.7.7	黄建雄	创建
//	2007.1.23	黄建雄	调整滚动条的响应
//  2007.6.14	黄建雄  修改一个bug,将调用IsWindowVisible来判断滚动条是否可见改为判断窗口Style
//  2012 7 18   崔光浩  修改一个bug，当窗口没有边框的时候不显示 修改了 窗口过程函数的（70行） 那里 设置 标记 并且强制的进入一次
//////////////////////////////////////////////////////////////////////	
#include "stdafx.h"
#include "SkinScrollWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TIMER_UPDATE 100
#define UM_DESTMOVE	(WM_USER+100)

static LRESULT CALLBACK HookWndProc(//子类化回调函数
    HWND hwnd, 
    UINT msg, 
    WPARAM wp, 
    LPARAM lp
) {
	static BOOL FLAG = TRUE;
	CSkinScrollWnd *skin=(CSkinScrollWnd*)GetWindowLongPtr(hwnd,GWLP_USERDATA);
	if (msg==WM_DESTROY) {
		WNDPROC proc_old=skin->m_fun_old_proc;
		UnskinWndScroll(CWnd::FromHandle(hwnd));
		return ::CallWindowProc(proc_old,hwnd,msg,wp,lp);
	}
	
	LRESULT lr=::CallWindowProc(skin->m_fun_old_proc,hwnd,msg,wp,lp);//执行原来的回调函数
    if (skin->m_bop) {
        return lr;
    }
	if (msg==WM_ERASEBKGND) {
			SCROLLINFO si;
			DWORD dw_style=::GetWindowLongPtr(hwnd,GWL_STYLE);
			if (dw_style&WS_VSCROLL) {
				memset(&si,0,sizeof(si));
				si.cbSize=sizeof(si);
				si.fMask=SIF_ALL;
				::GetScrollInfo(hwnd,SB_VERT,&si);
				if (si.nMax!=skin->m_sb_vert.m_si.nMax 
					||si.nMin!=skin->m_sb_vert.m_si.nMin
					||si.nPos!=skin->m_sb_vert.m_si.nPos
					||si.nPage!=skin->m_sb_vert.m_si.nPage) {
					skin->m_sb_vert.SetScrollInfo(&si,!skin->m_bop);
					skin->m_sb_vert.EnableWindow(si.nMax>=si.nPage);
				}
			}
			if (dw_style&WS_HSCROLL) {
				memset(&si,0,sizeof(si));
				si.cbSize=sizeof(si);
				si.fMask=SIF_ALL;
				::GetScrollInfo(hwnd,SB_HORZ,&si);
				if (si.nMax!=skin->m_sb_horz.m_si.nMax 
					||si.nMin!=skin->m_sb_horz.m_si.nMin
					||si.nPos!=skin->m_sb_horz.m_si.nPos
                    ||si.nPage!=skin->m_sb_horz.m_si.nPage) {
					skin->m_sb_horz.SetScrollInfo(&si,!skin->m_bop);
					skin->m_sb_horz.EnableWindow(si.nMax>=si.nPage);
				}
			}
	} else if (msg==WM_NCCALCSIZE && wp || FLAG) {
        FLAG = FALSE;
        LPNCCALCSIZE_PARAMS nc_calc_size_param=(LPNCCALCSIZE_PARAMS)lp;
        DWORD dw_style=::GetWindowLongPtr(hwnd,GWL_STYLE);
        DWORD dw_ex_style=::GetWindowLongPtr(hwnd,GWL_EXSTYLE);
        BOOL  left_scroll=dw_ex_style&WS_EX_LEFTSCROLLBAR;
        int wid=::GetSystemMetrics(SM_CXVSCROLL);
        if (dw_style&WS_VSCROLL) {
            if (left_scroll) {
                nc_calc_size_param->rgrc[0].left-=wid-skin->m_scroll_wid;
            } else {
                nc_calc_size_param->rgrc[0].right+=wid-skin->m_scroll_wid;
            }
        }
        if (dw_style&WS_HSCROLL) {
            nc_calc_size_param->rgrc[0].bottom+=wid-skin->m_scroll_wid;
        }

        RECT rc,rc_vert,rc_horz;
        ::GetWindowRect(hwnd,&rc);
        ::OffsetRect(&rc,-rc.left,-rc.top);

        wid=skin->m_scroll_wid;
        if (left_scroll) {
            int left=nc_calc_size_param->rgrc[0].left;
            int bottom=nc_calc_size_param->rgrc[0].bottom;
            rc_vert.right=left;
            rc_vert.left=left-wid;
            rc_vert.top=0;
            rc_vert.bottom=bottom;
            rc_horz.left=left;
            rc_horz.right=nc_calc_size_param->rgrc[0].right;
            rc_horz.top=bottom;
            rc_horz.bottom=bottom+wid;
        } else {
            int right=nc_calc_size_param->rgrc[0].right;
            int bottom=nc_calc_size_param->rgrc[0].bottom;
            rc_vert.left=right;
            rc_vert.right=right+wid;
            rc_vert.top=0;
            rc_vert.bottom=bottom;
            rc_horz.left=0;
            rc_horz.right=right;
            rc_horz.top=bottom;
            rc_horz.bottom=bottom+wid;
        }
        if (dw_style&WS_VSCROLL && dw_style&WS_HSCROLL) {
            skin->m_angle_type=left_scroll?1:2;
        } else {
            skin->m_angle_type=0;
        }
        if (dw_style&WS_VSCROLL) {
            skin->m_sb_vert.MoveWindow(&rc_vert);
            skin->m_sb_vert.ShowWindow(SW_SHOW);
        } else {
            skin->m_sb_vert.ShowWindow(SW_HIDE);
        }
        if (dw_style&WS_HSCROLL) {
            skin->m_sb_horz.MoveWindow(&rc_horz);
            skin->m_sb_horz.ShowWindow(SW_SHOW);
        } else {
            skin->m_sb_horz.ShowWindow(SW_HIDE);
        }
        skin->PostMessage(UM_DESTMOVE,dw_style&WS_VSCROLL,left_scroll);
    }
    return lr;
}


extern "C" CSkinScrollWnd* SkinWndScroll(
    CWnd *pWnd,
    HBITMAP hBmpScroll
) {
	CSkinScrollWnd *frame=new CSkinScrollWnd;
	frame->SkinWindow(pWnd,hBmpScroll);
	return frame;
}


extern "C" BOOL UnskinWndScroll(
    CWnd *pWnd
) {
	CSkinScrollWnd *frame=(CSkinScrollWnd *)GetWindowLongPtr(pWnd->m_hWnd,GWLP_USERDATA);
	if (frame) {
		RECT rc;
		CWnd *parent=frame->GetParent();
		frame->GetWindowRect(&rc);
		parent->ScreenToClient(&rc);
		SetWindowLongPtr(pWnd->m_hWnd,GWLP_WNDPROC,(LONG_PTR)frame->m_fun_old_proc);
		SetWindowLongPtr(pWnd->m_hWnd,GWLP_USERDATA,0);
		pWnd->SetParent(parent);
		pWnd->MoveWindow(&rc);
		frame->DestroyWindow();
		delete frame;
	}
	return TRUE;
}

CSkinScrollWnd::CSkinScrollWnd(
) {
	m_fun_old_proc=NULL;
	m_bop=FALSE;
	m_scroll_wid=16;
	m_bmp_scroll=0;
	m_angle_type=0;
}

CSkinScrollWnd::~CSkinScrollWnd(
) {
}


BEGIN_MESSAGE_MAP(CSkinScrollWnd, CWnd)
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_MESSAGE(UM_DESTMOVE,OnDestMove)
END_MESSAGE_MAP()


BOOL CSkinScrollWnd::SkinWindow(
    CWnd *pWnd,
    HBITMAP hBmpScroll
) {
	ASSERT(m_hWnd==NULL);
	m_bmp_scroll=hBmpScroll;
	BITMAP bm;
	GetObject(hBmpScroll,sizeof(bm),&bm);
	m_scroll_wid=bm.bmWidth/9;

	CWnd *parent=pWnd->GetParent();
	ASSERT(parent);
	RECT rc_frm,rc_wnd;
	pWnd->GetWindowRect(&rc_frm);
	parent->ScreenToClient(&rc_frm);
	rc_wnd=rc_frm;
	OffsetRect(&rc_wnd,-rc_wnd.left,-rc_wnd.top);
	UINT u_id=pWnd->GetDlgCtrlID();
	DWORD dw_style=pWnd->GetStyle();
	DWORD dw_ex_style=pWnd->GetExStyle();
	DWORD dw_frm_style=WS_CHILD|SS_NOTIFY;
	DWORD dw_frm_style_ex=0;
	if (dw_ex_style & WS_EX_TOOLWINDOW) {
		dw_frm_style_ex |= WS_EX_TOOLWINDOW;
		dw_frm_style_ex |= WS_EX_TOPMOST;
	}
    if (dw_style&WS_VISIBLE) {
        dw_frm_style|=WS_VISIBLE;
    }

	if (dw_style&WS_BORDER) {
		dw_frm_style|=WS_BORDER;
		pWnd->ModifyStyle(WS_BORDER,0);
		int border=::GetSystemMetrics(SM_CXBORDER);
		rc_wnd.right-=border*2;
		rc_wnd.bottom-=border*2;
	}
    if (dw_ex_style&WS_EX_CLIENTEDGE) {
		pWnd->ModifyStyleEx(WS_EX_CLIENTEDGE,0);
		int border=::GetSystemMetrics(SM_CXEDGE);
		rc_wnd.right-=border*2;
		rc_wnd.bottom-=border*2;
		dw_frm_style_ex|=WS_EX_CLIENTEDGE;
	}
	this->CreateEx(dw_frm_style_ex,AfxRegisterWndClass(NULL),L"SkinScrollBarFrame",dw_frm_style,rc_frm,parent,u_id);

	m_wnd_limit.Create(NULL,L"LIMIT",WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,200);
	m_sb_horz.Create(WS_CHILD,CRect(0,0,0,0),this,100);
	m_sb_vert.Create(WS_CHILD|SBS_VERT,CRect(0,0,0,0),this,101);
	m_sb_horz.SetBitmap(m_bmp_scroll);
	m_sb_vert.SetBitmap(m_bmp_scroll);

	pWnd->SetParent(&m_wnd_limit);
	SetWindowLongPtr(pWnd->m_hWnd,GWLP_USERDATA,(LONG_PTR)this);
	m_fun_old_proc=(WNDPROC)SetWindowLongPtr(pWnd->m_hWnd,GWLP_WNDPROC,(LONG_PTR)HookWndProc);

	pWnd->MoveWindow(&rc_wnd);
	SetTimer(TIMER_UPDATE,500,NULL);
	return TRUE;
}

void CSkinScrollWnd::OnSize(
    UINT nType, 
    int cx, 
    int cy
) {
	CWnd::OnSize(nType, cx, cy);
    if (cx==0 || cy==0) {
        return;
    }
	if (m_wnd_limit.m_hWnd) {
		CWnd *wnd=m_wnd_limit.GetWindow(GW_CHILD);
		wnd->MoveWindow(0,0,cx,cy);
	}
}

void CSkinScrollWnd::OnVScroll(
    UINT nSBCode, 
    UINT nPos, 
    CScrollBar* pScrollBar
) {
	CWnd *wnd = m_wnd_limit.GetWindow(GW_CHILD);
	m_bop=TRUE;
	wnd->SendMessage(WM_VSCROLL,MAKELONG(nSBCode,nPos),0);
	m_bop=FALSE;
    if (nSBCode==SB_THUMBTRACK) {
        return;
    }
	SCROLLINFO si={0};
	si.cbSize=sizeof(si);
	si.fMask=SIF_ALL;
	wnd->GetScrollInfo(SB_VERT,&si);
	pScrollBar->SetScrollInfo(&si,TRUE);
}

void CSkinScrollWnd::OnHScroll(
    UINT nSBCode, 
    UINT nPos, 
    CScrollBar* pScrollBar
) {
	CWnd *wnd=m_wnd_limit.GetWindow(GW_CHILD);
	m_bop=TRUE;
	wnd->SendMessage(WM_HSCROLL,MAKELONG(nSBCode,nPos),0);
	m_bop=FALSE;
    if (nSBCode==SB_THUMBTRACK) {
        return;
    }
	SCROLLINFO si={0};
	si.cbSize=sizeof(si);
	si.fMask=SIF_ALL;
	wnd->GetScrollInfo(SB_HORZ,&si);
	pScrollBar->SetScrollInfo(&si,TRUE);
}

void CSkinScrollWnd::OnPaint(
) {
	CPaintDC dc(this); // device context for painting
	CDC memdc;
	memdc.CreateCompatibleDC(&dc);
	HGDIOBJ old_bmp=::SelectObject(memdc,m_bmp_scroll);
	RECT rc;
	GetClientRect(&rc);
    if (m_angle_type==1) {
		dc.BitBlt(rc.left,rc.bottom-m_scroll_wid,m_scroll_wid,m_scroll_wid,&memdc,m_scroll_wid*8,m_scroll_wid*1,SRCCOPY);
    } else if (m_angle_type==2) {
		dc.BitBlt(rc.right-m_scroll_wid,rc.bottom-m_scroll_wid,m_scroll_wid,m_scroll_wid,&memdc,m_scroll_wid*8,m_scroll_wid*0,SRCCOPY);
    }
	::SelectObject(memdc,old_bmp);
}

void CSkinScrollWnd::OnTimer(
    UINT_PTR nIDEvent
) {
	CWnd *wnd=m_wnd_limit.GetWindow(GW_CHILD);
	SCROLLINFO si1={0};
	si1.cbSize=sizeof(SCROLLINFO);
	si1.fMask=SIF_ALL;
	SCROLLINFO si2={0};
	if (GetWindowLongPtr(m_sb_vert.m_hWnd,GWL_STYLE)&WS_VISIBLE && !m_sb_vert.m_drag) {
		wnd->GetScrollInfo(SB_VERT,&si1);
		m_sb_vert.GetScrollInfo(&si2,SIF_ALL);
        if (si1.nMax!=si2.nMax||si1.nMin!=si2.nMin||si1.nPos!=si2.nPos||si1.nPage!=si2.nPage) {
			m_sb_vert.SetScrollInfo(&si1);
        }
	}
	if (GetWindowLongPtr(m_sb_horz.m_hWnd,GWL_STYLE)&WS_VISIBLE && !m_sb_horz.m_drag) {
		wnd->GetScrollInfo(SB_HORZ,&si1);
		m_sb_horz.GetScrollInfo(&si2,SIF_ALL);
        if (si1.nMax!=si2.nMax||si1.nMin!=si2.nMin||si1.nPos!=si2.nPos||si1.nPage!=si2.nPage) {
			m_sb_horz.SetScrollInfo(&si1);
        }
	}
}

LRESULT CSkinScrollWnd::OnDestMove(
    WPARAM wParam, 
    LPARAM lParam
) {
	m_bop=TRUE;
	BOOL scroll=wParam;
	BOOL left_scroll=lParam;
	RECT rc_client;
	GetClientRect(&rc_client);
	RECT rc_limit,rc_wnd;
	rc_wnd=rc_client;
	rc_limit=rc_client;
    if (GetWindowLongPtr(m_sb_horz.m_hWnd,GWL_STYLE)&WS_VISIBLE) {
        rc_limit.bottom-=m_scroll_wid;
    }
    if (left_scroll) { 
		if (scroll) {
			rc_limit.left+=m_scroll_wid;
			OffsetRect(&rc_wnd,-m_scroll_wid,0);
		}
	} else {
        if (scroll) {
            rc_limit.right-=m_scroll_wid;
        }
	}
	m_wnd_limit.MoveWindow(&rc_limit);
	m_wnd_limit.GetWindow(GW_CHILD)->SetWindowPos(NULL,rc_wnd.left,0,0,0,SWP_NOSIZE|SWP_NOZORDER);
	m_bop=FALSE;
	return 0;
}
