// OwnerDrawnView.h : interface of the COwnerDrawnView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OWNERDRAWNVIEW_H__804258A1_A990_4BD4_B7E2_EA99F6B74348__INCLUDED_)
#define AFX_OWNERDRAWNVIEW_H__804258A1_A990_4BD4_B7E2_EA99F6B74348__INCLUDED_

#if _MSC_VER >= 1000
    #pragma once
#endif // _MSC_VER >= 1000

#include "ui_TabCtrl.h"
#include "ui_Button.h"
#include "ui_ColorLabel.h"
#include "ui_ToolTipDlg.h"
#include "UserSettingsSheet.h"

static const COLORREF g_crBack          = RGB(181, 192, 187);
static const COLORREF g_crText          = RGB(10,    0, 100);

static const COLORREF g_crBtnFace       = RGB(227, 235, 231);
static const COLORREF g_crBtnHi         = RGB(246, 252, 249);
static const COLORREF g_crBtnDark       = RGB(50,  52,  51);
static const COLORREF g_crBtnShadow     = RGB(135, 141, 138);
static const COLORREF g_crBtnText       = g_crText;

static const COLORREF g_crTabFill       = g_crBack;
static const COLORREF g_crTabSel        = RGB(222, 222, 222);
static const COLORREF g_crTabHi         = g_crBtnHi;
static const COLORREF g_crTabUnSel      = g_crBtnFace;

class COwnerDrawnView : public CDialogImpl<COwnerDrawnView>
{
public:
    enum { IDD = IDD_OWNERDRAWN_FORM };

    ui_Button           m_Btn;
    ui_Button           m_Btn2;
    ui_ColorLabel       m_Label1;
    ui_ColorLabel       m_Label2;
    ui_ToolTipDlg       m_TipDlg;
    CUserSettingsSheet  m_Sheet;

    COwnerDrawnView() {}

    BOOL PreTranslateMessage(MSG* pMsg)
    {
        return IsDialogMessage(pMsg);
    }

    BEGIN_MSG_MAP(COwnerDrawnView)
    MESSAGE_HANDLER(WM_INITDIALOG,          OnInitDialog)
    COMMAND_ID_HANDLER(ID_MENU_ITEM,        OnMenuItem)
    COMMAND_ID_HANDLER(ID_APP_EXIT,         OnFileExit)
    COMMAND_HANDLER(IDC_BUTTON1, BN_CLICKED, OnClickedButton1)
    COMMAND_HANDLER(IDC_BUTTON2, BN_CLICKED, OnClickedButton2)
    REFLECT_NOTIFICATIONS()             //for ui_Button to work properly
    END_MSG_MAP()

    LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        m_Btn.SubclassWindow(GetDlgItem(IDC_BUTTON1));
        m_Btn.SetColors(g_crBtnText, g_crBtnFace);
        m_Btn.SetBorderColors(g_crBtnDark, g_crBtnShadow, g_crBtnHi);
        m_Btn.SetMenuID(IDR_BTN_MENU);
        m_Btn2.SubclassWindow(GetDlgItem(IDC_BUTTON2));
        m_Btn2.SetColors(g_crBtnText, g_crBtnFace);
        m_Btn2.SetBorderColors(g_crBtnDark, g_crBtnShadow, g_crBtnHi);
        m_Label1.SubclassWindow(GetDlgItem(IDC_TEXT_1));
        m_Label1.SetBold(true,          false);
        m_Label1.SetTextColor(g_crText, false);
        m_Label1.SetBackColor(g_crBack, false);
        m_Label1.SetText("Label 1",     true);
        m_Label2.SubclassWindow(GetDlgItem(IDC_TEXT_2));
        m_Label2.SetTextColor(g_crText, false);
        m_Label2.SetBackColor(g_crBack, false);
        m_Label2.SetTransparent(true,   false);
        m_Label2.SetText("Label 2",     true);
        m_TipDlg.SetOwner(m_hWnd);
        HWND hWndPlaceHolder = GetDlgItem(IDC_PROP_SHEET_HOLDER);
        ::ShowWindow(hWndPlaceHolder, FALSE);
        CRect rc;
        ::GetWindowRect(hWndPlaceHolder, &rc);
        ScreenToClient(&rc);
        m_Sheet.Create(m_hWnd, 0, rc);
        return 0;
    }

    LRESULT OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        ::PostMessage(GetParent(), WM_CLOSE, 0, 0);
        return 0;
    }

    LRESULT OnMenuItem(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        m_Label1.SetText("Menu Item Selected", true);
        return 0;
    }

    LRESULT OnClickedButton1(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
    {
        m_Label1.SetText("Button 1 Clicked", true);
        return 0;
    }
    LRESULT OnClickedButton2(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
    {
        m_Label2.SetText("Button 2 Clicked -- Since it is transparent it gets messed up", true);
        return 0;
    }
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OWNERDRAWNVIEW_H__804258A3_A990_4BD4_B7E2_EA99F6B74348__INCLUDED_)
