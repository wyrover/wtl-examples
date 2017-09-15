#if !defined(AFX_SKINSCROLLBAR_H__F5B158D2_0277_45F4_B61A_4F41E69C8CFA__INCLUDED_)
#define AFX_SKINSCROLLBAR_H__F5B158D2_0277_45F4_B61A_4F41E69C8CFA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif
class CSkinScrollBar : public CScrollBar
{
public:
	CSkinScrollBar();
	HBITMAP	m_bmp;
	int		m_wid;
	int		m_frm_hei;
	int		m_hei;
	SCROLLINFO	m_si;
	BOOL		m_drag;
	CPoint		m_pt_drag;
	int			m_drag_pos;
	UINT		m_clicked;
	BOOL		m_notify;
	UINT		m_ht_prev;
	BOOL		m_pause;
	BOOL		m_trace;

public:
	void DrawArrow(UINT uArrow,int nState);
	void SetBitmap(HBITMAP bmp);
	BOOL IsVertical();
	virtual ~CSkinScrollBar();

protected:
    virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	void DrawThumb(CDC *pDestDC, RECT *pDestRect, CDC *pSourDC, RECT *pSourRect);
	void TileBlt(CDC *pDestDC,RECT *pDestRect,CDC *pSourDC,RECT *pSourRect);
	RECT GetRect(UINT uSBCode);
	RECT GetImageRect(UINT uSBCode,int nState=0);
	UINT HitTest(CPoint pt);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);

	DECLARE_MESSAGE_MAP()
};
#endif
