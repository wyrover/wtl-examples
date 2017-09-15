// Border.cpp: implementation of the Border class.
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

#include "stdafx.h"
#include "Border.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Border::Border()
{
}

Border::~Border()
{
}

//=============================================================================
//
// GetPath()
//
// Purpose:     Defines a the appropriate path and places it in the GraphicsPath
//
// Parameters:  pPath       - [out] pointer to GraphicsPath that will recieve the
//                                  path data
//              r           - [in]  Rect that defines the round rectangle boundaries
//
// Returns:     None
//
void Border::GetPath(GraphicsPath *pPath, Rect r)
{
    if (shape == RECTANGLE) {
        GetRectPath(pPath, r);
    } else {
        GetRoundRectPath(pPath, r);
    }
}


//=============================================================================
//
// GetRectPath()
//
// Purpose:     Defines a Rectangle and places it in the GraphicsPath
//
// Parameters:  pPath       - [out] pointer to GraphicsPath that will recieve the
//                                  path data
//              r           - [in]  Rect that defines the round rectangle boundaries
//
// Returns:     None
//
void Border::GetRectPath(GraphicsPath *pPath, Rect r)
{
    pPath->Reset();
    pPath->AddRectangle(r);
    pPath->CloseFigure();
}

//=============================================================================
//
// GetRoundRectPath()
//
// Purpose:     Defines a Rounded Rectangle and places it in the GraphicsPath
//
// Parameters:  pPath       - [out] pointer to GraphicsPath that will recieve the
//                                  path data
//              r           - [in]  Rect that defines the round rectangle boundaries
//
// Returns:     None
//
void Border::GetRoundRectPath(GraphicsPath *pPath, Rect r)
{
    // set the diameter
    int dia = 2 * radius;

    // this isn't a round rect anymore but it
    // can occur with progress bars
    if ((dia > r.Width) || (dia > r.Height)) {
        r.Inflate(0, -(dia / r.Width)); // add other case
        pPath->AddEllipse(r);
        return;
    }

    // define a corner
    Rect Corner(r.X, r.Y, dia, dia);
    // begin path
    pPath->Reset();
    // top left
    pPath->AddArc(Corner, 180, 90);

    // tweak needed for radius of 10 (dia of 20)
    if (dia == 20) {
        Corner.Width += 1;
        Corner.Height += 1;
        r.Width -= 1;
        r.Height -= 1;
    }

    // top right
    Corner.X += (r.Width - dia - 1);
    pPath->AddArc(Corner, 270, 90);
    // bottom right
    Corner.Y += (r.Height - dia - 1);
    pPath->AddArc(Corner,   0, 90);
    // bottom left
    Corner.X -= (r.Width - dia - 1);
    pPath->AddArc(Corner,  90, 90);
    // end path
    pPath->CloseFigure();
}


//=============================================================================
//
// Draw()
//
// Purpose:     Draws a border with a solid pen
//
// Parameters:  pGraphics   - [in]  pointer to the Graphics device
//              r           - [in]  Rect that defines the round rectangle boundaries
//              ulclr       - [in]  Color value for the pen
//              brclr       - [in]  Bottom right pen color (SQUARE border only)
//              width       - [in]  width of the border
//
// Returns:     None
//
void Border::Draw(Graphics* pGraphics, Rect r,  Color ulclr, Color brclr, int width)
{
    if (shape == RECTANGLE) {
        DrawRect(pGraphics, r, ulclr, brclr, width);
    }

    if (shape == ELLIPSE) {
        Pen pen(ulclr, 1);
        pen.SetAlignment(PenAlignmentCenter);
        RectF rf((float)r.X - 1, (float)r.Y - 1, (float)r.Width + 1, (float)r.Height + 1);
        pGraphics->DrawEllipse(&pen, rf);
    } else if (shape == TRANSITION) {
        // disable smoothing for the clip fill
        SmoothingMode oldMode = pGraphics->GetSmoothingMode();
        pGraphics->SetSmoothingMode(SmoothingModeNone);
        // fill the transition zone using a clip region
        pGraphics->SetClip(r, CombineModeReplace);
        // fill one pixel width into the round rect if width > 1
        // this supresses any transition antialiasing
        Rect cr(r);

        if (width > 1) cr.Inflate(-1, -1);

        // use local clip function for round rect
        SetBorderClip(pGraphics, cr, CombineModeExclude);
        // fill with the border color
        SolidBrush sbr(ulclr);
        pGraphics->FillRectangle(&sbr, r);
        // clear the clipping region
        pGraphics->ResetClip();
        // restore any smoothing mode
        pGraphics->SetSmoothingMode(oldMode);
        // now draw the round border
        DrawRoundRect(pGraphics, r, ulclr, width);
    } else {
        DrawRoundRect(pGraphics, r, ulclr, width);
    }
}

//=============================================================================
//
// DrawRect()
//
// Purpose:     Draws a rectangle with a solid pen
//
// Parameters:  pGraphics   - [in]  pointer to the Graphics device
//              r           - [in]  Rect that defines the round rectangle boundaries
//              color       - [in]  Color value for the brush
//              width       - [in]  width of the border
//
// Returns:     None
//
void Border::DrawRect(Graphics* pGraphics, Rect r,  Color ulclr, Color brclr, int width)
{
    int i, left, top, bottom, right;
    // set to pixel mode
    Unit oldPageUnit = pGraphics->GetPageUnit();
    pGraphics->SetPageUnit(UnitPixel);
    // define the upper left pen
    Pen ulpen(ulclr, 1);
    ulpen.SetAlignment(PenAlignmentCenter);
    // define the bottom right pen
    Pen brpen(brclr, 1);
    brpen.SetAlignment(PenAlignmentCenter);
    // not sure why
    Rect rc(r);

    for (i = 0; i < width; i++) {
        left = rc.X;
        top = rc.Y;
        bottom = rc.GetBottom() - 1;
        right = rc.GetRight() - 1;
        // left
        pGraphics->DrawLine(&ulpen, left, top, left, bottom);
        // top
        pGraphics->DrawLine(&ulpen, left, top, right, top);
        // right
        pGraphics->DrawLine(&brpen, right, top + 1, right, bottom);
        // bottom
        pGraphics->DrawLine(&brpen, left + 1, bottom, right, bottom);
        rc.Inflate(-1, -1);
    }

    // restore page unit
    pGraphics->SetPageUnit(oldPageUnit);
}

//=============================================================================
//
// DrawRoundRect()
//
// Purpose:     Draws a rounded rectangle with a solid pen
//
// Parameters:  pGraphics   - [in]  pointer to the Graphics device
//              r           - [in]  Rect that defines the round rectangle boundaries
//              color       - [in]  Color value for the brush
//              width       - [in]  width of the border
//
// Returns:     None
//
void Border::DrawRoundRect(Graphics* pGraphics, Rect r,  Color color, int width)
{
    // set to pixel mode
    Unit oldPageUnit = pGraphics->GetPageUnit();
    pGraphics->SetPageUnit(UnitPixel);
    // define the pen
    Pen pen(color, 1);
    pen.SetAlignment(PenAlignmentCenter);
    // get the corner path
    GraphicsPath path;
    // get path
    GetRoundRectPath(&path, r);
    // draw the round rect
    pGraphics->DrawPath(&pen, &path);
    // save smoothing mode
    SmoothingMode oldMode = pGraphics->GetSmoothingMode();

    // if width > 1
    for (int i = 1; i < width; i++) {
        // disable smoothing for brclr lines
        if (i == 1)              pGraphics->SetSmoothingMode(SmoothingModeNone);

        // re enable for last line
        if (i == (width - 1))    pGraphics->SetSmoothingMode(oldMode);

        // left stroke
        r.Inflate(-1, 0);
        // get the path
        GetRoundRectPath(&path, r);
        // draw the round rect
        pGraphics->DrawPath(&pen, &path);
        // up stroke
        r.Inflate(0, -1);
        // get the path
        GetRoundRectPath(&path, r);
        // draw the round rect
        pGraphics->DrawPath(&pen, &path);
    }

    // restore page unit
    pGraphics->SetPageUnit(oldPageUnit);
}

//=============================================================================
//
// FillRoundRect()
//
// Purpose:     Fills a rounded rectangle with a solid brush.  Draws the border
//              first then fills in the rectangle.
//
// Parameters:  pGraphics   - [in]  pointer to the Graphics device
//              r           - [in]  Rect that defines the round rectangle boundaries
//              color       - [in]  Color value for the brush
//              radius      - [in]  radius of the rounded corner
//
// Returns:     None
//
void Border::FillRoundRect(Graphics* pGraphics, Rect r,  Color color, int radius)
{
    SolidBrush sbr(color);
    FillRoundRect(pGraphics, &sbr, r, color, radius);
}

//=============================================================================
//
// FillRoundRect()
//
// Purpose:     Fills a rounded rectangle with the passed brush.  Fills the
//              rectangle then drawst the border.
//
// Parameters:  pGraphics   - [in]  pointer to the Graphics device
//              pBrush      - [in]  pointer to a Brush
//              r           - [in]  Rect that defines the round rectangle boundaries
//              color       - [in]  Color value for the border (needed in case the
//                                  brush is a type other than solid)
//              radius      - [in]  radius of the rounded corner
//
// Returns:     None
//
void Border::FillRoundRect(Graphics* pGraphics, Brush* pBrush, Rect r, Color border, int radius)
{
    int dia = 2 * radius;
    // set to pixel mode
    Unit oldPageUnit = pGraphics->GetPageUnit();
    pGraphics->SetPageUnit(UnitPixel);
    // define the pen
    Pen pen(border, 1);
    pen.SetAlignment(PenAlignmentCenter);
    // get the corner path
    GraphicsPath path;
    // get path
    GetRoundRectPath(&path, r);
    // fill
    pGraphics->FillPath(pBrush, &path);
    // draw the border last so it will be on top in case the color is different
    pGraphics->DrawPath(&pen, &path);
    // restore page unit
    pGraphics->SetPageUnit(oldPageUnit);
}

//=============================================================================
//
// SetBorderClip()
//
// Purpose:     Sets the clipping region to the inside of and including this border.
//              The SetClip(path) of GDI+ has the same problem that a fill path does
//              on a round rectangle, so use GDI's function instead
//
// Parameters:  pGraphics   - [in]  pointer to the Graphics device
//
// Returns:     None
//
void Border::SetBorderClip(Graphics* pGraphics, Rect rc, CombineMode mode)
{
    CRgn frgn;
    int dia;
    dia = 2 * radius;

    if (shape == UNDEFINED) {
        // the border needs a shape
        ASSERT(FALSE);
    }

    if (shape == RECTANGLE) {
        frgn.CreateRectRgn(rc.X, rc.Y, rc.GetRight() + 1, rc.GetBottom() + 1);
    } else if (shape == ELLIPSE) {
        frgn.CreateEllipticRgn(rc.X - 1, rc.Y - 1, rc.GetRight() + 2, rc.GetBottom() + 2);
    }
    // handle this special case - TODO: add for Height < dia
    else if (rc.Width < dia) {
        rc.Width++;
        rc.Height++;
        Rect lrc(rc);
        lrc.Width = 2 * dia;
        Rect rrc(rc);
        rrc.Width = 2 * dia;
        rrc.X = rrc.X - (rrc.Width - rc.Width);
        CRgn lrgn, rrgn;
        lrgn.CreateRoundRectRgn(lrc.X, lrc.Y, lrc.GetRight() + 1, lrc.GetBottom() + 1, dia + 1, dia + 1);
        rrgn.CreateRoundRectRgn(rrc.X, rrc.Y, rrc.GetRight() + 1, rrc.GetBottom() + 1, dia + 1, dia + 1);
        frgn.CreateRectRgn(0, 0, 0, 0);
        frgn.CombineRgn(&lrgn, &rrgn, RGN_AND);
    } else {
        frgn.CreateRoundRectRgn(rc.X, rc.Y, rc.GetRight() + 1, rc.GetBottom() + 1, dia + 1, dia + 1);
    }

    Region grgn(frgn);
    pGraphics->SetClip(&grgn, mode);
}
