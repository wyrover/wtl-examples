//
// StyleButton.h : Version 1.0 - see article at CodeProject.com
//
// Author:  Darren Sessions
//
//
// Description:
//     StyleButton is a CButton derived control that uses GDI+ to support
//     alternate image formats.  StyleButton is an updated version of my
//     GdipButton that supports the use of Styles.
//
// History
//      Version 1.1 - 2008 July 25
//      - Changed all button types to styles
//
//      Version 1.0 - 2008 July 1
//      - Initial public release
//
// License:
//     This software is released under the Code Project Open License (CPOL),
//     which may be found here:  http://www.codeproject.com/info/eula.aspx
//     You are free to use this software in any way you like, except that you
//     may not sell this source code.
//
//     This software is provided "as is" with no expressed or implied warranty.
//     I accept no liability for any damage or loss of business that this
//     software may cause.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include "style.h"

/////////////////////////////////////////////////////////////////////////////
// StyleButton window

class StyleButton : public CButton
{
public:

    StyleButton();
    virtual ~StyleButton();

    // image states
    enum ButtonStates {
        STD_STATE   = 0,
        ALT_STATE,
        DIS_STATE
    };

    // sets the image type
    void SetImage(int type);

    // load image functions
    BOOL LoadAltImage(UINT id, LPCTSTR pType);
    BOOL LoadStdImage(UINT id, LPCTSTR pType);

    // load style functions
    void LoadStdStyle(Style style);
    void LoadHotStyle(Style style);
    void LoadPressedStyle(Style style);
    void LoadAltStyle(Style style);
    void LoadAltHotStyle(Style style);
    void LoadAltPressedStyle(Style style);
    void LoadDisabledStyle(Style style);

    // if false, disables the press state and uses grayscale image if it exists
    void EnableButton(BOOL bEnable = TRUE)
    {
        m_bIsDisabled = !bEnable;
    }

    // in toggle mode each press toggles between std and alt images
    void EnableToggle(BOOL bEnable = TRUE);

    // return the enable/disable state
    BOOL IsDisabled(void)
    {
        return (m_bIsDisabled == TRUE);
    }

    void SetBkGnd(CDC* pDC);

    void Regenerate();

    void SetToolTipText(CString spText, BOOL bActivate = TRUE);
    void SetToolTipText(UINT nId, BOOL bActivate = TRUE);
    void DeleteToolTip();


protected:

    void CreateButton();

    void PaintBk(CDC* pDC);
    void PaintBtn(CDC* pDC);

    BOOL    m_bIsDisabled;
    BOOL    m_bIsToggle;
    BOOL    m_bIsHovering;
    BOOL    m_bIsTracking;

    BOOL    m_bHaveAltStyle;

    int     m_nCurState;

    CString         m_tooltext;
    CToolTipCtrl*   m_pToolTip;

    void    InitToolTip();

    virtual void PreSubclassWindow();
    virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
    virtual BOOL PreTranslateMessage(MSG* pMsg);

    //{{AFX_MSG(StyleButton)
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);
    afx_msg LRESULT OnMouseHover(WPARAM wparam, LPARAM lparam);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()

private:

    CDC     m_dcBk;         // button background

    Style   m_Background;

    Style*  m_pCurBtn;

    Style   m_StdStyle;
    Style   m_StdPStyle;
    Style   m_StdHStyle;
    Style   m_StdGStyle;
    Style   m_AltStyle;
    Style   m_AltPStyle;
    Style   m_AltHStyle;
};
