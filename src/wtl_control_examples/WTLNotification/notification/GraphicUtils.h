#ifndef __GRAPHIC_UTILS_H__
#define __GRAPHIC_UTILS_H__

#pragma once

#include <gdiplus.h>
using namespace Gdiplus;

namespace WTL
{

/*
Utility class for graphic routines.
*/
class CGraphicUtils
{
public:
    static const COLORREF RGB_BLACK      = 0x00000000L;
    static const COLORREF RGB_WHITE      = 0x00FFFFFFL;
    static const COLORREF RGB_RED        = 0x000000FFL;
    static const COLORREF RGB_GREEN      = 0x0000FF00L;
    static const COLORREF RGB_BLUE       = 0x00FF0000L;
    static const COLORREF RGB_LIGHTGRAY  = 0x00C0C0C0L;

public:
    // Fills a rectangle with a horizontal gradient, with a specified number of segments, and a start and end color.
    static void GradientFillHorizontal(
        HDC hdc,
        CRect* prc,
        COLORREF cptStart,
        COLORREF cptEnd,
        bool colorInversion = false)
    {
        Graphics g(hdc);
        Color colorFrom;
        colorFrom.SetFromCOLORREF(colorInversion ? cptEnd : cptStart);
        Color colorTo;
        colorTo.SetFromCOLORREF(colorInversion ? cptStart : cptEnd);
        Rect rect(prc->left, prc->top, prc->Width(), prc->Height());
        LinearGradientBrush brush(rect, colorFrom, colorTo, LinearGradientModeHorizontal);
        g.FillRectangle(&brush, rect);
    }

    // Fills a rectangle with a vertical gradient, with a specified number of segments, and a start and end color.
    static void GradientFillVertical(
        HDC hdc,
        CRect* prc,
        COLORREF cptStart,
        COLORREF cptEnd,
        bool colorInversion = false)
    {
        Graphics g(hdc);
        Color colorFrom;
        colorFrom.SetFromCOLORREF(colorInversion ? cptEnd : cptStart);
        Color colorTo;
        colorTo.SetFromCOLORREF(colorInversion ? cptStart : cptEnd);
        Rect rect(prc->left, prc->top, prc->Width(), prc->Height());
        LinearGradientBrush brush(rect, colorFrom, colorTo, LinearGradientModeVertical);
        g.FillRectangle(&brush, rect);
    }
};


};

#endif // __GRAPHIC_UTILS_H__