// MainFrm.h : interface of the CMainFrame class
//


#pragma once

class CCustomFrame : public CFrameWnd
{
	
public:
	CCustomFrame();
protected: 
	DECLARE_DYNAMIC(CCustomFrame)
CWnd *c_childWnd;
// Operations
public:
	virtual ~CCustomFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:  
	//The enum of statistics used
	struct wind_st{
		int titlb_sz;
		int bdr_wdth;
		int frm_clp_wdth;
		int ico_size;
	};
	struct frame_rects{
		CRect r_Mrect;
		CRect r_Trect;
		CRect r_Lrect;
		CRect r_Rrect;
		CRect r_Brect;
		CRect r_TLrect;
		CRect r_TRrect;
		CRect r_BLrect;
		CRect r_BRrect;
		CRect r_Close;
		CRect r_Minimize;
		CRect r_Maximize;
		CRect r_Move;
	};
	
	BOOL b_maximized;
	//The window region used
	CRgn m_CustomRgn;
	//Store the previous rect for restore
	CRect m_PrevRect;
	wind_st winStats;
	frame_rects r_windRects;
	COLORREF cr_bkgnd;
	COLORREF cr_frm;
	CStatic st_winNm;
// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
	//Used windows event driven methods
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);	
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

private:
	int ProcessResize(CPoint point);
	int maximize(void);
	void restore(void);
	void close_window(void);	
	void SetWindowRects(void);
	bool HandleCutomeFrame(CPoint point);
	void HandleCustomeFrameCursor(CPoint point);
};


