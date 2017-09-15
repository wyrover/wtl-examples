// MFCDlgDemoDlg.h : header file
//

#if !defined(AFX_MFCDLGDEMODLG_H__8EAD6216_4049_49A6_884D_48D9B62C63F5__INCLUDED_)
#define AFX_MFCDLGDEMODLG_H__8EAD6216_4049_49A6_884D_48D9B62C63F5__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000

#include "WndShadow/WndShadow.h"

/////////////////////////////////////////////////////////////////////////////
// CMFCDlgDemoDlg dialog

class CMFCDlgDemoDlg : public CDialog
{
// Construction
public:
    CMFCDlgDemoDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CMFCDlgDemoDlg)
    enum { IDD = IDD_MFCDLGDEMO_DIALOG };
    CSliderCtrl m_ColorRCtrl;
    CSliderCtrl m_ColorGCtrl;
    CSliderCtrl m_ColorBCtrl;
    CSliderCtrl m_SizeCtrl;
    CSliderCtrl m_SharpnessCtrl;
    CSliderCtrl m_DarknessCtrl;
    CSliderCtrl m_PosXCtrl;
    CSliderCtrl m_PosYCtrl;
    int     m_nColorB;
    int     m_nColorG;
    int     m_nColorR;
    int     m_nSize;
    int     m_nSharpness;
    int     m_nDarkness;
    int     m_nPosX;
    int     m_nPosY;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CMFCDlgDemoDlg)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    HICON m_hIcon;
    CWndShadow m_Shadow;

    // Generated message map functions
    //{{AFX_MSG(CMFCDlgDemoDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    //}}AFX_MSG

    void UpdateShadow(void);
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCDLGDEMODLG_H__8EAD6216_4049_49A6_884D_48D9B62C63F5__INCLUDED_)
