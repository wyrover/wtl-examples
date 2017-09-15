#if !defined(AFX_SKINHEADERCTRL_H__8B0847B1_B4E6_4372_A62D_038582FFEA5C__INCLUDED_)
#define AFX_SKINHEADERCTRL_H__8B0847B1_B4E6_4372_A62D_038582FFEA5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

#define CLICK_DOWN 1
#define CLICKED_UP 0
#define MAX_BUF 256
#define MAX_TEXT 255

class CSkinHeaderCtrl : public CHeaderCtrl
{
public:
	CSkinHeaderCtrl();
	virtual ~CSkinHeaderCtrl();
private:
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    BOOL m_mouse_click_header;
    BOOL m_mouse_moving;
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    DECLARE_MESSAGE_MAP()
};

#endif
