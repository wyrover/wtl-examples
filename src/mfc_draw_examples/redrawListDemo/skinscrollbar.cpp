// SkinScrollBar.cpp : implementation file
//	模块:位图皮肤控件
//		实现一个位图滚动条控件
//	位图格式：位图应该是(width/9=height/3)
//	2006.7.7	黄建雄 创建        	
//	2007.1.22	黄建雄 修改定时器等问题
//	2007.1.23	黄建雄 修改控件太小时显示的问题，修改拖动时一个计算错误
//////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "SkinScrollBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TIMERID_NOTIFY	100
#define TIMERID_DELAY	200
#define TIME_DELAY		500
#define TIME_INTER		100

#define THUMB_BORDER	3
#define THUMB_MINSIZE	(THUMB_BORDER*2)

CSkinScrollBar::CSkinScrollBar(
) {
	m_bmp=NULL;
	m_drag=FALSE;
	memset(&m_si,0,sizeof(SCROLLINFO));
	m_si.nTrackPos=-1;
	m_clicked=-1;
	m_notify=FALSE;
	m_ht_prev=-1;
	m_pause=FALSE;
	m_trace=FALSE;
}

CSkinScrollBar::~CSkinScrollBar(
) {
}


BEGIN_MESSAGE_MAP(CSkinScrollBar, CScrollBar)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
END_MESSAGE_MAP()

BOOL CSkinScrollBar::IsVertical(
) {
	DWORD dw_style=GetStyle();
	return dw_style&SBS_VERT;
}

UINT CSkinScrollBar::HitTest(
    CPoint pt
) {
	int test_pos=pt.y;
    if (!IsVertical()) {
        test_pos=pt.x;
    }
    if (test_pos<0) {
        return -1;
    }
	SCROLLINFO si=m_si;
	int inter_hei=m_hei-2*m_wid;
    if (inter_hei<0) {
        inter_hei=0;
    }
	int	slide_hei=si.nPage*inter_hei/(si.nMax-si.nMin+1);
    if (slide_hei<THUMB_MINSIZE) {
        slide_hei=THUMB_MINSIZE;
    }
    if (inter_hei<THUMB_MINSIZE) {
        slide_hei=0;
    }
	int empty_hei=inter_hei-slide_hei;
	
	int arrow_hei=(inter_hei==0)?(m_hei/2):m_wid;
	int bottom=0;
	int seg_len=arrow_hei;
	bottom+=seg_len;
	UINT hit=SB_LINEUP;
    if (test_pos<bottom) {
        return hit;
    }
    if (si.nTrackPos==-1) {
        si.nTrackPos=si.nPos;
    }
	hit=SB_PAGEUP;
    if ((si.nMax-si.nMin-si.nPage+1)==0) {
		seg_len=empty_hei/2;
    } else {
		seg_len=empty_hei*si.nTrackPos/(si.nMax-si.nMin-si.nPage+1);
    }
	bottom+=seg_len;
    if (test_pos<bottom) {
        return hit;
    }
	seg_len=slide_hei;
	bottom+=seg_len;
	hit=SB_THUMBTRACK;
    if (test_pos<bottom) {
        return hit;
    }
	bottom=m_hei-arrow_hei;
	hit=SB_PAGEDOWN;
    if (test_pos<bottom) {
        return hit;
    }
	hit=SB_LINEDOWN;
	return hit;
}

void CSkinScrollBar::SetBitmap(
    HBITMAP bmp
) {
	ASSERT(m_hWnd);
	m_bmp=bmp;
	BITMAP bm;
	GetObject(bmp,sizeof(bm),&bm);
	m_wid=bm.bmWidth/9;
	m_frm_hei = bm.bmHeight/3;
	CRect rc;
	GetWindowRect(&rc);
	GetParent()->ScreenToClient(&rc);
    if (IsVertical()) {
		rc.right=rc.left+m_wid;
	} else {
		rc.bottom=rc.top+m_wid;
	}
	MoveWindow(&rc);
}

void CSkinScrollBar::OnSize(
    UINT nType, 
    int cx, 
    int cy
) {
	CScrollBar::OnSize(nType, cx, cy);

	m_hei=IsVertical() ? cy : cx;
}

void CSkinScrollBar::OnPaint(
) {
	CPaintDC dc(this);
    if (!m_bmp) {
        return;
    }
	CDC memdc;
	memdc.CreateCompatibleDC(&dc);
	HGDIOBJ old_bmp=::SelectObject(memdc,m_bmp);

	RECT rc_sour={0,0,m_wid,m_wid};
    if (!IsVertical()) {
        OffsetRect(&rc_sour,m_wid*4,0);
    }
	RECT rc_dest;
	rc_dest=GetRect(SB_LINEUP);
	if ((rc_dest.right-rc_dest.left != rc_sour.right-rc_sour.left)
        ||(rc_dest.bottom-rc_dest.top != rc_sour.bottom-rc_sour.top)) {
		dc.StretchBlt(rc_dest.left,rc_dest.top,rc_dest.right-rc_dest.left,rc_dest.bottom-rc_dest.top,
			&memdc,
			rc_sour.left,rc_sour.top,rc_sour.right-rc_sour.left,rc_sour.bottom-rc_sour.top,
			SRCCOPY);
    } else {
		dc.BitBlt(rc_dest.left,rc_dest.top,m_wid,m_wid,&memdc,rc_sour.left,rc_sour.top,SRCCOPY);
    }
	rc_dest=GetRect(SB_LINEDOWN);
	OffsetRect(&rc_sour,m_wid,0);
	if ((rc_dest.right-rc_dest.left != rc_sour.right-rc_sour.left)
        ||(rc_dest.bottom-rc_dest.top != rc_sour.bottom-rc_sour.top)) {
		dc.StretchBlt(rc_dest.left,rc_dest.top,rc_dest.right-rc_dest.left,rc_dest.bottom-rc_dest.top,
			&memdc,
			rc_sour.left,rc_sour.top,rc_sour.right-rc_sour.left,rc_sour.bottom-rc_sour.top,
			SRCCOPY);
    } else {
		dc.BitBlt(rc_dest.left,rc_dest.top,m_wid,m_wid,&memdc,rc_sour.left,rc_sour.top,SRCCOPY);
    }
	rc_dest=GetRect(SB_THUMBTRACK);
	OffsetRect(&rc_sour,m_wid,0);
	DrawThumb(&dc,&rc_dest,&memdc,&rc_sour);
	OffsetRect(&rc_sour,m_wid,0);
	rc_dest=GetRect(SB_PAGEUP);
	TileBlt(&dc,&rc_dest,&memdc,&rc_sour);
	rc_dest=GetRect(SB_PAGEDOWN);
	TileBlt(&dc,&rc_dest,&memdc,&rc_sour);

	::SelectObject(memdc,old_bmp);
}

RECT CSkinScrollBar::GetImageRect(
    UINT uSBCode,
    int nState
) {
	int index=0;
    switch(uSBCode)	{
        case SB_LINEUP:
            index=0;
            break;
        case SB_PAGEUP:
            index=3;
            break;
        case SB_THUMBTRACK:
            index=2;
            break;
        case SB_PAGEDOWN:
            index=3;
            break;
        case SB_LINEDOWN:
            index=1;
            break;
    }
    if (!IsVertical()) {
        index+=4;
    }
	RECT rc_ret={m_wid*index,m_wid*nState,m_wid*(index+1),m_wid*(nState+1)};
	return rc_ret;
}

RECT CSkinScrollBar::GetRect(
    UINT uSBCode
) {
	SCROLLINFO si=m_si;
	if(si.nTrackPos==-1) si.nTrackPos=si.nPos;
	int inter_hei=m_hei-2*m_wid;
    if (inter_hei<0) {
        inter_hei=0;
    }
	int	slide_hei=si.nPage*inter_hei/(si.nMax-si.nMin+1);
    if (slide_hei<THUMB_MINSIZE) {
        slide_hei=THUMB_MINSIZE;
    }
    if (inter_hei<THUMB_MINSIZE) {
        slide_hei=0;
    }
    if ((si.nMax-si.nMin-si.nPage+1)==0) {
        slide_hei=0;
    }
	int empty_hei=inter_hei-slide_hei;
	int arrow_hei=m_wid;
    if (inter_hei==0) {
        arrow_hei=m_hei/2;
    }
	RECT rc_ret={0,0,m_wid,arrow_hei};
    if (uSBCode==SB_LINEUP) {
        goto end;
    }
	rc_ret.top=rc_ret.bottom;
    if ((si.nMax-si.nMin-si.nPage+1)==0) {
		rc_ret.bottom+=empty_hei/2;
    } else {
		rc_ret.bottom+=empty_hei*si.nTrackPos/(si.nMax-si.nMin-si.nPage+1);
    }
    if (uSBCode==SB_PAGEUP) {
        goto end;
    }
	rc_ret.top=rc_ret.bottom;
	rc_ret.bottom+=slide_hei;
    if (uSBCode==SB_THUMBTRACK) {
        goto end;
    }
	rc_ret.top=rc_ret.bottom;
	rc_ret.bottom=m_hei-arrow_hei;
    if (uSBCode==SB_PAGEDOWN) {
        goto end;
    }
	rc_ret.top=rc_ret.bottom;
	rc_ret.bottom=m_hei;
    if (uSBCode==SB_LINEDOWN) {
        goto end;
    }
end:
	if (!IsVertical()) {
		int t=rc_ret.left;
		rc_ret.left=rc_ret.top;
		rc_ret.top=t;
		t=rc_ret.right;
		rc_ret.right=rc_ret.bottom;
		rc_ret.bottom=t;
	}
	return rc_ret;
}

void CSkinScrollBar::TileBlt(
    CDC *pDestDC, 
    RECT *pDestRect, 
    CDC *pSourDC, 
    RECT *pSourRect
) {
	int sour_hei=pSourRect->bottom-pSourRect->top;
	int sour_wid=pSourRect->right-pSourRect->left;

	int y=pDestRect->top;
	while (y<pDestRect->bottom) {
		int nHei=sour_hei;
        if (y+nHei>pDestRect->bottom) {
            nHei=pDestRect->bottom-y;
        }

		int x=pDestRect->left;
		while (x<pDestRect->right) {
			int nWid=sour_wid;
            if (x+nWid>pDestRect->right) {
                nWid=pDestRect->right-x;
            }
			pDestDC->BitBlt(x,y,nWid,nHei,pSourDC,pSourRect->left,pSourRect->top,SRCCOPY);
			x+=nWid;
		}
		y+=nHei;
	}
}

void CSkinScrollBar::DrawThumb(
    CDC *pDestDC, 
    RECT *pDestRect, 
    CDC *pSourDC, 
    RECT *pSourRect
) {
    if (IsRectEmpty(pDestRect)) {
        return;
    }
	RECT rc_dest=*pDestRect,rc_sour=*pSourRect;
    if (IsVertical()) {
		ASSERT(pDestRect->bottom-pDestRect->top>=THUMB_MINSIZE);
		pDestDC->BitBlt(pDestRect->left,pDestRect->top,m_wid,THUMB_BORDER,pSourDC,pSourRect->left,pSourRect->top,SRCCOPY);
		pDestDC->BitBlt(pDestRect->left,pDestRect->bottom-THUMB_BORDER,m_wid,THUMB_BORDER,pSourDC,pSourRect->left,pSourRect->bottom-THUMB_BORDER,SRCCOPY);
		rc_dest.top+=THUMB_BORDER,rc_dest.bottom-=THUMB_BORDER;
		rc_sour.top+=THUMB_BORDER,rc_sour.bottom-=THUMB_BORDER;
		TileBlt(pDestDC,&rc_dest,pSourDC,&rc_sour);
	} else {
		ASSERT(pDestRect->right-pDestRect->left>=THUMB_MINSIZE);
		pDestDC->BitBlt(pDestRect->left,pDestRect->top,THUMB_BORDER,m_wid,pSourDC,pSourRect->left,pSourRect->top,SRCCOPY);
		pDestDC->BitBlt(pDestRect->right-THUMB_BORDER,pDestRect->top,THUMB_BORDER,m_wid,pSourDC,pSourRect->right-THUMB_BORDER,pSourRect->top,SRCCOPY);
		rc_dest.left+=THUMB_BORDER,rc_dest.right-=THUMB_BORDER;
		rc_sour.left+=THUMB_BORDER,rc_sour.right-=THUMB_BORDER;
		TileBlt(pDestDC,&rc_dest,pSourDC,&rc_sour);
	}
}

void CSkinScrollBar::OnLButtonDown(
    UINT nFlags, 
    CPoint point
) {
	SetCapture();
	UINT hit=HitTest(point);
	if (hit==SB_THUMBTRACK)	{
		m_drag=TRUE;
		m_pt_drag=point;
		m_si.nTrackPos=m_si.nPos;
		m_drag_pos=m_si.nPos;
	} else {
		m_clicked=hit;
		GetParent()->SendMessage(IsVertical()?WM_VSCROLL:WM_HSCROLL,MAKELONG(m_clicked,0),(LPARAM)m_hWnd);
		SetTimer(TIMERID_DELAY,TIME_DELAY,NULL);
		m_pause=FALSE;
        if (hit==SB_LINEUP||hit==SB_LINEDOWN) {
            DrawArrow(hit,2);
        }
	}
}

void CSkinScrollBar::OnMouseMove(
    UINT nFlags, 
    CPoint point
) {
	if (!m_trace && nFlags!=-1)	{
		m_trace=TRUE;
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE;
		tme.dwHoverTime = 1;
		m_trace = _TrackMouseEvent(&tme);
	}

    if (m_drag) {
		int inter_hei=m_hei-2*m_wid;
		int	slide_hei=m_si.nPage*inter_hei/(m_si.nMax-m_si.nMin+1);
        if (slide_hei<THUMB_MINSIZE) {
            slide_hei=THUMB_MINSIZE;
        }
        if (inter_hei<THUMB_MINSIZE) {
            slide_hei=0;
        }
		int empty_hei=inter_hei-slide_hei;
		int nDragLen=IsVertical()?point.y-m_pt_drag.y:point.x-m_pt_drag.x;
		int nSlide=(empty_hei==0)?0:(nDragLen*(int)(m_si.nMax-m_si.nMin-m_si.nPage+1)/empty_hei);
		int nNewTrackPos=m_drag_pos+nSlide;
		if (nNewTrackPos<m_si.nMin) {
			nNewTrackPos=m_si.nMin;
		} else if (nNewTrackPos>(int)(m_si.nMax-m_si.nMin-m_si.nPage+1)) {
			nNewTrackPos=m_si.nMax-m_si.nMin-m_si.nPage+1;
		}
		if (nNewTrackPos!=m_si.nTrackPos) {
			CDC *pDC=GetDC();
			CDC memdc;
			memdc.CreateCompatibleDC(pDC);
			HGDIOBJ old_bmp=SelectObject(memdc,m_bmp);
			RECT rc_thumb=GetRect(SB_THUMBTRACK);
			m_si.nTrackPos=nNewTrackPos;
			RECT rc_thumb1=GetRect(SB_THUMBTRACK);

			RECT rcSourSlide=GetImageRect(SB_PAGEUP,0);
			RECT rcSourThumb=GetImageRect(SB_THUMBTRACK,2);
			RECT rcOld;
			if (IsVertical()) {
				rcOld.left=0,rcOld.right=m_wid;
				if (rc_thumb1.bottom>rc_thumb.bottom) {
					rcOld.top=rc_thumb.top;
					rcOld.bottom=rc_thumb1.top;
				} else {
					rcOld.top=rc_thumb1.bottom;
					rcOld.bottom=rc_thumb.bottom;
				}
			} else {
				rcOld.top=0,rcOld.bottom=m_wid;
				if (rc_thumb1.right>rc_thumb.right) {
					rcOld.left=rc_thumb.left;
					rcOld.right=rc_thumb1.left;
				} else {
					rcOld.left=rc_thumb1.right;
					rcOld.right=rc_thumb.right;
				}
			}
			TileBlt(pDC,&rcOld,&memdc,&rcSourSlide);
			DrawThumb(pDC,&rc_thumb1,&memdc,&rcSourThumb);
			SelectObject(memdc,old_bmp);
			ReleaseDC(pDC);
			
			GetParent()->SendMessage(IsVertical()?WM_VSCROLL:WM_HSCROLL,MAKELONG(SB_THUMBTRACK,m_si.nTrackPos),(LPARAM)m_hWnd);
		}
	} else if (m_clicked!=-1) {
		CRect rc=GetRect(m_clicked);
		m_pause=!rc.PtInRect(point);
		if (m_clicked==SB_LINEUP||m_clicked==SB_LINEDOWN) {
			DrawArrow(m_clicked,m_pause?0:2);
		}
	} else {
		UINT hit=HitTest(point);
        if (hit!=m_ht_prev) {
			if (m_ht_prev!=-1) {
				if (m_ht_prev==SB_THUMBTRACK) {
					CDC *pDC=GetDC();
					CDC memdc;
					memdc.CreateCompatibleDC(pDC);
					HGDIOBJ old_bmp=SelectObject(memdc,m_bmp);
					RECT rc_dest=GetRect(SB_THUMBTRACK);
					RECT rc_sour=GetImageRect(SB_THUMBTRACK,0);
					DrawThumb(pDC,&rc_dest,&memdc,&rc_sour);
					ReleaseDC(pDC);
					SelectObject(memdc,old_bmp);
				} else if (m_ht_prev==SB_LINEUP||m_ht_prev==SB_LINEDOWN) {
					DrawArrow(m_ht_prev,0);
				}
			}
			if (hit!=-1) {
				if (hit==SB_THUMBTRACK) {
					CDC *pDC=GetDC();
					CDC memdc;
					memdc.CreateCompatibleDC(pDC);
					HGDIOBJ old_bmp=SelectObject(memdc,m_bmp);
					RECT rc_dest=GetRect(SB_THUMBTRACK);
					RECT rc_sour=GetImageRect(SB_THUMBTRACK,1);
					DrawThumb(pDC,&rc_dest,&memdc,&rc_sour);
					ReleaseDC(pDC);
					SelectObject(memdc,old_bmp);
				} else if (hit==SB_LINEUP||hit==SB_LINEDOWN) {
					DrawArrow(hit,1);
				}
			}
			m_ht_prev=hit;
		}
	}
}

void CSkinScrollBar::OnLButtonUp(
    UINT nFlags, 
    CPoint point
) {
	ReleaseCapture();
	if (m_drag) {
		m_drag=FALSE;
		GetParent()->SendMessage(IsVertical()?WM_VSCROLL:WM_HSCROLL,MAKELONG(SB_THUMBPOSITION,m_si.nTrackPos),(LPARAM)m_hWnd);
		CDC *pDC=GetDC();
		CDC memdc;
		memdc.CreateCompatibleDC(pDC);
		HGDIOBJ old_bmp=SelectObject(memdc,m_bmp);
		if (m_si.nTrackPos != m_si.nPos) {
			RECT rc_thumb=GetRect(SB_THUMBTRACK);
			RECT rc_sour={m_wid*3,0,m_wid*4,m_wid};
            if (!IsVertical()) {
                OffsetRect(&rc_sour,m_wid*4,0);
            }
			TileBlt(pDC,&rc_thumb,&memdc,&rc_sour);
		}
		m_si.nTrackPos=-1;

		RECT rc_thumb=GetRect(SB_THUMBTRACK);
		RECT rc_sour={m_wid*2,0,m_wid*3,m_wid};
        if (PtInRect(&rc_thumb,point)) {
            OffsetRect(&rc_sour,0,m_wid);
        }
        if (!IsVertical()) {
            OffsetRect(&rc_sour,m_wid*4,0);
        }
		DrawThumb(pDC,&rc_thumb,&memdc,&rc_sour);
		SelectObject(memdc,old_bmp);
		ReleaseDC(pDC);
	} else if (m_clicked!=-1) {
		if (m_notify) {
			KillTimer(TIMERID_NOTIFY);
			m_notify=FALSE;
		} else {
			KillTimer(TIMERID_DELAY);
		}
        if (m_clicked==SB_LINEUP||m_clicked==SB_LINEDOWN) {
            DrawArrow(m_clicked,0);
        }
		m_clicked=-1;
	}
}

void CSkinScrollBar::OnTimer(
    UINT_PTR nIDEvent
) {
    if (nIDEvent==TIMERID_DELAY) {
		m_notify=TRUE;
		nIDEvent=TIMERID_NOTIFY;
		KillTimer(TIMERID_DELAY);
		SetTimer(TIMERID_NOTIFY,TIME_INTER,NULL);
	}
    if (nIDEvent==TIMERID_NOTIFY && !m_pause) {
        ASSERT(m_clicked!=-1 && m_clicked!=SB_THUMBTRACK);

        switch(m_clicked) {
            case SB_LINEUP:
                if (m_si.nPos==m_si.nMin) {
                    KillTimer(TIMERID_NOTIFY);
                    break;
                }
                GetParent()->SendMessage(IsVertical()?WM_VSCROLL:WM_HSCROLL,MAKELONG(SB_LINEUP,0),(LPARAM)m_hWnd);
                break;
            case SB_LINEDOWN:
                if (m_si.nPos==m_si.nMax) {
                    KillTimer(TIMERID_NOTIFY);
                    break;
                }
                GetParent()->SendMessage(IsVertical()?WM_VSCROLL:WM_HSCROLL,MAKELONG(SB_LINEDOWN,0),(LPARAM)m_hWnd);
                break;
            case SB_PAGEUP:
            case SB_PAGEDOWN:
                {
                    CPoint pt;
                    GetCursorPos(&pt);
                    ScreenToClient(&pt);
                    CRect rc=GetRect(SB_THUMBTRACK);
                    if (rc.PtInRect(pt)) {
                        KillTimer(TIMERID_NOTIFY);
                        break;
                    }
                    GetParent()->SendMessage(IsVertical()?WM_VSCROLL:WM_HSCROLL,MAKELONG(m_clicked,0),(LPARAM)m_hWnd);
                }
                break;
            default:
                ASSERT(FALSE);
                break;
        }
    }
}

void CSkinScrollBar::DrawArrow(
    UINT uArrow, 
    int nState
) {
	ASSERT(uArrow==SB_LINEUP||uArrow==SB_LINEDOWN);
	CDC *pDC=GetDC();
	CDC memdc ;
	memdc.CreateCompatibleDC(pDC);
	HGDIOBJ old_bmp=::SelectObject(memdc,m_bmp);
	
	RECT rc_dest=GetRect(uArrow);
	RECT rc_sour=GetImageRect(uArrow,nState);
	if ((rc_dest.right-rc_dest.left != rc_sour.right-rc_sour.left)
        ||(rc_dest.bottom-rc_dest.top != rc_sour.bottom-rc_sour.top)) {
		pDC->StretchBlt(rc_dest.left,rc_dest.top,rc_dest.right-rc_dest.left,rc_dest.bottom-rc_dest.top,
			&memdc,
			rc_sour.left,rc_sour.top,rc_sour.right-rc_sour.left,rc_sour.bottom-rc_sour.top,
			SRCCOPY);
    } else {
		pDC->BitBlt(rc_dest.left,rc_dest.top,m_wid,m_wid,&memdc,rc_sour.left,rc_sour.top,SRCCOPY);
    }

	ReleaseDC(pDC);
	::SelectObject(memdc,old_bmp);
}


LRESULT CSkinScrollBar::OnMouseLeave(
    WPARAM wparam, 
    LPARAM lparam
) {
	m_trace = FALSE;
	OnMouseMove(-1,CPoint(-1,-1));
	return 0;
}


LRESULT CSkinScrollBar::WindowProc(
    UINT message, 
    WPARAM wParam, 
    LPARAM lParam
) {
    if (message==WM_LBUTTONDBLCLK) {
        return 1;
    }
    if (message==SBM_SETSCROLLINFO) {
		BOOL bRedraw=wParam;
		LPSCROLLINFO lpScrollInfo=(LPSCROLLINFO)lParam;
        if (lpScrollInfo->fMask&SIF_PAGE) {
            m_si.nPage=lpScrollInfo->nPage;
        }
        if (lpScrollInfo->fMask&SIF_POS) {
            m_si.nPos=lpScrollInfo->nPos;
        }
        if (lpScrollInfo->fMask&SIF_RANGE) {
			m_si.nMin=lpScrollInfo->nMin;
			m_si.nMax=lpScrollInfo->nMax;
		}
		if (bRedraw) {
			CDC *pDC=GetDC();
			CDC memdc;
			memdc.CreateCompatibleDC(pDC);
			HGDIOBJ old_bmp=::SelectObject(memdc,m_bmp);

			RECT rc_sour=GetImageRect(SB_PAGEUP);
			RECT rc_dest=GetRect(SB_PAGEUP);
			TileBlt(pDC,&rc_dest,&memdc,&rc_sour);
			rc_dest=GetRect(SB_THUMBTRACK);
			rc_sour=GetImageRect(SB_THUMBTRACK);
			DrawThumb(pDC,&rc_dest,&memdc,&rc_sour);
			rc_dest=GetRect(SB_PAGEDOWN);
			rc_sour=GetImageRect(SB_PAGEDOWN);
			TileBlt(pDC,&rc_dest,&memdc,&rc_sour);
			::SelectObject(memdc,old_bmp);
			ReleaseDC(pDC);
		}
		return TRUE;
	}
	if (message==SBM_GETSCROLLINFO) {
		LPSCROLLINFO lpScrollInfo=(LPSCROLLINFO)lParam;
		int mask=lpScrollInfo->fMask;
        if (mask&SIF_PAGE) {
            lpScrollInfo->nPage=m_si.nPage;
        }
        if (mask&SIF_POS) {
            lpScrollInfo->nPos=m_si.nPos;
        }
        if (mask&SIF_TRACKPOS) {
            lpScrollInfo->nTrackPos=m_si.nTrackPos;
        }
		if (mask&SIF_RANGE) {
			lpScrollInfo->nMin=m_si.nMin;
			lpScrollInfo->nMax=m_si.nMax;
		}
		return TRUE;
	}
	return CScrollBar::WindowProc(message, wParam, lParam);
}