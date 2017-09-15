#ifndef _MEMDC_H_
#define _MEMDC_H_

class CMemDC : public CDC 
{
private:
	CBitmap*	m_bitmap;
	CBitmap*	m_old_bitmap;
	CDC*		m_pDC;
	CRect		m_rc_bounds;
public:
	CMemDC(CDC* pDC, const CRect& rcBounds);
	~CMemDC() ;
};

#endif