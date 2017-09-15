//
// Layers.cpp: source file for the Layers class.
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
//     Version 1.1 - 2008 July 22
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
#include "Layers.h"

#include "math.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//=============================================================================
// Construction/Destruction
//=============================================================================

//=============================================================================
// empty constructor
Layers::Layers()
//=============================================================================
{
    Init();
}

//=============================================================================
// pre allocate alloc number of layers and strings
Layers::Layers(int alloc)
//=============================================================================
{
    Init(alloc);
}

//=============================================================================
// Layers Initializer
void Layers::Init(int alloc)
//=============================================================================
{
    ::ZeroMemory(&Frame, sizeof(FRAME));
    m_Layers.reserve(alloc);
    m_Strings.reserve(alloc);
}

//=============================================================================
// destructor
Layers::~Layers()
//=============================================================================
{
    // delete the image objects
    for (image = m_Images.begin(); image != m_Images.end(); ++image) {
        if ((*image).pImage) delete(*image).pImage;
    }

    // delete the region objects
    for (layer = m_Layers.begin(); layer != m_Layers.end(); ++layer) {
        if ((*layer).pRegion) delete(*layer).pRegion;
    }
}

//=============================================================================
// copy constructor
Layers::Layers(const Layers& other)
//=============================================================================
{
    Copy(other);
}

//=============================================================================
// copy function
void Layers::Copy(const Layers& other)
//=============================================================================
{
    // copy frame
    memcpy(&Frame, &other.Frame, sizeof(FRAME));
    // Copy layers and strings
    CopyLayers(other);
}

//=============================================================================
// copy function helper
void Layers::CopyLayers(const Layers& other)
//=============================================================================
{
    // copy OPERATION
    for (clayer = other.m_Layers.begin(); clayer != other.m_Layers.end(); ++clayer) {
        m_Layers.push_back(*clayer);
    }

    // copy TEXTINFO
    for (cwsIter = other.m_Strings.begin(); cwsIter != other.m_Strings.end(); ++cwsIter) {
        m_Strings.push_back(*cwsIter);
    }

    // copy IMAGEINFO
    for (cimage = other.m_Images.begin(); cimage != other.m_Images.end(); ++cimage) {
        m_Images.push_back(*cimage);
    }
}

//=============================================================================
// operator =
Layers& Layers::operator=(const Layers& other)
//=============================================================================
{
    m_Layers.clear();
    m_Strings.clear();
    m_Images.clear();
    Copy(other);
    return *this;
}

//=============================================================================
void Layers::MakeFrame(SRect sr)
//=============================================================================
{
    Frame.frect = sr.rect;
    // default to rects
    Frame.OuterBorder.shape = RECTANGLE;
    Frame.MiddleBorder.shape = RECTANGLE;
    Frame.InnerBorder.shape = RECTANGLE;
    MakeFrameRgn();
}

//=============================================================================
void Layers::MakeFrameRgn()
//=============================================================================
{
    Region rgn(Frame.frect);
    Frame.clipRgn.MakeEmpty();
    Frame.clipRgn.Union(&rgn);
}

//=============================================================================
//
// AddLayer()
//
// Purpose:     Adds a layer to the stack.  A transparent layer will be created
//              and set to the Frames rect just prior to painting
//
// Parameters:  None
//
// Returns:     None
//
int Layers::AddLayer()
{
    OPERATION Layer;
    ::ZeroMemory(&Layer, sizeof(OPERATION));
    m_Layers.push_back(Layer);
    return (int)(m_Layers.size() - 1);
}

//=============================================================================
//
// AddLayer()
//
// Purpose:     Adds a layer to the stack.  If only the rect is passed
//              a transparent layer will be created
//
// Parameters:  sr      - [in] Rect boundary of this layer
//              clr     - [in] optional - color of this layer
//
// Returns:     None
//
int Layers::AddLayer(SRect sr, Clr clr)
{
    OPERATION Layer;
    ::ZeroMemory(&Layer, sizeof(OPERATION));
    Layer.lrect = sr.rect;
    Layer.clr1 = clr.value;
    m_Layers.push_back(Layer);
    return (int)(m_Layers.size() - 1);
}

//=============================================================================
//
// SetShape()
//
// Purpose:     Sets the border style and radius
//
// Parameters:  style   - [in] the border style
//              radius  - [in] optional - the corner radius for round borders
//
// Returns:     None
//
void Layers::SetShape(int shape, int radius)
{
    MakeFrameRgn();
    // make all the borders the same
    Frame.OuterBorder.radius = radius;
    Frame.MiddleBorder.radius = radius;
    Frame.InnerBorder.radius = radius;
    Frame.OuterBorder.shape = shape;
    Frame.MiddleBorder.shape = shape;
    Frame.InnerBorder.shape = shape;

    // only the outer border can be transition
    if (shape == TRANSITION) {
        Frame.MiddleBorder.shape = ROUNDRECT;
        Frame.InnerBorder.shape = ROUNDRECT;
    }
}

//=============================================================================
//
// SetClipping()
//
// Purpose:     Sets the Graphics clipping region to the frames tlclr border
//
// Parameters:  None
//
// Returns:     None
//
void Layers::SetClipping(Graphics* pGraphics)
{
    Frame.OuterBorder.SetBorderClip(pGraphics, Frame.frect);
}
//=============================================================================
//
// RestoreClipping()
//
// Purpose:     Restores the Graphics clipping region
//
// Parameters:  None
//
// Returns:     None
//
void Layers::RestoreClipping(Graphics* pGraphics)
{
    pGraphics->ResetClip();
}

//=============================================================================
//
// PaintBorders()
//
// Purpose:     Paints the Outer, Middle and Inner borders based on the
//              borders paramaters.
//
// Parameters:  None
//
// Returns:     None
//
void Layers::PaintBorders()
{
    Rect bdr(Frame.frect);
    int width, ovlap;

    if ((width = Frame.OuterBorder.width)) {
        ovlap = width;

        if ((Frame.MiddleBorder.shape != RECTANGLE) && (Frame.MiddleBorder.width > 0) &&
            (Frame.MiddleBorder.ulclr.GetA() == 255)) ovlap++;

        Frame.OuterBorder.Draw(m_pGdi, bdr, Frame.OuterBorder.ulclr, Frame.OuterBorder.brclr, ovlap);
        bdr.Inflate(-width, -width);
    }

    if ((width = Frame.MiddleBorder.width)) {
        ovlap = width;

        if ((Frame.InnerBorder.shape != RECTANGLE) && (Frame.InnerBorder.width > 0) &&
            (Frame.InnerBorder.ulclr.GetA() == 255)) ovlap++;

        Frame.MiddleBorder.Draw(m_pGdi, bdr, Frame.MiddleBorder.ulclr, Frame.MiddleBorder.brclr, ovlap);
        bdr.Inflate(-width, -width);
    }

    if ((width = Frame.InnerBorder.width)) {
        Frame.InnerBorder.Draw(m_pGdi, bdr, Frame.InnerBorder.ulclr, Frame.InnerBorder.brclr, width);
    }
}

//=============================================================================
//
// PaintLayers()
//
// Purpose:     Paints the solid or gradient base rectangle
//              The rectangle is clipped with the Frame struct
//
//=============================================================================
void Layers::PaintLayers()
{
    Color colors[3];

    if (m_pLayer->LayerType == SOLID) {
        SolidBrush br(m_pLayer->clr1);
        Fill(&br);
    } else if (m_pLayer->LayerType == TRIGRAD) {
        colors[0] = m_pLayer->clr1;
        colors[1] = m_pLayer->clr2;
        colors[2] = m_pLayer->clr3;
        REAL positions[] = { 0.0f, m_pLayer->rParams[0], 1.0f };
        LinearGradientMode mode = (LinearGradientMode)m_pLayer->gradMode;
        LinearGradientBrush lgbr(m_pLayer->lrect, Color::Black, Color::White, mode);
        lgbr.SetInterpolationColors(colors, positions, 3);
        Fill(&lgbr);
    } else if (m_pLayer->LayerType == BIGRAD) {
        // check center point for minus flag
        float dp = m_pLayer->rParams[0];
        colors[0] = m_pLayer->clr1;

        if (dp < 0.0f) {
            colors[1] = m_pLayer->clr2;
            dp = 1.0f + dp;
        } else {
            colors[1] = m_pLayer->clr1;
        }

        colors[2] = m_pLayer->clr2;
        REAL positions[] = { 0.0f, dp, 1.0f };
        LinearGradientMode mode = (LinearGradientMode)m_pLayer->gradMode;
        LinearGradientBrush lgbr(m_pLayer->lrect, m_pLayer->clr1,
                                 m_pLayer->clr2, mode);
        lgbr.SetWrapMode(WrapModeClamp);
        lgbr.SetInterpolationColors(colors, positions, 3);
        Fill(&lgbr);
    } else if (m_pLayer->LayerType == RADIAL) {
        GraphicsPath path;
        Rect pr = m_pLayer->lrect;
        path.AddEllipse(pr);
        path.CloseFigure();
        PathGradientBrush pgr(&path);
        int count = 1;
        Color clr = m_pLayer->clr1;
        Color t[1];
        t[0] = m_pLayer->clr2;
        pgr.SetCenterPoint(Point(pr.X + pr.Width / 2, pr.Y + pr.Height / 2));
        pgr.SetSurroundColors(t, &count);
        pgr.SetCenterColor(clr);
        m_pGdi->FillPath(&pgr, &path);
    } else if (m_pLayer->LayerType == IMAGE) {
        PaintImage();
    } else if (m_pLayer->LayerType == STRING) {
        PaintString();
    } else if (m_pLayer->LayerType == EFFECTSTRING) {
        PaintEffectString();
    } else if (m_pLayer->LayerType >= TOP_EDGE && m_pLayer->LayerType <= BOTTOM_EDGE_BEVEL) {
        PaintBar();
    } else if (m_pLayer->LayerType == CREATERGN) {
        GraphicsPath path;
        GetPath(&path);
        Region rgn(&path);
        m_pLayer->pRegion = rgn.Clone();
    } else if (m_pLayer->LayerType == COMBINEMOD) {
        Region *pR0, *pR1;
        pR0 = m_Layers[m_pLayer->rgnIndex[0]].pRegion;
        pR1 = m_Layers[m_pLayer->rgnIndex[1]].pRegion;
        CombineRgns(pR0, pR1, m_pLayer->clipMode);
    } else if (m_pLayer->LayerType == COMBINENEW) {
        Region *pR0, *pR1;
        pR0 = m_Layers[m_pLayer->rgnIndex[0]].pRegion;
        pR1 = m_Layers[m_pLayer->rgnIndex[1]].pRegion;
        m_pLayer->pRegion = pR0->Clone();
        CombineRgns(m_pLayer->pRegion, pR1, m_pLayer->clipMode);
    } else if (m_pLayer->LayerType == APPLYCLIP) {
        m_pGdi->SetClip(m_Layers[m_pLayer->rgnIndex[0]].pRegion);
    } else if (m_pLayer->LayerType == RESTORECLIP) {
        Frame.OuterBorder.SetBorderClip(m_pGdi, Frame.frect);
    } else if (m_pLayer->LayerType == REGIONBLUR) {
        RegionBlur(m_Layers[m_pLayer->rgnIndex[0]].pRegion, m_pLayer->width);
    } else if (m_pLayer->LayerType == WRAP) {
        colors[0] = m_pLayer->clr1;
        colors[1] = m_pLayer->clr2;
        colors[2] = m_pLayer->clr3;
        REAL positions[] = { 0.0f, 0.5, 1.0f };
        //LinearGradientMode mode = (LinearGradientMode)m_pLayer->gradMode;
        LinearGradientMode mode = (LinearGradientMode)HORIZ;
        Rect sr = m_pLayer->lrect;
        sr.Width = m_pLayer->width;
        LinearGradientBrush lgbr(sr, Color::Black, Color::White, mode);
        lgbr.SetInterpolationColors(colors, positions, 3);
        Fill(&lgbr);
    } else if (m_pLayer->LayerType == SETSMOOTH) {
        SmoothingMode sm = SmoothingMode(m_pLayer->clipMode);
        m_pGdi->SetSmoothingMode(sm);
    } else if (m_pLayer->LayerType == RESTORESMOOTH) {
        // this is the default smoothing mode
        m_pGdi->SetSmoothingMode(SmoothingModeAntiAlias);
    } else if (m_pLayer->LayerType == APPLYXFORM) {
        Transform(m_pLayer->gradMode);
    }
}

//
// fills based on the layer shape
//
void Layers::Fill(Brush* pBrush)
{
    Rect r = m_pLayer->lrect;
    int style = Frame.OuterBorder.shape;

    if (style == RECTANGLE) {
        m_pGdi->FillRectangle(pBrush, r);
    } else if (style == ELLIPSE) {
        m_pGdi->FillEllipse(pBrush, r);
    } else if ((style == ROUNDRECT) || (style == TRANSITION)) {
        Color brdr = m_pLayer->clr1;
        int radius = Frame.OuterBorder.radius;
        Frame.OuterBorder.FillRoundRect(m_pGdi, pBrush, r, brdr, radius);
    }
}

//
// Get a path based on the layer shape
//
void Layers::GetPath(GraphicsPath *pPath)
{
    if (m_pLayer->LayerShape == RECTANGLE) {
        pPath->AddRectangle(m_pLayer->lrect);
    } else if (m_pLayer->LayerShape == ELLIPSE) {
        pPath->AddEllipse(m_pLayer->lrect);
    } else if (m_pLayer->LayerShape == ROUNDRECT) {
        Frame.OuterBorder.GetRoundRectPath(pPath, m_pLayer->lrect);
    }
}

//
//  CombineRgns()
//
void Layers::CombineRgns(Region* pRgn1, Region* pRgn2, int mode)
{
    if (m_pLayer->clipMode == INTERSECT) {
        pRgn1->Intersect(pRgn2);
    } else if (m_pLayer->clipMode == UNION) {
        pRgn1->Union(pRgn2);
    } else if (m_pLayer->clipMode == XOR) {
        pRgn1->Xor(pRgn2);
    } else if (m_pLayer->clipMode == EXCLUDE) {
        pRgn1->Exclude(pRgn2);
    } else if (m_pLayer->clipMode == COMPLEMENT) {
        pRgn1->Complement(pRgn2);
    }
}

void Layers::RegionBlur(Region* pRgn, int amount)
{
    // blur the frame rect
    Rect rc = Frame.frect;
    // size for bitmaps
    int width = rc.Width;
    int height = rc.Height;
    // move rect to origin for bitmaps
    Rect bmrc = rc;
    bmrc.X = 0;
    bmrc.Y = 0;
    // create a bitmap for src data
    Bitmap sbm(width, height);
    // create a bitmap for dst data
    Bitmap dbm(width, height);
    // create a graphics object
    Graphics gr(&sbm);
    // fill the region
    pRgn->Translate(-rc.X, -rc.Y);
    gr.SetClip(pRgn);
    SolidBrush gbr(m_pLayer->clr1);
    gr.FillRectangle(&gbr, bmrc);
    gr.ResetClip();
    // call blur function
    SigmoidBlur(&dbm, &sbm, amount);
    // draw image
    m_pGdi->DrawImage(&dbm, rc, 0, 0, width, height, UnitPixel);
}

//
// This is an optimized version of the blur method from
// this article: http://www.codeproject.com/KB/GDI-plus/aqualize.aspx
//
// Use this function with caution! As the bitmap size and blur amount
// increase, so will the computation time.
//
void Layers::SigmoidBlur(Bitmap* pDst, Bitmap* pSrc, int boxw)
{
    int width = pSrc->GetWidth();
    int height = pSrc->GetHeight();
    // these bitmpas need to be the same size
    ASSERT(width == pDst->GetWidth() && height == pSrc->GetHeight());
    Rect bmrc(0, 0, width, height);
    // lock the src bits
    BitmapData sbmData;
    pSrc->LockBits(&bmrc, ImageLockModeWrite | ImageLockModeRead, PixelFormat32bppARGB, &sbmData);
    // access variables
    int line = sbmData.Stride / 4;
    UINT32* src = (UINT32*)sbmData.Scan0;
    // lock the dst bits
    BitmapData dbmData;
    pDst->LockBits(&bmrc, ImageLockModeWrite | ImageLockModeRead, PixelFormat32bppARGB, &dbmData);
    UINT32* dst = (UINT32*)dbmData.Scan0;
    float a, r, g, b, weight, weightsum;
    UINT32 ia, ir, ig, ib, c;
    float* weights = new float[2 * boxw + 1];
    weights[boxw] = 1.0f;

    for (int i = 0; i < boxw; i++) {
        float y = Sigmoid((float)i, 0.0f, (float)((boxw + 1) / 2), (float)(boxw + 1));
        weights[i] = y;
        weights[boxw * 2 - i] = y;
    }

    // horizontal blur
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            r = 0;
            g = 0;
            b = 0;
            a = 0;
            weightsum = 0;

            for (int i = 0; i < boxw * 2 + 1; i++) {
                int x = col - boxw + i;

                if (x < 0) {
                    i += -x;
                    x = 0;
                }

                if (x > width - 1)
                    break;

                c = src[x + row * line];
                weight = weights[i];
                a += ((c >> 24) & 0x000000FF) * weight;
                r += ((c >> 16) & 0x000000FF) * weight;
                g += ((c >>  8) & 0x000000FF) * weight;
                b += ((c >>  0) & 0x000000FF) * weight;
                weightsum += weight;
            }

            ia = min((UINT32)(a / weightsum), 255);
            ir = min((UINT32)(r / weightsum), 255);
            ig = min((UINT32)(g / weightsum), 255);
            ib = min((UINT32)(b / weightsum), 255);
            dst[col + row * line] = ((ia << 24) | (ir << 16) | (ig << 8) | (ib << 0));
        }
    }

    // vertical blur
    for (int col = 0; col < width; col++) {
        for (int row = 0; row < height; row++) {
            r = 0;
            g = 0;
            b = 0;
            a = 0;
            weightsum = 0;

            for (int i = 0; i < boxw * 2 + 1; i++) {
                int y = row - boxw + i;

                if (y < 0) {
                    i += -y;
                    y = 0;
                }

                if (y > height - 1)
                    break;

                c = dst[col + y * line];
                weight = weights[i];
                a += ((c >> 24) & 0x000000FF) * weight;
                r += ((c >> 16) & 0x000000FF) * weight;
                g += ((c >>  8) & 0x000000FF) * weight;
                b += ((c >>  0) & 0x000000FF) * weight;
                weightsum += weight;
            }

            ia = min((UINT32)(a / weightsum), 255);
            ir = min((UINT32)(r / weightsum), 255);
            ig = min((UINT32)(g / weightsum), 255);
            ib = min((UINT32)(b / weightsum), 255);
            dst[col + row * line] = ((ia << 24) | (ir << 16) | (ig << 8) | (ib << 0));
        }
    }

    pDst->UnlockBits(&dbmData);
    pSrc->UnlockBits(&sbmData);
    delete [] weights;
}

//
// This blur method uses a constant weight for the sliding
// box, which makes the calculation independant of the box
// size.  Also only the endpoints need to be calculated as
// the box slides.  This makes the algorithm much faster,
// but it doesn't look as nice as the SigmoidBlur.
//
void Layers::FastBlur(Bitmap* pDst, Bitmap* pSrc, int boxw)
{
    // this function is not finished :)
    ASSERT(FALSE);
#if 0
    // the approach is here
    // http://www.gamasutra.com/features/20010209/Listing3.cpp
    int width = pSrc->GetWidth();
    int height = pSrc->GetHeight();
    // these bitmpas need to be the same size
    ASSERT(width == pDst->GetWidth() && height == pSrc->GetHeight());
    Rect bmrc(0, 0, width, height);
    // lock the src bits
    BitmapData sbmData;
    pSrc->LockBits(&bmrc, ImageLockModeWrite | ImageLockModeRead, PixelFormat32bppARGB, &sbmData);
    // access variables
    int line = sbmData.Stride / 4;
    UINT32* src = (UINT32*)sbmData.Scan0;
    // lock the dst bits
    BitmapData dbmData;
    pDst->LockBits(&bmrc, ImageLockModeWrite | ImageLockModeRead, PixelFormat32bppARGB, &dbmData);
    UINT32* dst = (UINT32*)dbmData.Scan0;
    float a, r, g, b, weight, weightsum;
    UINT32 ia, ir, ig, ib, c, alpha;

    if (boxw >= width) boxw = width - 1;

    weightsum = 2 * boxw + 1;

    for (int row = 0; row < height; row++) {
        //int tot=0;
        r = 0;
        g = 0;
        b = 0;
        a = 0; //weightsum = 0;

        for (int col = 0; col < boxw; col++) {
            // tot += src[col];
            c = src[col + row * line];
            a += ((c >> 24) & 0x000000FF);
            r += ((c >> 16) & 0x000000FF);
            g += ((c >>  8) & 0x000000FF);
            b += ((c >>  0) & 0x000000FF);
        }

        for (int col = 0; col < width; col++) {
            if (col > boxw) {
                // tot -= src[-boxw-1];
                c = src[(col - boxw - 1) + row * line];
                a -= ((c >> 24) & 0x000000FF);
                r -= ((c >> 16) & 0x000000FF);
                g -= ((c >>  8) & 0x000000FF);
                b -= ((c >>  0) & 0x000000FF);
            }

            if ((col + boxw) < width) {
                // tot += src[boxw];
                c = src[boxw + row * line];
                a += ((c >> 24) & 0x000000FF);
                r += ((c >> 16) & 0x000000FF);
                g += ((c >>  8) & 0x000000FF);
                b += ((c >>  0) & 0x000000FF);
                alpha = ((c >> 24) & 0x000000FF);
                r = alpha * r / 255.0f;
                g = alpha * g / 255.0f;
                b = alpha * b / 255.0f;
            }

            //*dst++ = UINT(tot*mul);
            ia = min((UINT32)(a / weightsum), 255);
            ir = min((UINT32)(r / weightsum), 255);
            ig = min((UINT32)(g / weightsum), 255);
            ib = min((UINT32)(b / weightsum), 255);
            UINT32 clr = ((ia << 24) | (ir << 16) | (ig << 8) | (ib << 0));

            if (clr == 0xff000000)
                int tmp = 1;

            dst[col + row * line] = clr;
            //src++;
        }
    }

    pDst->UnlockBits(&dbmData);
    pSrc->UnlockBits(&sbmData);
#endif
}

//=============================================================================
//
// PaintBar()
//
// Purpose:     Paints a bar at the edge of a frame
//
//=============================================================================
void Layers::PaintBar()
{
    // various modes leave artifacts
    SmoothingMode oldMode = m_pGdi->GetSmoothingMode();
    m_pGdi->SetSmoothingMode(SmoothingModeNone);
    LinearGradientMode gtype;
    Rect rc = m_pLayer->lrect;
    int type = m_pLayer->LayerType;
    int ewidth = m_pLayer->width;
    GraphicsPath path;

    if (type == LEFT_EDGE  || type == LEFT_EDGE_BEVEL) {
        gtype = (LinearGradientMode)HORIZ;
        rc.Width = ewidth;

        if (type == LEFT_EDGE) {
            path.AddRectangle(rc);
        } else {
            Point corners[] = { Point(rc.X, rc.Y),
                                Point(rc.X + ewidth, rc.Y + ewidth),
                                Point(rc.X + ewidth, rc.Y + rc.Height - ewidth),
                                Point(rc.X, rc.Y + rc.Height)
                              };
            path.AddPolygon(corners, 4);
        }
    } else if (type == TOP_EDGE || type == TOP_EDGE_BEVEL) {
        gtype = (LinearGradientMode)VERT;
        rc.Height = ewidth;

        if (type == TOP_EDGE) {
            path.AddRectangle(rc);
        } else {
            Point corners[] = { Point(rc.X, rc.Y),
                                Point(rc.X + rc.Width, rc.Y),
                                Point(rc.X + rc.Width - ewidth, rc.Y + ewidth),
                                Point(rc.X + ewidth, rc.Y + ewidth)
                              };
            path.AddPolygon(corners, 4);
        }
    } else if (type == RIGHT_EDGE || type == RIGHT_EDGE_BEVEL) {
        gtype = (LinearGradientMode)HORIZ;
        rc.X = rc.X + rc.Width - ewidth;
        rc.Width = ewidth;

        if (type == RIGHT_EDGE) {
            path.AddRectangle(rc);
        } else {
            Point corners[] = { Point(rc.X, rc.Y + ewidth),
                                Point(rc.X + rc.Width, rc.Y),
                                Point(rc.X + rc.Width, rc.Y + rc.Height),
                                Point(rc.X, rc.Y + rc.Height - ewidth)
                              };
            path.AddPolygon(corners, 4);
        }
    } else if (type == BOTTOM_EDGE || type == BOTTOM_EDGE_BEVEL) {
        gtype = (LinearGradientMode)VERT;
        rc.Y = rc.Y + rc.Height - ewidth;
        rc.Height = ewidth;

        if (type == BOTTOM_EDGE) {
            path.AddRectangle(rc);
        } else {
            Point corners[] = { Point(rc.X + ewidth, rc.Y),
                                Point(rc.X + rc.Width - ewidth, rc.Y),
                                Point(rc.X + rc.Width, rc.Y + rc.Height),
                                Point(rc.X, rc.Y + rc.Height)
                              };
            path.AddPolygon(corners, 4);
        }
    }

    Color colors[5];
    colors[0] = m_pLayer->clr1;
    colors[1] = m_pLayer->clr2;
    colors[2] = m_pLayer->clr3;
    LinearGradientBrush lgbr(rc, colors[0], colors[2], gtype);

    // the extra interpolation point appears to get rid of some artifacts
    if (m_pLayer->rParams[1] != NULL) {
        float profile[3];
        profile[0] = m_pLayer->rParams[0];
        profile[1] = m_pLayer->rParams[1];
        profile[2] = m_pLayer->rParams[2];
        lgbr.SetInterpolationColors(colors, profile, 3);
    }

    // relies on clipping region for round rects
    m_pGdi->FillPath(&lgbr, &path);
    m_pGdi->SetSmoothingMode(oldMode);
}

//=============================================================================
//
// PaintString()
//
// Purpose:     Draws the strings
//
//=============================================================================
void Layers::PaintString()
{
    TEXTINFO* pTI = &m_Strings[m_pLayer->strIndex];
    Font font(pTI->fname, (float)pTI->fsize, pTI->fstyle, UnitPixel);
    SolidBrush br(m_pLayer->clr1);
    RectF rf = MakeRectF(m_pLayer->lrect);
    // add in any offset
    rf.X += pTI->foffset.X;
    rf.Y += pTI->foffset.Y;
    rf.Width -= 2 * pTI->foffset.X;
    rf.Height -= 2 * pTI->foffset.Y;
    StringFormat sf;

    if (pTI->align == ALIGN_NEAR) {
        sf.SetAlignment(StringAlignmentNear);
        sf.SetLineAlignment(StringAlignmentNear);
    } else if (pTI->align == ALIGN_CENTER) {
        sf.SetAlignment(StringAlignmentCenter);
        sf.SetLineAlignment(StringAlignmentCenter);
    } else if (pTI->align == ALIGN_FAR) {
        sf.SetAlignment(StringAlignmentFar);
        sf.SetLineAlignment(StringAlignmentFar);
    }

    m_pGdi->DrawString(pTI->string.c_str(), -1, &font, rf, &sf, &br);
}


//=============================================================================
//
// PaintEffectString()
//
// Purpose:     Draws the strings
//
//=============================================================================
void Layers::PaintEffectString()
{
    TEXTINFO* pTI = &m_Strings[m_pLayer->strIndex];
    Font font(pTI->fname, (float)pTI->fsize, pTI->fstyle, UnitPixel);
    SolidBrush br(m_pLayer->clr1);
    WCHAR* wstr = (WCHAR*)pTI->string.c_str();
    SolidBrush br2(m_pLayer->clr2);
    PointF pt(pTI->foffset.X + m_pLayer->lrect.X, pTI->foffset.Y + m_pLayer->lrect.Y);

    if (m_pLayer->rParams[0] == OUTLINE) {
        int width = (int)m_pLayer->rParams[1];
        int span = 2 * width + 1;
        GraphicsPath path;
        StringFormat sf;
        FontFamily ff(pTI->fname);
        path.SetFillMode(FillModeWinding);

        for (int x = 0; x < span; x++) {
            for (int y = 0; y < span; y++) {
                PointF dp(pt.X + x - width, pt.Y + y - width);
                m_pGdi->DrawString(wstr, -1, &font, dp, &br2);
            }
        }

        // draw face
        m_pGdi->DrawString(wstr, -1, &font, pt, &br);
    }
}


//=============================================================================
//
// PaintImage()
//
// Purpose:     Draws the image set by SetImage
//
//=============================================================================
void Layers::PaintImage()
{
    IMAGEINFO* pII = &m_Images[m_pLayer->imgIndex];
    pII->pImage = new GResource;
    RectF srcF, destF, paneF;
    Unit unit;
    // convert pane offset point to float
    PointF dptF((float)pII->destpt.X, (float)pII->destpt.Y);
    // convert src offset point to float
    PointF sptF((float)pII->srcpt.X, (float)pII->srcpt.Y);
    // convert pane rect to float
    Rect rc = Frame.frect;
    paneF.X = (float)rc.X;
    paneF.Y = (float)rc.Y;
    paneF.Width = (float)rc.Width;
    paneF.Height = (float)rc.Height;

    if (pII->pImage->Load(pII->resID, pII->resType)) {
        // get image dimensions
        pII->pImage->m_pBitmap->GetBounds(&srcF, &unit);
        // offset into src
        srcF.Offset(sptF);
        srcF.Width -= sptF.X;
        srcF.Height -= sptF.Y;
        // destination is pane rect + destpt offset
        destF = paneF;
        destF.Offset(dptF);

        // if src is smaller, adjust dest
        if (destF.Width > srcF.Width) destF.Width = srcF.Width;

        if (destF.Height > srcF.Height) destF.Height = srcF.Height;

        // if dest is smaller and clipping is on, adjust src
        if (pII->clip == TRUE) {
            if (srcF.Width > destF.Width) srcF.Width = destF.Width;

            if (srcF.Height > destF.Height) srcF.Height = destF.Height;
        }

        if (pII->xform == NOXFORM) {
            m_pGdi->DrawImage(*pII->pImage, destF, srcF.X, srcF.Y, srcF.Width, srcF.Height, unit);
        } else if (pII->xform == LIGHTEN) {
            ColorMatrix HotMat = {  1.05f, 0.00f, 0.00f, 0.00f, 0.00f,
                                    0.00f, 1.05f, 0.00f, 0.00f, 0.00f,
                                    0.00f, 0.00f, 1.05f, 0.00f, 0.00f,
                                    0.00f, 0.00f, 0.00f, 1.00f, 0.00f,
                                    0.05f, 0.05f, 0.05f, 0.00f, 1.00f
                                 };
            ImageAttributes ia;
            ia.SetColorMatrix(&HotMat);
            m_pGdi->DrawImage(*pII->pImage, destF, srcF.X, srcF.Y, srcF.Width, srcF.Height, unit, &ia);
        } else if (pII->xform == GRAYSCALE) {
            ColorMatrix GrayMat = { 0.30f, 0.30f, 0.30f, 0.00f, 0.00f,
                                    0.59f, 0.59f, 0.59f, 0.00f, 0.00f,
                                    0.11f, 0.11f, 0.11f, 0.00f, 0.00f,
                                    0.00f, 0.00f, 0.00f, 1.00f, 0.00f,
                                    0.00f, 0.00f, 0.00f, 0.00f, 1.00f
                                  };
            ImageAttributes ia;
            ia.SetColorMatrix(&GrayMat);
            m_pGdi->DrawImage(*pII->pImage, destF, srcF.X, srcF.Y, srcF.Width, srcF.Height, unit, &ia);
        }
    }
}

void Layers::Transform(int xform)
{
    Rect r = m_pLayer->lrect;
    Bitmap *pBmp = m_pDC->GetBitmap();

    if (xform == LIGHTEN) {
        ColorMatrix HotMat = {  1.05f, 0.00f, 0.00f, 0.00f, 0.00f,
                                0.00f, 1.05f, 0.00f, 0.00f, 0.00f,
                                0.00f, 0.00f, 1.05f, 0.00f, 0.00f,
                                0.00f, 0.00f, 0.00f, 1.00f, 0.00f,
                                0.05f, 0.05f, 0.05f, 0.00f, 1.00f
                             };
        ImageAttributes ia;
        ia.SetColorMatrix(&HotMat);
        m_pGdi->DrawImage((Image*)pBmp, r, 0, 0, r.Width, r.Height, UnitPixel, &ia);
    } else if (xform == GRAYSCALE) {
        ColorMatrix GrayMat = { 0.30f, 0.30f, 0.30f, 0.00f, 0.00f,
                                0.59f, 0.59f, 0.59f, 0.00f, 0.00f,
                                0.11f, 0.11f, 0.11f, 0.00f, 0.00f,
                                0.00f, 0.00f, 0.00f, 1.00f, 0.00f,
                                0.00f, 0.00f, 0.00f, 0.00f, 1.00f
                              };
        ImageAttributes ia;
        ia.SetColorMatrix(&GrayMat);
        m_pGdi->DrawImage((Image*)pBmp, r, 0, 0, r.Width, r.Height, UnitPixel, &ia);
    }

    delete pBmp;
}

//=============================================================================
//
// Regenerate
//
// Purpose:     Marks the stack to be regenerated on the next paint operation.
//              If a layer index is passed, it will reset all of the layer rects
//              above and including the index to zero, causing them to be
//              recalcculated from the frame rect
//
// Parameters:  x   - [in] the x offset
//              y   - [in] the y offset
//
// Returns:     None
//
void Layers::Regenerate(int layerIdx)
{
    Frame.bUseBitmap = FALSE;

    if (layerIdx != -1) {
        for (layer = m_Layers.begin() + layerIdx; layer != m_Layers.end(); ++layer) {
            (*layer).lrect.Width = 0;
            (*layer).lrect.Height = 0;
        }
    }
}

//=============================================================================
//
// PaintStack()
//
// Procedure:   1.  Create the borders and clipping region
//              2.  Paint all the layers into the device context
//              3.  Flatten the layers into a bitmap
//
//=============================================================================
void Layers::PaintStack(MemDC* pDC, Graphics* pGraphics)
{
    // the Frame must have a rect
    ASSERT(!(Frame.frect.Width == 0 && Frame.frect.Height == 0));
    // set the Graphics object
    m_pGdi = pGraphics;
    // set the MemDC object
    m_pDC = pDC;
    // set clip region
    SetClipping(m_pGdi);

    for (layer = m_Layers.begin(); layer != m_Layers.end(); ++layer) {
        // pointer to this layer
        m_pLayer = &(*layer);

        // if the layer rect is not defined, it uses the Frame rect
        if ((m_pLayer->lrect.Width == 0) && (m_pLayer->lrect.Height == 0)) {
            m_pLayer->lrect = Frame.frect;
        }

        if (m_pLayer->LayerShape == UNDEFINED) {
            m_pLayer->LayerShape = Frame.OuterBorder.shape;
        }

        // paint the layer
        PaintLayers();
    }

    // restore the clip region
    RestoreClipping(m_pGdi);
    // paint the borders
    PaintBorders();
    // delete dc in case of regeneration
    m_dc.DeleteDC();
    int x       = Frame.frect.X;
    int y       = Frame.frect.Y;
    int width   = Frame.frect.Width;
    int height  = Frame.frect.Height;
    // store into m_dc
    CBitmap bmp;
    m_dc.CreateCompatibleDC(pDC);
    bmp.CreateCompatibleBitmap(pDC, width, height);
    m_dc.SelectObject(&bmp);
    m_dc.BitBlt(0, 0, width, height, pDC, x, y, SRCCOPY);
    bmp.DeleteObject();
    Frame.bUseBitmap = TRUE;
}
