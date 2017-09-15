#include "stdafx.h"
#include "SkinHeaderCtrl.h"
#include "memdc.h"
#include "resource.h"

CSkinHeaderCtrl::CSkinHeaderCtrl(
) {
    m_mouse_click_header = CLICKED_UP;
    m_mouse_moving = FALSE;
}

CSkinHeaderCtrl::~CSkinHeaderCtrl(
) {
}


BEGIN_MESSAGE_MAP(CSkinHeaderCtrl, CHeaderCtrl)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
    ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

void CSkinHeaderCtrl::OnPaint(
) {
    CPaintDC dc(this);
    CRect rect, rect_item, client_rect;
    GetClientRect(&rect);
    GetClientRect(&client_rect);
    CMemDC mem_dc(&dc, rect);

    CDC bitmap_dc;
    bitmap_dc.CreateCompatibleDC(&dc);

    CBitmap bitmap_span;
    bitmap_span.LoadBitmap(IDB_COLUMNHEADER_START);
    CBitmap* old_bitmap_span = bitmap_dc.SelectObject(&bitmap_span);
    for (int v=0; v<rect.Width(); v++) {
        mem_dc.BitBlt((rect.left+2)+(v*1), 0, 1, 22, &bitmap_dc,0,0,SRCCOPY);
    }
    bitmap_dc.SelectObject(old_bitmap_span);
    bitmap_span.DeleteObject();

    int item_number = GetItemCount();

    CBitmap bitmap;
    CBitmap bitmap2;
    CBitmap bitmap3;

    if (m_mouse_click_header == CLICKED_UP || m_mouse_moving == TRUE) {//表头正常状态
        bitmap.LoadBitmap(IDB_COLUMNHEADER_START);
        bitmap2.LoadBitmap(IDB_COLUMNHEADER_SPAN);
        bitmap3.LoadBitmap(IDB_COLUMNHEADER_END); 

    } else {//表头处于点击状态，并且不是表头移动状态
        bitmap.LoadBitmap(IDB_COLUMNHEADER_START_CLICKED);
        bitmap2.LoadBitmap(IDB_COLUMNHEADER_SPAN_CLICKED);
        bitmap3.LoadBitmap(IDB_COLUMNHEADER_END_CLICKED);
    }

    for(int i = 0; i <item_number; i++) {
        TCHAR buf1[MAX_BUF];
        HD_ITEM hditem1;

        hditem1.mask = HDI_TEXT | HDI_FORMAT | HDI_ORDER;
        hditem1.pszText = buf1;
        hditem1.cchTextMax = MAX_TEXT;
        GetItem( i, &hditem1 );

        GetItemRect(i, &rect);

        CBitmap* old_bitmap = NULL;

		//make sure we draw the start piece
		//on the first item so it has a left border

		//For the following items we will just use the
		//right border of the previous items as the left
		//border
        if (hditem1.iOrder==0) {
            old_bitmap = bitmap_dc.SelectObject(&bitmap);
            mem_dc.BitBlt(rect.left,rect.top,2,22,&bitmap_dc,0,0,SRCCOPY);
        } else {
            mem_dc.BitBlt(rect.left-3,rect.top,2,22,&bitmap_dc,0,0,SRCCOPY);
            old_bitmap = bitmap_dc.SelectObject(&bitmap2);
            mem_dc.BitBlt(rect.left+1,rect.top,1,22,&bitmap_dc,0,0,SRCCOPY);
        }

        bitmap_dc.SelectObject(old_bitmap);

		//span the bitmap for the width of the column header item
        int width = rect.Width() - 4;

        CBitmap* old_bitmap2 = bitmap_dc.SelectObject(&bitmap2);
        for (int v=0; v<width; v++) {
            mem_dc.BitBlt((rect.left+2)+(v*1), 0, 1, 22, &bitmap_dc,0,0,SRCCOPY);
        }

        bitmap_dc.SelectObject(old_bitmap2);

		//draw the end piece of the column header
        CBitmap* old_bitmap3 = bitmap_dc.SelectObject(&bitmap3);
        mem_dc.BitBlt((rect.right-2), 0, 2, 22, &bitmap_dc,0,0,SRCCOPY);
        bitmap_dc.SelectObject(old_bitmap3);

		//Get all the info for the current
		//item so we can draw the text to it
		//in the desired font and style
        DRAWITEMSTRUCT	draw_item_struct;
        GetItemRect(i, &rect_item);

        draw_item_struct.CtlType		= 100;
        draw_item_struct.hDC			= dc.GetSafeHdc();
        draw_item_struct.itemAction	= ODA_DRAWENTIRE; 
        draw_item_struct.hwndItem 	= GetSafeHwnd(); 
        draw_item_struct.rcItem	= rect_item;
        draw_item_struct.itemID	= i;

        UINT format = DT_SINGLELINE | DT_NOPREFIX | DT_TOP | DT_END_ELLIPSIS ;

        CFont font;
        LOGFONT lf;
        memset(&lf, 0, sizeof(LOGFONT));
        lf.lfHeight = 20;//字体大小
        strcpy((char *)lf.lfFaceName, "Sevenet 7");
        font.CreateFontIndirect(&lf);
        CFont* def_font = mem_dc.SelectObject(&font);

        mem_dc.SetBkMode(TRANSPARENT);
        mem_dc.SetTextColor(RGB(255, 255, 255));
        if (m_mouse_click_header == CLICKED_UP || m_mouse_moving == TRUE) {	//实现单机表头的时候字体下移一个像素
            rect_item.DeflateRect(8,2,2,2);//字体显示
        } else {
            rect_item.DeflateRect(9,3,2,2);
        }

        TCHAR buf[256];
        HD_ITEM hditem;

        hditem.mask = HDI_TEXT | HDI_FORMAT | HDI_ORDER;
        hditem.pszText = buf;
        hditem.cchTextMax = 255;
        GetItem( draw_item_struct.itemID, &hditem );

        mem_dc.DrawText(buf, &rect_item, format);
        mem_dc.SelectObject(def_font);
        font.DeleteObject();
    }
}

BOOL CSkinHeaderCtrl::OnEraseBkgnd(
    CDC* pDC
) {
	return false;	
}

void CSkinHeaderCtrl::OnLButtonUp(
    UINT nFlags, 
    CPoint point
) {
    m_mouse_click_header = CLICKED_UP;
    m_mouse_moving = FALSE;
    CHeaderCtrl::OnLButtonUp(nFlags, point);
}

void CSkinHeaderCtrl::OnLButtonDown(
    UINT nFlags, 
    CPoint point
) {
    m_mouse_click_header = CLICK_DOWN;
    CHeaderCtrl::OnLButtonDown(nFlags, point);
}

void CSkinHeaderCtrl::OnMouseMove(
    UINT nFlags, 
    CPoint point
) {
    if (m_mouse_click_header == CLICKED_UP) {
        return;
    }
    m_mouse_moving = TRUE;
    CHeaderCtrl::OnMouseMove(nFlags, point);
}