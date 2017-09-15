// XuBitmap.h: interface for the CXuBitmap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XUBITMAP_H__DC80AD66_EBA8_4EA1_BF26_22D6C0586C8E__INCLUDED_)
#define AFX_XUBITMAP_H__DC80AD66_EBA8_4EA1_BF26_22D6C0586C8E__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000

#include "EnBitmap.h"

class CXuBitmap : public CEnBitmap
{
public:
    CXuBitmap();
    virtual ~CXuBitmap();

    BOOL Draw(CDC *pDC, LPRECT r);
    //draw sub bmp to special point
    BOOL Draw(CDC *pDC, int x, int y, LPRECT sr);
    BOOL Draw(CDC *pDC, int x, int y, LPRECT sr, COLORREF colTrans, BOOL bTrans);

    BOOL StretchDraw(CDC *pDC, LPRECT tr, LPRECT sr);
    BOOL StretchDraw(CDC *pDC, LPRECT r);

    int  Width()
    {
        return GetWidth();
    }
    int  Height()
    {
        return GetHeight();
    }

    void Attach(HBITMAP hbmp)
    {
        CBitmap::Attach(hbmp);
    }

    BOOL LoadBitmap(UINT nResName, HMODULE hInst = NULL, COLORREF crBack = 0)
    {
        if (m_hBitmap) DeleteObject();

        return LoadImage(nResName, RT_BITMAP, hInst, crBack);
    }
    BOOL LoadBitmap(LPCTSTR lpctImagePath, COLORREF crBack = 0)
    {
        if (m_hBitmap) DeleteObject();

        return LoadImage(lpctImagePath, crBack);
    }

    BOOL DrawTransparent(CDC * pDC, int x, int y, COLORREF crColour);
    HRGN CreateRgnFromFile(COLORREF color);
};

#endif // !defined(AFX_XUBITMAP_H__DC80AD66_EBA8_4EA1_BF26_22D6C0586C8E__INCLUDED_)
