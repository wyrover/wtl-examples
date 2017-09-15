//
// Layers.h: header file for the Layers class.
//
// Author:  Darren Sessions
//
//
// Description:
//
//      The Layers class contains all the structures and arrays used by the
//      Style Toolkit.
//
// History
//     Version 1.1 - 2008 August 1
//     - More features added
//
//     Version 1.0 - 2008 July 22
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

#pragma warning( disable : 4786 )

#include <vector>
using namespace std;

#include "Border.h"
#include "GResource.h"
#include "MemDC.h"
#include "colors.h"
#include "StyleEnum.h"

//////////////////////////////////////////////////////////////////////
// This class allows the API to take arguments of COLORREF or Color
//////////////////////////////////////////////////////////////////////
class Clr
{
public:
    Clr(Color color)
    {
        value = color;
    }

    Clr(COLORREF c)
    {
        value = ARGB(((0x000000ff) << 24) |
                     ((c & 0x000000ff) << 16) |
                     ((c & 0x0000ff00) <<  0) |
                     ((c & 0x00ff0000) >> 16));
    }

    Clr(int a, COLORREF c)
    {
        value = ARGB(((a & 0x000000ff) << 24) |
                     ((c & 0x000000ff) << 16) |
                     ((c & 0x0000ff00) <<  0) |
                     ((c & 0x00ff0000) >> 16));
    }

    COLORREF GetRGB()
    {
        COLORREF rgb = ((value.GetR() <<  0) |
                        (value.GetG() <<  8) |
                        (value.GetB() << 16)) ;
        return rgb;
    }

    ARGB Blend(const ARGB bg, const ARGB src)
    {
        ARGB a = src >> 24;

        if (0 == a) return bg;

        ARGB rb = (((src & 0x00ff00ff) * a) +
                   ((bg & 0x00ff00ff) * (0xff - a))) & 0xff00ff00;
        ARGB g = (((src & 0x0000ff00) * a) +
                  ((bg & 0x0000ff00) * (0xff - a))) & 0x00ff0000;
        return (src & 0xff000000) | ((rb | g) >> 8);
    }

    Color Blend(const Color other)
    {
        ARGB src = other.GetValue();
        ARGB bg = value.GetValue();
        return Color(Blend(bg, src));
    }


public:
    Color value;
};

//////////////////////////////////////////////////////////////////////
// This class allows the API to take arguments of CRect or Rect
//////////////////////////////////////////////////////////////////////
class SRect
{
public:
    SRect(Rect r)
    {
        rect = r;
    }

    SRect(CRect cr)
    {
        rect.X = cr.left;
        rect.Y = cr.top;
        rect.Width = cr.Width();
        rect.Height = cr.Height();
    }
public:
    Rect rect;
};

//////////////////////////////////////////////////////////////////////
// This class allows the API to take arguments of CPoint or Point
//////////////////////////////////////////////////////////////////////
class SPoint
{
public:
    SPoint(Point p)
    {
        point = p;
    }

    SPoint(CPoint cp)
    {
        point.X = cp.x;
        point.Y = cp.y;
    }

public:
    Point point;
};


///////////////////////////////////////////////////////////////////////////
// This class contains the frame and all the layers, strings and images
///////////////////////////////////////////////////////////////////////////
class Layers
{
public:

    // constructors
    Layers();
    Layers(int alloc);
    ~Layers();

    //==========================================================================================//
    //      The main paint function called by the Style class
    //==========================================================================================//
    void    PaintStack(MemDC* pDC, Graphics* pGraphics);
    void    PaintStaticStack(CDC* pDC, Graphics* pGraphics);    // future

    void    SetClipping(Graphics* pGraphics);
    void    RestoreClipping(Graphics* pGraphics);

    CDC*    GetDC()
    {
        return &m_dc;
    }

    // conversion function
    RectF   MakeRectF(Rect r)
    {
        RectF rf((float)r.X, (float)r.Y,
                 (float)r.Width, (float)r.Height);
        return rf;
    }

protected:

    Layers(const Layers& other);
    Layers& operator=(const Layers& other);

    void    Copy(const Layers& other);
    void    CopyLayers(const Layers& other);
    void    Init(int alloc = 10);

    void    MakeFrame(SRect rect);
    void    MakeFrameRgn();

    int     AddLayer();
    int     AddLayer(SRect sr, Clr clr);

    void    SetShape(int shape, int xradius = 0);
    void    Regenerate(int layerIdx = -1);

    void    Transform(int xform);

public:

    typedef struct _OPERATION {
        Rect        lrect;

        Color       clr1;
        Color       clr2;
        Color       clr3;

        int         LayerType;
        int         LayerShape;

        union {
            int     width;
            int     gradMode;
            int     clipMode;
            int     imgIndex;
            int     strIndex;
        };

        REAL    rParams[3];
        int     rgnIndex[2];

        Region*     pRegion;

    } OPERATION;

    typedef struct _TEXTINFO {
        WCHAR       fname[32];
        PointF      foffset;
        int         align;
        int         fsize;
        int         fstyle;
        wstring     string;

    } TEXTINFO;

    typedef struct _IMAGEINFO {
        int         clip;
        int         xform;
        Point       destpt;
        Point       srcpt;
        UINT        resID;
        LPCTSTR     resType;
        GResource*  pImage;

    } IMAGEINFO;

    typedef struct _FRAME {
        Rect        frect;
        Region      clipRgn;

        Border      OuterBorder;
        Border      MiddleBorder;
        Border      InnerBorder;

        BOOL        bUseBitmap;

    } FRAME;

    ///////////// data elements /////////////////

    FRAME       Frame;

    vector<OPERATION>                   m_Layers;
    vector<OPERATION>::iterator         layer;
    vector<OPERATION>::const_iterator   clayer;

    vector<TEXTINFO>                    m_Strings;
    vector<TEXTINFO>::iterator          wsIter;
    vector<TEXTINFO>::const_iterator    cwsIter;

    vector<IMAGEINFO>                   m_Images;
    vector<IMAGEINFO>::iterator         image;
    vector<IMAGEINFO>::const_iterator   cimage;
    /////////////////////////////////////////////

private:

    void PaintLayers();
    void PaintImage();
    void PaintString();
    void PaintEffectString();
    void PaintBorders();
    void PaintBar();

    void Fill(Brush* pBrush);
    void CombineRgns(Region* pRgn1, Region* pRgn2, int mode);
    void RegionBlur(Region* pRgn, int amount);
    void SigmoidBlur(Bitmap* pDst, Bitmap* pSrc, int amount);
    void FastBlur(Bitmap* pDst, Bitmap* pSrc, int amount);
    void GetPath(GraphicsPath* pPath);

    // pointer to the current Graphics object
    Graphics*   m_pGdi;

    // pointer to the current CDC object
    MemDC*      m_pDC;

    // pointer to the current layer
    OPERATION*  m_pLayer;

    // dc object holds the flattened stack
    CDC m_dc;

    inline float Sigmoid(float x, float alpha, float beta, float gamma)
    {
        if (x <= alpha) return 0;

        if (x >= alpha && x <= beta) return 2 * (((x - alpha) / (gamma - alpha)) * ((x - alpha) / (gamma - alpha)));

        if (x >= beta && x <= gamma) return 1 - (2 * (((x - gamma) / (gamma - alpha)) * ((x - gamma) / (gamma - alpha))));

        return 1.0f;
    }

};
