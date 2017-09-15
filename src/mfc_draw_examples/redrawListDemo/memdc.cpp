
#include "stdafx.h"
#include "memdc.h"

CMemDC::CMemDC(
    CDC *pDC, 
    const CRect &rc_bounds
) {
    CreateCompatibleDC(pDC);
    m_bitmap = new CBitmap;
    m_bitmap->CreateCompatibleBitmap(pDC, rc_bounds.Width(), rc_bounds.Height());
    m_old_bitmap = SelectObject(m_bitmap);
    m_pDC = pDC;
    m_rc_bounds = rc_bounds;
}

CMemDC::~CMemDC(
) {
    m_pDC->BitBlt(m_rc_bounds.left, m_rc_bounds.top, m_rc_bounds.Width(), m_rc_bounds.Height(), 
        this, m_rc_bounds.left, m_rc_bounds.top, SRCCOPY);
    SelectObject(m_old_bitmap);
    if (m_bitmap != NULL) {
        delete m_bitmap;
    }
}