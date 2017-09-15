// PieChartDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "PieChartWnd.h"
// CPieChartDlg dialog
class CPieChartDlg : public CDialog
{
// Construction
public:
    CPieChartDlg(CWnd* pParent = NULL); // standard constructor

// Dialog Data
    enum { IDD = IDD_PIECHART_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    CPieChartWnd m_pieChart;
// Implementation
protected:
    HICON m_hIcon;

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
public:
    double m_Value;
public:
    CString m_Item;
public:
    CString m_Label;
public:
    CString m_LabelUpd;
public:
    double m_ValueUpd;
public:
    CComboBox m_GrLight;
public:
    CComboBox m_GrDark;
public:
    CSliderCtrl m_SliderGrLight;
public:
    CSliderCtrl m_SliderGrDark;
public:
    CSliderCtrl m_SliderStAngle;
public:
    CSliderCtrl m_SliderIncAngle;
public:
    CComboBox m_ClrPicker;
public:
    CComboBox m_FntPicker;
public:
    CEdit m_Title;
public:
    CComboBox m_Styles;
public:
    CComboBox m_Sort;
    COLORREF m_ItemColor;
public:
    afx_msg void OnBnClickedColoritem();
public:
    afx_msg void OnBnClickedAdd();
public:
    afx_msg void OnSize(UINT nType, int cx, int cy);
public:
    afx_msg void OnBnClickedUpdlabel();
public:
    afx_msg void OnBnClickedUpdvalue();
public:
    afx_msg void OnBnClickedUpdcolor();
public:
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
public:
    afx_msg void OnBnClickedColorset();
public:
    afx_msg void OnBnClickedFontset();
public:
    afx_msg void OnBnClickedTitleset();
public:
    afx_msg void OnBnClickedSave();
public:
    CString m_TitleStr;
public:
    afx_msg void OnCbnSelchangeStyle();
public:
    afx_msg void OnCbnSelchangeSort();
public:
    float m_Height;
public:
    afx_msg void OnBnClickedHeightset();
public:
    afx_msg void OnBnClickedRemove();
public:
    void AddTestItems(void);
public:
    afx_msg void OnCbnSelchangeGrdark();
public:
    afx_msg void OnCbnSelchangeGrlight();
public:
    CComboBox m_ItmSeperate;
public:
    CComboBox m_ItmTransparent;
public:
    CSliderCtrl m_Seperate;
public:
    CSliderCtrl m_Transparent;
public:
    CSliderCtrl m_HorizontalPos;
};
