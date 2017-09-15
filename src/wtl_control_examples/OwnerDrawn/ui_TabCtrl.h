//////////////////////////////////////////////////////////////////////////////////////////
//      Project: PinkYeti
//   $Workfile:: ui_TabCtrl.h                                          $   - Title
//
//  Description: This class implements an owner drawn tab control that will allow
//               colors to be set for the background, the selected tab, the unselected
//               tab, and the text. You can also set a font, point size, and if it is bold
//
//       Author: Jay Giganti
// Date Created: 2/17/2001
//     $Author:: Jay                                                   $   - Reviewer
//    $Modtime:: 3/04/01 10:22a                                        $   - Date Reviewed
//
//     $Archive:: /Code/Pkgs/UI/ui_TabCtrl.h                                             $
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

#ifndef __UI_TABCTRL_H__
#define __UI_TABCTRL_H__

#include <AtlCtrls.h>
#include <AtlMisc.h>
#include <AtlFrame.h>

class ui_TabCtrl : public CWindowImpl<ui_TabCtrl, CTabCtrl>
{

public:
    ui_TabCtrl();

    void SetColors(const COLORREF crSelected, const COLORREF crUnselected, const COLORREF crBack,
                   const COLORREF crText, const COLORREF crHiLight);

    void SetFont(const char * szFont, const bool bBoldFont, const int nPointSize);

    BOOL SubclassWindow(HWND hWnd);

    virtual ~ui_TabCtrl();

    int GetTabHeight()
    {
        return m_nTabH;
    }

    BEGIN_MSG_MAP(ui_TabCtrl)
    MESSAGE_HANDLER(WM_ERASEBKGND,  OnEraseBkgnd)
    MESSAGE_HANDLER(WM_PAINT,       OnPaint)
    MESSAGE_HANDLER(OCM_DRAWITEM,   OnDrawItem)
    END_MSG_MAP()

    LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnDrawItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);


protected:
    void PaintArea(HDC hDC);
    void Init();

    int         m_nTabH;
    int         m_nAdjY;
    COLORREF    m_crBack;
    COLORREF    m_crText;
    COLORREF    m_crUnselected;
    COLORREF    m_crSelected;
    COLORREF    m_crHiLight;
    CString     m_FontName;
    bool        m_bBoldFont;
    int         m_nPointSize;

private:                                            //Disable these
    ui_TabCtrl(const ui_TabCtrl& rhs);              //Copy constructor
    ui_TabCtrl& operator =(const ui_TabCtrl& rhs);  //Assignment
};

#endif //__UI_TABCTRL_H__

