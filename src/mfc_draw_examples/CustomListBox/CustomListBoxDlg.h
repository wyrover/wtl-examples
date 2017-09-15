// CustomListBoxDlg.h : header file
//

#if !defined(AFX_CUSTOMLISTBOXDLG_H__F3CE7B5C_4D82_4F49_8FB3_194B0CF51571__INCLUDED_)
#define AFX_CUSTOMLISTBOXDLG_H__F3CE7B5C_4D82_4F49_8FB3_194B0CF51571__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////

// Custom listbox header
#include "CWinListBox.h"

// GUI eye candy
#include "C_Button.h"
#include "C_Frame.h"

/////////////////////////////////////////////////////////////////////////////
// CCustomListBoxDlg dialog

class CCustomListBoxDlg : public CDialog
{
// Construction
public:
    CCustomListBoxDlg(CWnd* pParent = NULL);    // standard constructor

// Dialog Data
    //{{AFX_DATA(CCustomListBoxDlg)
    enum { IDD = IDD_CUSTOMLISTBOX_DIALOG };
    CStatic m_ST_Issa;
    CStatic m_ST_Grass;
    CC_Button   m_Tootle;
    CC_Frame    m_FR_GetSeleted;
    CEdit   m_EF_S_GetSelected;
    CEdit   m_EF_N_GetSelected;
    CC_Button   m_BT_GetSelected;
    CEdit   m_EF_S_Insert;
    CEdit   m_EF_S_Get;
    CEdit   m_EF_S_Change;
    CEdit   m_EF_S_Add;
    CEdit   m_EF_N_Remove;
    CEdit   m_EF_N_Populate;
    CEdit   m_EF_N_Insert;
    CEdit   m_EF_N_Get;
    CEdit   m_EF_N_ColumnWidth;
    CEdit   m_EF_N_Change;
    CButton m_CB_TextColor;
    CButton m_CB_Insert;
    CButton m_CB_Change;
    CButton m_CB_Add;
    CC_Button   m_BT_Add;
    CC_Frame    m_FR_Background2;
    CC_Frame    m_FR_Background1;
    CC_Frame    m_FR_Add;
    CC_Frame    m_FR_TextColor;
    CC_Frame    m_FR_Selection4;
    CC_Frame    m_FR_Selection3;
    CC_Frame    m_FR_Selection2;
    CC_Frame    m_FR_Selection1;
    CC_Frame    m_FR_SB4;
    CC_Frame    m_FR_SB3;
    CC_Frame    m_FR_SB2;
    CC_Frame    m_FR_SB1;
    CC_Frame    m_FR_Insert;
    CC_Frame    m_FR_Get;
    CC_Frame    m_FR_Change;
    CC_Frame    m_FR_Border2;
    CC_Frame    m_FR_Border1;
    CC_Button   m_BT_TextColor;
    CC_Button   m_BT_SelectionColors;
    CC_Button   m_BT_ScrollBarColors;
    CC_Button   m_BT_RemoveAll;
    CC_Button   m_BT_Remove;
    CC_Button   m_BT_Populate;
    CC_Button   m_BT_Insert;
    CC_Button   m_BT_Get;
    CC_Button   m_BT_ColumnWidth;
    CC_Button   m_BT_Change;
    CC_Button   m_BT_Border;
    CC_Button   m_BT_Background;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CCustomListBoxDlg)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    HICON m_hIcon;

    // Custom listbox field
    CCWinListBox    m_CWindListBox;

    // GUI eye candy
    CBrush*         m_pbBackground;

    // Generated message map functions
    //{{AFX_MSG(CCustomListBoxDlg)
    virtual BOOL OnInitDialog();
    virtual void OnOK() {};
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnDestroy();
    afx_msg void OnBye();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg void OnBtAdd();
    afx_msg void OnBtBackground();
    afx_msg void OnBtBorder();
    afx_msg void OnBtChange();
    afx_msg void OnBtColumnWidth();
    afx_msg void OnBtGet();
    afx_msg void OnBtInsert();
    afx_msg void OnBtPopulate();
    afx_msg void OnBtRemove();
    afx_msg void OnBtRemoveall();
    afx_msg void OnBtSb();
    afx_msg void OnBtSelection();
    afx_msg void OnBtTextcolor();
    afx_msg void OnBtGetselected();
    afx_msg void OnBtTootle();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMLISTBOXDLG_H__F3CE7B5C_4D82_4F49_8FB3_194B0CF51571__INCLUDED_)
