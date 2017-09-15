// Border.h: interface for the Border class.
//
// Author:  Darren Sessions
//
//
// Description:
//     Border Draws or Fills rounded rectangles for GDI+.  It was implemented
//     to overcome the asymmetric issues associated with GDI+ round rectangles
//
// History
//     Version 1.0 - 2008 June 24
//     - Initial public release
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

#include "StyleEnum.h"

class Border
{

public:
    Border();
    virtual ~Border();

    // base methods
    void GetPath(GraphicsPath *pPath, Rect r);
    void Draw(Graphics* pGraphics, Rect r,  Color ulclr, Color brclr, int width);

    // round rectangle methods
    void GetRoundRectPath(GraphicsPath *pPath, Rect r);
    void FillRoundRect(Graphics* pGraphics, Rect r,  Color color, int radius);
    void FillRoundRect(Graphics* pGraphics, Brush* pBrush, Rect r, Color border, int radius);
    void DrawRoundRect(Graphics* pGraphics, Rect r,  Color color, int width);

    // rectangle methods
    void GetRectPath(GraphicsPath *pPath, Rect r);
    void DrawRect(Graphics* pGraphics, Rect r,  Color ulclr, Color brclr, int width);

    // clip methods
    void SetBorderClip(Graphics* pGraphics, Rect rc, CombineMode = CombineModeReplace);

public:
    Color       ulclr;          // border color or upper left color
    Color       brclr;          // bottom right color
    int         width;          // width of border
    int         radius;         // radius of border
    int         shape;          // border style
};
