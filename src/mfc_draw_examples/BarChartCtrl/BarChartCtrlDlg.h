// BarChartCtrlDlg.h : header file
//

#if !defined(AFX_BARCHARTCTRLDLG_H__5D1E206A_C3C5_42A4_999B_FEC550A5902B__INCLUDED_)
#define AFX_BARCHARTCTRLDLG_H__5D1E206A_C3C5_42A4_999B_FEC550A5902B__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CBarChartCtrlDlg dialog
#include "BarChart.h"

class CBarChartCtrlDlg : public CDialog
{
// Construction
public:
    CBarChartCtrlDlg(CWnd* pParent = NULL); // standard constructor

// Dialog Data
    //{{AFX_DATA(CBarChartCtrlDlg)
    enum { IDD = IDD_BARCHARTCTRL_DIALOG };
    BOOL    m_bShowGrid;
    BOOL    m_bShowText;
    BOOL    m_bShowLabel;
    BOOL    m_bScale;
    int     m_nRemIndex;
    CString m_szLabel;
    CString m_szValue;
    BOOL    m_bShowTip;
    int     m_nGridHor;
    int     m_nGridVer;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CBarChartCtrlDlg)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    HICON m_hIcon;
    CBarChart   m_chart;
    CBrush  m_brushBK;

    // Generated message map functions
    //{{AFX_MSG(CBarChartCtrlDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnCreate();
    afx_msg void OnRandom();
    afx_msg void OnShowGrid();
    afx_msg void OnShowBarText();
    afx_msg void OnShowLabels();
    afx_msg void OnScale();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnValue();
    afx_msg void OnPercent();
    afx_msg void OnClearAll();
    afx_msg void OnRemoveAt();
    afx_msg void OnAddBar();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    virtual void OnCancel();
    afx_msg void OnPrint();
    afx_msg void OnShowTooltip();
    virtual void OnOK();
    afx_msg void OnReadFromDatabase();
    afx_msg void OnSave();
    afx_msg void OnDeltaposSpinGridVer(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnDeltaposSpinGridHor(NMHDR* pNMHDR, LRESULT* pResult);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BARCHARTCTRLDLG_H__5D1E206A_C3C5_42A4_999B_FEC550A5902B__INCLUDED_)
