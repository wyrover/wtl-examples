
// MiniNewsDlg.h : 头文件
//

#pragma once
#include "explorer1.h"


// CMiniNewsDlg 对话框
class CMiniNewsDlg : public CDialog
{
// 构造
public:
	CMiniNewsDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MININEWS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
public:
	//caizhiming

	//自绘标题栏、边框、最小化按钮、最大化按钮和关闭按钮等界面所需变量
	int m_nWinWidth;//窗口宽度，包括边框，
	int m_nWinHeight;//窗口高度，
	int m_nFrameCY;//获取对话边框的高度
	int m_nFrameCX;//获取对话边框的宽度
	int m_nBorderCY;//对话框边框高度
	int m_nBorderCX;//对话框边框宽度
	int m_nTitleBarCY ;//对话框标题栏高度
	int m_nTitleBarCX;//对话框标题栏宽度
	bool m_bMouseOnMinBtn;//鼠标是否在最小化按钮区域内
	bool m_bMouseOnCloseBtn;//鼠标是否在关闭按钮区域内
	bool m_bMouseOnMoreBtn;//鼠标是否在更多按钮区域内
	int m_nWinTitleHeight;//标题栏高度（含菜单工具按钮）

	void DrawDialog();//绘制对话框内容
	CString m_strTitle;
	COLORREF m_bkColor;//对话框背景颜色
	void SetTitleText(CString strTitle);
	void DisplayBmp(int x,int y,int w,int h,int nID); //在指定位置显示bmp位图图像
	void DrawTitleText();
public:
	CExplorer1 m_webBrowser;
// 实现
protected:
	HICON m_hIcon;


	afx_msg void OnNcPaint();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);

	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
	afx_msg void OnNcMouseLeave();
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

};
