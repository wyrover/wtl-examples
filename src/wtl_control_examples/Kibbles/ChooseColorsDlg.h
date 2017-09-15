// ChooseColorsDlg.h: interface for the CChooseColorsDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHOOSECOLORSDLG_H__B6EFC0BC_27D1_428C_8846_DE419EFFAC10__INCLUDED_)
#define AFX_CHOOSECOLORSDLG_H__B6EFC0BC_27D1_428C_8846_DE419EFFAC10__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000

#include "ColorButton.h"

class CChooseColorsDlg : public CDialogImpl<CChooseColorsDlg>,
    public CWinDataExchange<CChooseColorsDlg>
{
public:
    enum { IDD = IDD_CHOOSE_COLORS };

    // Construction
    CChooseColorsDlg();

    // Maps
    BEGIN_MSG_MAP(CChooseColorsDlg)
    MSG_WM_INITDIALOG(OnInitDialog)
    COMMAND_ID_HANDLER_EX(IDC_TEXT_COLOR, OnChooseTextColor)
    COMMAND_ID_HANDLER_EX(IDOK, OnOK)
    COMMAND_ID_HANDLER_EX(IDCANCEL, OnCancel)
    REFLECT_NOTIFICATIONS()
    END_MSG_MAP()

    BEGIN_DDX_MAP(CChooseColorsDlg)
    DDX_CONTROL(IDC_BK_COLOR, m_btnBkClr)
    DDX_CONTROL(IDC_DL_OUTLINE_COLOR, m_btnDownloadedOutlineClr)
    DDX_CONTROL(IDC_LEFT_OUTLINE_COLOR, m_btnRemainingOutlineClr)
    DDX_CONTROL(IDC_LEFT_FILL_COLOR, m_btnRemainingFillClr)
    END_DDX_MAP()

    // Message handlers
    BOOL OnInitDialog(HWND hwndFocus, LPARAM lParam);

    // Command handlers
    void OnChooseTextColor(UINT uCode, int nID, HWND hwndCtrl);
    void OnOK(UINT uCode, int nID, HWND hwndCtrl);
    void OnCancel(UINT uCode, int nID, HWND hwndCtrl);

    // Data
    COLORREF m_crText, m_crBkgnd, m_crDownloadedOutline,
             m_crRemainingOutline, m_crRemainingFill;

protected:
    // DDX vars
    CColorButton m_btnBkClr, m_btnDownloadedOutlineClr,
                 m_btnRemainingOutlineClr, m_btnRemainingFillClr;
};

#endif // !defined(AFX_CHOOSECOLORSDLG_H__B6EFC0BC_27D1_428C_8846_DE419EFFAC10__INCLUDED_)
