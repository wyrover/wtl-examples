#pragma once
#include "XListControl.h"
#include "SkinScrollWnd.h"
#include "SkinScrollBar.h"
#include "afxcmn.h"

#define COLOR_COMMON_TEXT   RGB(255,255,255)
#define INIT_NUMBER -1
#define DEFAULT_TIME 0
#define DEFAULT_MODE 0
#define FAILURE 1
#define ONE_HEADER_WIDTH 30
#define ALL_HEADER_WIDTH 500

// CredrawListDemoDlg dialog
class CredrawListDemoDlg : public CDialog
{
// Construction
public:
	CredrawListDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_REDRAWLISTDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	afx_msg void OnCustomdrawList ( NMHDR* pNMHDR, LRESULT* pResult );

private:
	 CXListControl m_pat_list;
	 HBITMAP m_bitmap_scrollbar;
	 afx_msg void OnBnClickedButton1();
	 afx_msg void OnLvnMarqueeBegin(NMHDR *pNMHDR, LRESULT *pResult);
	 afx_msg void OnLvnItemChangeList(NMHDR *pNMHDR, LRESULT *pResult);
	 afx_msg void OnLvnItemChangingList(NMHDR *rNMHDR, LRESULT *pResult);
	 afx_msg void OnLvnBeginDragList(NMHDR *pNMHDR, LRESULT *pResult);
	 afx_msg void OnLvnBeginRDragList(NMHDR *pNMHDR, LRESULT *pResult);
	 afx_msg void OnTimer(UINT_PTR nIDEvent);
	 afx_msg void OnNMSetfocusList(NMHDR *pNMHDR, LRESULT *pResult);
	 afx_msg void OnNMKillfocusList(NMHDR *pNMHDR, LRESULT *pResult);
	 afx_msg void OnHdnItemchangingList(NMHDR *pNMHDR, LRESULT *pResult);
	 afx_msg void OnHdnItemchangList(NMHDR *pNMHDR, LRESULT *pResult);
	 afx_msg void OnLvnKeyDown(NMHDR *pNMHDR, LRESULT *pResult);
	 afx_msg void OnNMClickPatientListControl(NMHDR *pNMHDR, LRESULT *pResult);
	 void ListSelectedProc(int mode);
	 int GetNowItemRow(POINT pt, CRect r, int mode);
	 BOOL  PreTranslateMessage(MSG* pMsg);
	 void ListClickedProc();
	 void OnStopTimer();

public:
	BOOL IsListItemEmpty(int num);
	UINT AllListItemNumber();
	CListCtrl m_test_list;

private:
	int m_timer;
	int m_first_list_selected;
    int m_first_change_list_select;
};
