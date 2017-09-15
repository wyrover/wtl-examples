#ifndef __ALERT_BUTTON_CLOSE_H__
#define __ALERT_BUTTON_CLOSE_H__

#pragma once

#include "AlertButton.h"

namespace WTL
{


/*
 The close alert button is an alert button that displays an X sight for closing.
*/
class CAlertButtonClose : public CAlertButton
{

public:
    DECLARE_WND_SUPERCLASS(_T("ALERT_BUTTON_CLOSE"), CAlertButton::GetWndClassName());
    BEGIN_MSG_MAP(CAlertButtonClose)
    CHAIN_MSG_MAP(CAlertButton)
    END_MSG_MAP()



public:
    CAlertButtonClose(HWND hWnd = NULL) : m_penBlack(Color(0, 0, 0))
    {
        m_hWnd = hWnd;
        m_penBlack.SetAlignment(PenAlignmentInset);
    }

    virtual ~CAlertButtonClose() {};

    virtual void OnDrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
    {
        CDCHandle dc(lpDrawItemStruct->hDC);
        Graphics g(lpDrawItemStruct->hDC);
        CRect rc(lpDrawItemStruct->rcItem);
        Rect rect(rc.left, rc.top, rc.Width(), rc.Height());

        if (m_fMouseOver && m_fHighlightBackground) {
            g.FillRectangle(&m_brHighlight, rect);
        }

        int x = (rc.Width() - 8) / 2;
        int y = (rc.Height() - 7) / 2;
        // top,left -> bottom,right
        g.DrawLine(&m_penBlack, x , y , x + 7, y + 7);
        g.DrawLine(&m_penBlack, x + 1, y, x + 8, y + 7);
        // bottom,left -> top,right
        g.DrawLine(&m_penBlack, x, y + 7, x + 7, y);
        g.DrawLine(&m_penBlack, x + 1, y + 7, x + 8, y);

        if (m_fMouseOver) {
            g.DrawRectangle(&m_penBlack, rect.GetLeft(), rect.GetTop(), rect.Width - 1, rect.Height - 1);
        }
    }

protected:
    Pen m_penBlack;
};

};
#endif //__ALERT_BUTTON_CLOSE_H__
