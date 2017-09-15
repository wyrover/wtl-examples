#if !defined(AFX_SKINSCROLLWND_H__891A5F44_7A55_46DF_8BD7_9C454283CE40__INCLUDED_)
#define AFX_SKINSCROLLWND_H__891A5F44_7A55_46DF_8BD7_9C454283CE40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif
#include "SkinScrollBar.h"

class CSkinScrollWnd : public CWnd
{
public:
	CSkinScrollWnd();
	int			m_scroll_wid;
	CSkinScrollBar	m_sb_horz,m_sb_vert;
	CWnd		m_wnd_limit;
	HBITMAP		m_bmp_scroll;
	BOOL		m_bop;
	int			m_angle_type;
	WNDPROC		m_fun_old_proc;
	BOOL SkinWindow(CWnd *pWnd,HBITMAP bmp_scroll);
	virtual ~CSkinScrollWnd();

protected:
	afx_msg LRESULT OnDestMove(WPARAM wParam,LPARAM lParam);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()
};

extern "C" BOOL UnskinWndScroll(CWnd *pWnd);

extern "C" CSkinScrollWnd* SkinWndScroll(CWnd *pWnd,HBITMAP hBmpScroll);

#endif
