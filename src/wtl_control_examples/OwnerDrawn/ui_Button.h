//////////////////////////////////////////////////////////////////////////////////////////
//      Project: PinkYeti
//   $Workfile:: ui_Button.h                                           $   - Title
//
//  Description: This class allows the drawing of a text button with a specific color
//               for the button, the button text
//
//       Author: Jay Giganti
// Date Created: 2/19/2001
//     $Author:: Jay                                                   $   - Reviewer
//    $Modtime:: 2/19/01 8:20p                                         $   - Date Reviewed
//
//     $Archive:: /Code/Pkgs/UI/ui_Button.h                                              $
//
//  This code may be used in compiled form in any way you desire. This
//  file may be redistributed unmodified by any means PROVIDING it is
//  not sold for profit without the authors written consent, and
//  providing that this notice and the authors name and all copyright
//  notices remains intact.
//
//  Email JGiganti@hotmail.com letting him know how you are using it would be nice as well.
//
//  Most of this code has been modified from other exaples on Code Project to do what I
//  need it to do and/or ported to use WTL
//
//  This file is provided "as is" with no expressed or implied warranty.
//  The author accepts no liability for any damage/loss of business that
//  this product may cause.
//
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef __UI_BUTTON_H__
#define __UI_BUTTON_H__

#include <AtlCtrls.h>
#include <AtlMisc.h>

class ui_Button : public CWindowImpl<ui_Button, CButton, CControlWinTraits>
{
public:
    DECLARE_WND_SUPERCLASS(_T("ui_Button"), CButton::GetWndClassName())

    ui_Button();
    ~ui_Button();

    ui_Button& operator=(HWND hWnd);

    void LoadTipText();
    void SetTipText(const char * szTip);
    void SetColors(const COLORREF crText, const COLORREF crButton);
    void SetBorderColors(const COLORREF crShadow, const COLORREF crDarkShadow, const COLORREF crHiLight);
    void GetAccelFromText();
    void SetAccel(const WPARAM wpAccel)
    {
        m_wpAccel = wpAccel;
    }

    void SetMenuID(UINT uiMenuId);
    BOOL SubclassWindow(HWND hWnd);

    typedef CWindowImpl<ui_Button, CButton, CControlWinTraits> thisClass;

    BEGIN_MSG_MAP(thisClass)
    MESSAGE_HANDLER(OCM_DRAWITEM,       OnDrawItem)
    MESSAGE_HANDLER(WM_CREATE,          OnCreate)
    MESSAGE_HANDLER(WM_GETDLGCODE,      OnGetDlgCode)
    MESSAGE_HANDLER(BM_SETSTYLE,        OnSetStyle)
    MESSAGE_HANDLER(WM_LBUTTONDOWN,     OnLButtonDown)
    MESSAGE_HANDLER(WM_LBUTTONDBLCLK,   OnLButtonDown)
    MESSAGE_RANGE_HANDLER(WM_MOUSEFIRST, WM_MOUSELAST, OnMouseMessage)
    END_MSG_MAP()

    LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnSetStyle(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnGetDlgCode(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnDrawItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnMouseMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

protected:
    void Init();
    bool CreateTip();
    void DrawBorder(CDC & dc, const CRect & rc, const bool bSelected, const bool bThin);
    BOOL ShowMenu(CPoint& pt);

    bool            m_bDefault;
    bool            m_bShowMenu;
    WPARAM          m_wpAccel;
    UINT            m_uiMenuId;
    COLORREF        m_crText;
    COLORREF        m_crButton;
    COLORREF        m_crShadow;
    COLORREF        m_crDarkShadow;
    COLORREF        m_crHiLight;
    CToolTipCtrl    m_Tip;

private:                                            //Disable these
    ui_Button(const ui_Button& rhs);                //Copy constructor
    ui_Button& operator =(const ui_Button& rhs);    //Assignment
};

#endif //__UI_BUTTON_H__

