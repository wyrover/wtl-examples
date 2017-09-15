//////////////////////////////////////////////////////////////////////////////////////////
//      Project: PinkYeti
//   $Workfile:: ui_ColorLabel.h                                       $   - Title
//
//  Description: This will allow labels to change the foreground color and will draw it
//               transparently. You can also set the Font Name and Point Size along with
//               Bold, Italic, Underline, and PointSize
//
//       Author: Jay Giganti
// Date Created: 11/04/2000
//     $Author:: Jay                                                   $   - Reviewer
//    $Modtime:: 3/07/01 2:05p                                         $   - Date Reviewed
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
//     $Archive:: /Code/Pkgs/UI/ui_ColorLabel.h                                          $
//
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef __UI__COLOR_LABEL_H__
#define __UI__COLOR_LABEL_H__

#include <string>

class ui_ColorLabel : public CWindowImpl<ui_ColorLabel, CWindow>
{
public:
    ui_ColorLabel();
    virtual ~ui_ColorLabel();

    void SubclassWindow(HWND hWnd);

    virtual void SetBackColor(const COLORREF crBack, const bool bRedraw);
    virtual void SetTextColor(const COLORREF crText, const bool bRedraw);
    virtual void SetText(const char * Text, const bool bRedraw);
    virtual void SetFontName(const char * FontName, const bool bRedraw);
    virtual void SetFontSize(const int nSize, const bool bRedraw);
    virtual void SetBold(const bool bBold, const bool bRedraw);
    virtual void SetUnderline(const bool bUnderline, const bool bRedraw);
    virtual void SetItalic(const bool bItalic, const bool bRedraw);
    virtual void SetTransparent(const bool bTransparent, const bool bRedraw);

protected:
    bool CreateFont(const LOGFONT & lf, const bool bRedraw);

    BEGIN_MSG_MAP(ui_ColorLabel)
    MESSAGE_HANDLER(WM_PAINT,       OnPaint)
    MESSAGE_HANDLER(WM_ERASEBKGND,  OnEraseBackground)
    END_MSG_MAP()

    LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnEraseBackground(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    bool        m_bTransparent;
    COLORREF    m_crText;
    COLORREF    m_crBack;
    CFont       m_Font;
    std::string m_Text;
};

#endif //__UI__COLOR_LABEL_H__
