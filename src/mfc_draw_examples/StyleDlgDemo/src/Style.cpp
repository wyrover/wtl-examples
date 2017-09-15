//
// Style.cpp: implementation file for the Style class and Stack class.
//
// Author:  Darren Sessions
//
//
// Description:
//
//      The Stack class defines the User API of the Style Toolkit.  The Style
//      class is used to paint the stacks.
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
#include "Style.h"

Style::Style()
{
    // pre allocate some stack space
    m_Stacks.reserve(5);
}

Style::~Style()
{
}

//=============================================================================
//
// AddStack()
//
// Purpose:     Adds a stack to the top of this style
//
// Parameters:  stack   - [in] the stack to add
//
// Returns:     None
//
int Style::AddStack(Stack& stack)
{
    m_Stacks.push_back(stack);
    return (int)(m_Stacks.size() - 1);
}

//=============================================================================
//
// PaintStyle()
//
// Purpose:     Paints all the stacks for this style
//
// Parameters:  pDevC   - [in] the device context
//              rect    - [in] the bounding rect for this style
//
// Returns:     None
//
void Style::PaintStyle(CDC* pDevC, CRect rect)
{
    MemDC pDC(pDevC, rect, TRUE);
    Graphics gdi(pDC->m_hDC);
    // default smoothing mode
    gdi.SetSmoothingMode(SmoothingModeAntiAlias);
    gdi.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);

    // paint all stacks
    for (stack = m_Stacks.begin(); stack != m_Stacks.end(); ++stack) {
        if ((*stack).Frame.bUseBitmap) {
            // copy the bitmap to the DC
            pDC->BitBlt((*stack).Frame.frect.X,
                        (*stack).Frame.frect.Y,
                        (*stack).Frame.frect.Width,
                        (*stack).Frame.frect.Height,
                        (*stack).GetDC(), 0, 0, SRCCOPY);
        } else {
            // the first call to PaintStyle will create all the bitmaps here
            (*stack).PaintStack(pDC, &gdi);
        }
    }
}

//=============================================================================
//
// SetPosition()
//
// Purpose:     Sets the origin of all the stacks and layers
//
// Parameters:  x   - [in] the x offset
//              y   - [in] the y offset
//
// Returns:     None
//
void Style::SetPosition(int x, int y)
{
    // iterate all stacks
    for (stack = m_Stacks.begin(); stack != m_Stacks.end(); ++stack) {
        ASSERT(!((*stack).Frame.frect.Width == 0 && (*stack).Frame.frect.Height == 0));
        (*stack).SetPosition(x, y);
    }
}

//=============================================================================
//
// Regenerate()
//
// Purpose:     Marks all the stacks in the style for regeneration
//
// Parameters:  None
//
// Returns:     None
//
void Style::Regenerate()
{
    // iterate all stacks
    for (stack = m_Stacks.begin(); stack != m_Stacks.end(); ++stack) {
        (*stack).Regenerate();
    }
}

//=============================================================================
int Style::GetTopIndex()
//=============================================================================
{
    return (int)(m_Stacks.size() - 1);
}


//=============================================================================
// operator =
Stack& Stack::operator=(const Stack& other)
//=============================================================================
{
    Layers::m_Layers.clear();
    Layers::Copy(other);
    return *this;
}

//=============================================================================
// operator +=
Stack& Stack::operator+=(const Stack& other)
//=============================================================================
{
    // the region indexes need to be adjusted to add
    // the layers beneath it
    int cnt = (int)m_Layers.size();
    Layers::CopyLayers(other);

    for (layer = m_Layers.begin() + cnt; layer != m_Layers.end(); ++layer) {
        // just adjust all of them even if they don't apply
        (*layer).rgnIndex[0] += cnt;
        (*layer).rgnIndex[1] += cnt;
    }

    return *this;
}

//=============================================================================
// operator +
Stack operator+(const Stack& lhs, const Stack& rhs)
//=============================================================================
{
    return Stack(lhs) += rhs;
}

//=============================================================================
// GDI constructor with boundaries
Stack::Stack(SRect sr)
//=============================================================================
{
    Init();
    MakeFrame(sr.rect);
}

//=============================================================================
// GDI constructor with Initial layer
Stack::Stack(SRect sr, Clr clr)
//=============================================================================
{
    Init();
    MakeFrame(sr.rect);
    AddLayer(sr.rect, clr);
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
int Stack::AddLayer()
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
int Stack::AddLayer(SRect sr, Clr clr)
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
// SetRect()
//
// Purpose:     Sets the size and position of the stack relative to the
//              parent's origin (the parent is the Style that will paint
//              this object)
//
// Parameters:  rect    - [in] CRect object
//
// Returns:     None
//
void Stack::SetRect(SRect rect)
{
    MakeFrame(rect);
}

//=============================================================================
//
// SetShape()
//
// Purpose:     Sets the shape of the stacks borders to the passed argurmen
//
// Parameters:  shape   - [in] one of LayerShapes
//              radius  - [in] radius of corner for ROUNDRECT type shape
//
// Returns:     None
//
void Stack::SetShape(int shape, int radius)
{
    Layers::SetShape(shape, radius);
}

//=============================================================================
//
// Regenerate()
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
void Stack::Regenerate(int layerIdx)
{
    Layers::Regenerate(layerIdx);
}

//=============================================================================
//
// SetPosition()
//
// Purpose:     Moves the frame and all the layers in the stack to the x y position
//
// Parameters:  x, y - [in] the new position
//
// Returns:     None
//
void Stack::SetPosition(int x, int y)
{
    int xoff = x - Frame.frect.X;
    int yoff = y - Frame.frect.Y;
    // set the frame origin
    Frame.frect.X = x;
    Frame.frect.Y = y;

    // iterate all the layers
    for (layer = m_Layers.begin(); layer != m_Layers.end(); ++layer) {
        (*layer).lrect.X += xoff;
        (*layer).lrect.Y += yoff;
    }
}

//=============================================================================
//
// FillSolid()
//
// Purpose:     Defines the layer as a solid fill
//
// Parameters:  cr          - [in] the rect for this layer
//              clr1        - [in] color for this layer
//
// Returns:     index to layer added
//
int Stack::FillSolid(SRect cr, Clr color)
{
    int layer = AddLayer();
    m_Layers[layer].lrect = cr.rect;
    m_Layers[layer].clr1 = color.value;
    m_Layers[layer].LayerType = SOLID;
    return layer;
}

//=============================================================================
//
// FillSolid()
//
// Purpose:     Defines the layer as a solid fill
//
// Parameters:  clr1        - [in] color for this layer
//
// Returns:     index to layer added
//
int Stack::FillSolid(Clr color)
{
    int layer = AddLayer();
    m_Layers[layer].clr1 = color.value;
    m_Layers[layer].LayerType = SOLID;
    return layer;
}

//=============================================================================
//
// FillGrad2()
//
// Purpose:     Defines the layer as a 2 color gradient
//
// Parameters:  rect        - [in] Rectangle for this layer
//              style       - [in] Gradient style - HORIZ, VERT, DIAGF, DIAGR
//              clr1        - [in] Begin color for gradient
//              clr2        - [in] End color for gradient
//              diffpt      - [in] Diffusion point (-1.0, 1.0)
//                                 negative values mean diffuse relative to clr2 position
//
// Returns:     index to layer added
//
int Stack::FillGrad2(SRect sr, int style, Clr clr1, Clr clr2, float diffpt)
{
    int layer = AddLayer();
    m_Layers[layer].lrect = sr.rect;
    m_Layers[layer].gradMode = style;
    m_Layers[layer].clr1 = clr1.value;
    m_Layers[layer].clr2 = clr2.value;
    m_Layers[layer].rParams[0] = diffpt;
    m_Layers[layer].LayerType = BIGRAD;
    return layer;
}

//=============================================================================
//
// FillGrad2()
//
// Purpose:     Defines the layer as a 2 color gradient
//
// Parameters:  style       - [in] Gradient style - HORIZ, VERT, DIAGF, DIAGR
//              clr1        - [in] Begin color for gradient
//              clr2        - [in] End color for gradient
//              diffpt      - [in] Diffusion point (-1.0, 1.0)
//                                 negative values mean diffuse relative to clr2 position
//
// Returns:     index to layer added
//
int Stack::FillGrad2(int style, Clr clr1, Clr clr2, float diffpt)
{
    int layer = AddLayer();
    m_Layers[layer].gradMode = style;
    m_Layers[layer].rParams[0] = diffpt;
    m_Layers[layer].clr1 = clr1.value;
    m_Layers[layer].clr2 = clr2.value;
    m_Layers[layer].LayerType = BIGRAD;
    return layer;
}

//=============================================================================
//
// FillRadial()
//
// Purpose:     Defines the layer as a 2 radial gradient
//
// Parameters:  rect        - [in] Rectangle for this layer
//              clr1        - [in] Begin color for gradient
//              clr2        - [in] End color for gradient
//
// Returns:     index to layer added
//
int Stack::FillRadial(SRect sr, Clr clr1, Clr clr2)
{
    int layer = AddLayer();
    m_Layers[layer].lrect = sr.rect;
    m_Layers[layer].clr1 = clr1.value;
    m_Layers[layer].clr2 = clr2.value;
    m_Layers[layer].LayerType = RADIAL;
    return layer;
}

//=============================================================================
//
// FillRadial()
//
// Purpose:     Defines the layer as a 2 radial gradient
//
// Parameters:  clr1        - [in] Begin color for gradient
//              clr2        - [in] End color for gradient
//
// Returns:     index to layer added
//
int Stack::FillRadial(Clr clr1, Clr clr2)
{
    int layer = AddLayer();
    m_Layers[layer].clr1 = clr1.value;
    m_Layers[layer].clr2 = clr2.value;
    m_Layers[layer].LayerType = RADIAL;
    return layer;
}

//=============================================================================
//
// FillGrad3()
//
// Purpose:     Defines the layer as a 3 color gradient
//
// Parameters:  cr          - [in] rect for this layer
//              style       - [in] Gradient style - HORIZ, VERT, DIAGF, DIAGR
//              clr1        - [in] Begin color for gradient
//              clr2        - [in] Middle color for gradient
//              clr3        - [in] End color for gradient
//              diffpt      - [in] Diffusion point (-1.0, 1.0) (future)
//
// Returns:     index to layer added
//=============================================================================///
int Stack::FillGrad3(SRect sr, int style, Clr clr1, Clr clr2, Clr clr3, float diffpt)
{
    int layer = AddLayer();
    m_Layers[layer].lrect = sr.rect;
    m_Layers[layer].gradMode = style;
    m_Layers[layer].rParams[0] = diffpt;
    m_Layers[layer].clr1 = clr1.value;
    m_Layers[layer].clr2 = clr2.value;
    m_Layers[layer].clr3 = clr3.value;
    m_Layers[layer].LayerType = TRIGRAD;
    return layer;
}

//=============================================================================
//
// FillGrad3()
//
// Purpose:     Defines the layer as a 3 color gradient
//
// Parameters:  style       - [in] Gradient style - HORIZ, VERT, DIAGF, DIAGR
//              clr1        - [in] Begin color for gradient
//              clr2        - [in] Middle color for gradient
//              clr3        - [in] End color for gradient
//              diffpt      - [in] Diffusion point (0.0, 1.0)
//
// Returns:     index to layer added
//=============================================================================///
int Stack::FillGrad3(int style, Clr clr1, Clr clr2, Clr clr3, float diffpt)
{
    int layer = AddLayer();
    m_Layers[layer].gradMode = style;
    m_Layers[layer].rParams[0] = diffpt;
    m_Layers[layer].clr1 = clr1.value;
    m_Layers[layer].clr2 = clr2.value;
    m_Layers[layer].clr3 = clr3.value;
    m_Layers[layer].LayerType = TRIGRAD;
    return layer;
}

//=============================================================================
//
// SetOuterBorder()
//
// Purpose:     Sets the Stacks border parameters
//
// Parameters:  width       - [in] the border width
//              clr         - [in] color of border or upper left color if both are defined
//              brclr       - [in] optional - bottom right color
//
// Returns:     None
//
void Stack::SetOuterBorder(int width, Clr clr, Clr brclr)
{
    Frame.OuterBorder.width = width;
    Frame.OuterBorder.ulclr = clr.value;
    Frame.OuterBorder.brclr = brclr.value;
}
void Stack::SetOuterBorder(int width, Clr clr)
{
    Frame.OuterBorder.width = width;
    Frame.OuterBorder.ulclr = clr.value;
    Frame.OuterBorder.brclr = clr.value;
}

//=============================================================================
//
// SetMiddleBorder()
//
// Purpose:     Sets the Stacks border parameters
//
// Parameters:  width       - [in] the border width
//              clr         - [in] color of border or upper left color if both are defined
//              brclr       - [in] optional - bottom right color
//
// Returns:     None
//
void Stack::SetMiddleBorder(int width, Clr clr, Clr brclr)
{
    Frame.MiddleBorder.width = width;
    Frame.MiddleBorder.ulclr = clr.value;
    Frame.MiddleBorder.brclr = brclr.value;
}
void Stack::SetMiddleBorder(int width, Clr clr)
{
    Frame.MiddleBorder.width = width;
    Frame.MiddleBorder.ulclr = clr.value;
    Frame.MiddleBorder.brclr = clr.value;
}

//=============================================================================
//
// SetInnerBorder()
//
// Purpose:     Sets the Stacks border parameters
//
// Parameters:  width       - [in] the border width
//              clr         - [in] color of border or upper left color if both are defined
//              brclr       - [in] optional - bottom right color
//
// Returns:     None
//
void Stack::SetInnerBorder(int width, Clr clr, Clr brclr)
{
    Frame.InnerBorder.width = width;
    Frame.InnerBorder.ulclr = clr.value;
    Frame.InnerBorder.brclr = brclr.value;
}
void Stack::SetInnerBorder(int width, Clr clr)
{
    Frame.InnerBorder.width = width;
    Frame.InnerBorder.ulclr = clr.value;
    Frame.InnerBorder.brclr = clr.value;
}


//=============================================================================
//
// FillBar()
//
// Purpose:     Adds a gradient bar effect to one of edges
//
// Parameters:  cr          - [in] the rectangle containing this edge
//              type        - [in] bar type - TOP_EDGE, LEFT_EDGE, RIGHT_EDGE, BOTTOM_EDGE
//              width       - [in] the bar width
//              tlclr       - [in] top or left color
//              brclr       - [in] bottom or right color
//
// Returns:     index to layer added
//
int Stack::FillBar(SRect sr,  int type, int width, Clr tlclr, Clr brclr)
{
    int layer = AddLayer();
    m_Layers[layer].lrect = sr.rect;
    m_Layers[layer].LayerType = type;
    m_Layers[layer].width = width;
    m_Layers[layer].clr1 = tlclr.value;
    m_Layers[layer].clr2 = brclr.value;
    m_Layers[layer].clr3 = brclr.value;
    return layer;
}

//=============================================================================
//
// FillBar()
//
// Purpose:     Adds a gradient bar effect to one of edges
//
// Parameters:  type        - [in] bar type - TOP_EDGE, LEFT_EDGE, RIGHT_EDGE, BOTTOM_EDGE
//              width       - [in] the bar width
//              tlclr       - [in] top or left color
//              brclr       - [in] bottom or right color
//
// Returns:     index to layer added
//
int Stack::FillBar(int type, int width, Clr tlclr, Clr brclr)
{
    int layer = AddLayer();
    m_Layers[layer].LayerType = type;
    m_Layers[layer].width = width;
    m_Layers[layer].clr1 = tlclr.value;
    m_Layers[layer].clr2 = brclr.value;
    m_Layers[layer].clr3 = brclr.value;
    return layer;
}

//=============================================================================
//
// FillBar()
//
// Purpose:     Adds a gradient bar effect to one of edges
//
// Parameters:  cr          - [in] the rectangle containing this edge
//              type        - [in] bar type - TOP_EDGE, LEFT_EDGE, RIGHT_EDGE, BOTTOM_EDGE
//              width       - [in] the bar width
//              tlclr       - [in] top or left color
//              mclr        - [in] middle color
//              brclr       - [in] bottom or right color
//              profile     - [in] array of 3 floats defining trinagle gradient
//
// Returns:     index to layer added
//
int Stack::FillBar(SRect sr,  int type, int width, Clr tlclr, Clr mclr, Clr brclr, float* profile)
{
    int layer = AddLayer();
    m_Layers[layer].lrect = sr.rect;
    m_Layers[layer].LayerType = type;
    m_Layers[layer].width = width;
    m_Layers[layer].clr1 = tlclr.value;
    m_Layers[layer].clr2 = mclr.value;
    m_Layers[layer].clr3 = brclr.value;
    memcpy(m_Layers[layer].rParams, profile, 3 * sizeof(float));
    return layer;
}

//=============================================================================
//
// FillBar()
//
// Purpose:     Adds a gradient bar effect to one of edges
//
// Parameters:  type        - [in] bar type - TOP_EDGE, LEFT_EDGE, RIGHT_EDGE, BOTTOM_EDGE
//              width       - [in] the bar width
//              tlclr       - [in] top or left color
//              mclr        - [in] middle color
//              brclr       - [in] bottom or right color
//              profile     - [in] array of 3 floats defining trinagle gradient
//
// Returns:     index to layer added
//
int Stack::FillBar(int type, int width, Clr tlclr, Clr mclr, Clr brclr, float* profile)
{
    int layer = AddLayer();
    m_Layers[layer].LayerType = type;
    m_Layers[layer].width = width;
    m_Layers[layer].clr1 = tlclr.value;
    m_Layers[layer].clr2 = mclr.value;
    m_Layers[layer].clr3 = brclr.value;
    memcpy(m_Layers[layer].rParams, profile, 3 * sizeof(float));
    return layer;
}

//=============================================================================
//
// FillWrap()
//
// Purpose:     Adds a gradient of size width to the rect and then tiles
//              with the tile mode
//
// Parameters:  type        - [in] tile type
//              width       - [in] the width of the tiled piece
//              tlclr       - [in] top or left color
//              mclr        - [in] middle color
//              brclr       - [in] bottom or right color
//
// Returns:     index to layer added
//
int Stack::FillWrap(int type, int width, Clr tlclr, Clr mclr, Clr brclr)
{
    int layer = AddLayer();
    m_Layers[layer].LayerType = WRAP;
    m_Layers[layer].width = width;
    m_Layers[layer].clr1 = tlclr.value;
    m_Layers[layer].clr2 = mclr.value;
    m_Layers[layer].clr3 = brclr.value;
    return layer;
}

//=============================================================================
//
// FillWrap()
//
// Purpose:     Adds a gradient of size width to the rect and then tiles
//              with the tile mode
//
// Parameters:  type        - [in] tile type
//              width       - [in] the width of the tiled piece
//              tlclr       - [in] top or left color
//              mclr        - [in] middle color
//              brclr       - [in] bottom or right color
//
// Returns:     index to layer added
//
int Stack::FillWrap(SRect sr, int type, int width, Clr tlclr, Clr mclr, Clr brclr)
{
    int layer = AddLayer();
    m_Layers[layer].lrect = sr.rect;
    m_Layers[layer].LayerType = WRAP;
    m_Layers[layer].width = width;
    m_Layers[layer].clr1 = tlclr.value;
    m_Layers[layer].clr2 = mclr.value;
    m_Layers[layer].clr3 = brclr.value;
    return layer;
}

//=============================================================================
//
// CreateRgn()
//
// Purpose:     Create a region
//
// Parameters:  cr          - [in] the rectangle bounding the region
//              shape       - [in] the clipping shape
//
// Returns:     index to layer referencing this clip region
//
int Stack::CreateRgn(SRect sr, int shape)
{
    int layer = AddLayer();
    m_Layers[layer].lrect = sr.rect;
    m_Layers[layer].LayerType = CREATERGN;
    m_Layers[layer].LayerShape = shape;
    return layer;
}

//=============================================================================
//
// CombineRgnModify()
//
// Purpose:     Combines two clipping regions using the passed clipping mode
//              The resultRgn will be modified
//
// Parameters:  resultRgn   - [in] this region will contain the combined result
//              combineRgn  - [in] this region will be combined with the resultRgn
//              mode        - [in] the clipping mode
//
// Returns:     index to layer added
//
int Stack::CombineRgnModify(int resultRgn, int combineRgn, int mode)
{
    int layer = AddLayer();
    m_Layers[layer].LayerType = COMBINEMOD;
    m_Layers[layer].clipMode = mode;
    m_Layers[layer].rgnIndex[0] = resultRgn;
    m_Layers[layer].rgnIndex[1] = combineRgn;
    return layer;
}

//=============================================================================
//
// CombineRgnCreate()
//
// Purpose:     Combines two clipping regions using the passed clipping mode
//              The combined result will be placed in a new region
//
// Parameters:  rgn1    - [in] this region will copied first
//              rgn2    - [in] this region will be combined with the copy
//              mode    - [in] the clipping mode
//
// Returns:     index to layer added
//
int Stack::CombineRgnCreate(int rgn1, int rgn2, int mode)
{
    ASSERT(rgn1 != NULL && rgn2 != NULL);
    int layer = AddLayer();
    m_Layers[layer].LayerType = COMBINENEW;
    m_Layers[layer].clipMode = mode;
    m_Layers[layer].rgnIndex[0] = rgn1;
    m_Layers[layer].rgnIndex[1] = rgn2;
    return layer;
}

//=============================================================================
//
// ApplyClipRgn()
//
// Purpose:     Replace the current clipping region
//
// Parameters:  region      - [in] the new region
//
// Returns:     index to layer added
//
int Stack::ApplyClipRgn(int region)
{
    int layer = AddLayer();
    m_Layers[layer].LayerType = APPLYCLIP;
    m_Layers[layer].rgnIndex[0] = region;
    return layer;
}

//=============================================================================
//
// RestoreClipRgn()
//
// Purpose:     Restores the clipping region to the Fram region
//
// Parameters:  None
//
// Returns:     index to layer added
//
int Stack::RestoreClipRgn()
{
    int layer = AddLayer();
    m_Layers[layer].LayerType = RESTORECLIP;
    return layer;
}


//=============================================================================
//
// SetSmoothing()
//
// Purpose:     Set the current smoothing mode
//
// Parameters:  mode    - [in] one of SmoothModes
//
// Returns:     index to layer added
//
int Stack::SetSmoothing(int mode)
{
    int layer = AddLayer();
    m_Layers[layer].LayerType = SETSMOOTH;
    m_Layers[layer].clipMode = mode;
    return layer;
}

//=============================================================================
//
// RestoreSmoothing()
//
// Purpose:     Set the current smoothing mode
//
// Parameters:  mode    - [in] one of SmoothModes
//
// Returns:     index to layer added
//
int Stack::RestoreSmoothing()
{
    int layer = AddLayer();
    m_Layers[layer].LayerType = RESTORESMOOTH;
    return layer;
}

//=============================================================================
//
// ApplyBlur()
//
// Purpose:     Applies a blur effect to the current frame
//
// Parameters:  width       - [in] the amount of blur
//
// Returns:     index to layer added
//
int Stack::FillBlur(int region, Clr clr, int width)
{
    int layer = AddLayer();
    m_Layers[layer].clr1 = clr.value;
    m_Layers[layer].LayerType = REGIONBLUR;
    m_Layers[layer].width = width;
    m_Layers[layer].rgnIndex[0] = region;
    return layer;
}

//=============================================================================
//
// AddImage()
//
// Purpose:     Adds an image to the stack
//
// Parameters:  pt          - [in] offset into the layer rect
//              id          - [in] resource id
//              type        - [in] resource type
//              clip        - [in] TRUE if clipped, else streched
//              xform       - [in] apply image xform - one of ImageXForms
//
// Returns:     index to layer added
//
int Stack::AddImage(SPoint sp, UINT id, LPCTSTR type, int clip, int xform)
{
    IMAGEINFO ii;
    ::ZeroMemory(&ii, sizeof(IMAGEINFO));
    ii.destpt = sp.point;
    ii.resID = id;
    ii.resType = type;
    ii.xform = xform;
    ii.clip = clip;
    Layers::m_Images.push_back(ii);
    int layer = AddLayer();
    m_Layers[layer].LayerType = IMAGE;
    m_Layers[layer].imgIndex = (int)(m_Images.size() - 1);
    return layer;
}

//=============================================================================
//
// AddImage()
//
// Purpose:     Adds an image to the stack
//
// Parameters:  dest        - [in] images destination within the layer rect
//              src         - [in] src rect within the image
//              id          - [in] resource id
//              type        - [in] resource type
//              clip        - [in] TRUE if clipped, else streched
//              xform       - [in] apply image xform - one of ImageXForms
//
// Returns:     index to layer added
//
int Stack::AddImage(SPoint dest, SPoint src, UINT id, LPCTSTR type, int clip, int xform)
{
    IMAGEINFO ii;
    ::ZeroMemory(&ii, sizeof(IMAGEINFO));
    ii.destpt = dest.point;
    ii.srcpt = src.point;
    ii.resID = id;
    ii.resType = type;
    ii.xform = xform;
    ii.clip = clip;
    m_Images.push_back(ii);
    int layer = AddLayer();
    m_Layers[layer].LayerType = IMAGE;
    m_Layers[layer].imgIndex = (int)(m_Images.size() - 1);
    return layer;
}

//=============================================================================
//
// AddString()
//
// Purpose:     Adds a string to the stack
//
// Parameters:  str         - [in] the CString to add
//              offset      - [in] CPoint offset into the Frame rect
//              clr         - [in] sting color
//              size        - [in] vertical size of the string
//              style       - [in] the font style (one of enum FontStyles)
//              name        - [in] Font Family name string
//
// Returns:     index to layer added
//
int Stack::AddString(CString str, SPoint offset, Clr clr, int size, int style, WCHAR* name)
{
    TEXTINFO ti;
    ::ZeroMemory(&ti, sizeof(TEXTINFO));
    memcpy(ti.fname, name, 2 * wcslen(name));
    ti.fsize = size;
    ti.fstyle = style;
    ti.foffset.X = (float)offset.point.X;
    ti.foffset.Y = (float)offset.point.Y;
#ifdef _MBCS
    // convert the CString to wstring
    size_t cssize = strlen(str) + 1;
    size_t wcsize = cssize * sizeof(wchar_t);
    ti.string.reserve(wcsize);
    wchar_t *pwstr = (wchar_t*)malloc(wcsize);
    MultiByteToWideChar(CP_ACP, 0, str, (int)cssize, pwstr, (int)wcsize);
    ti.string = pwstr;
    m_Strings.push_back(ti);
    free(pwstr);
#else
    ti.string = str;
    m_Strings.push_back(ti);
#endif
    int layer = AddLayer();
    m_Layers[layer].LayerType = STRING;
    m_Layers[layer].strIndex = (int)(m_Strings.size() - 1);
    m_Layers[layer].clr1 = clr.value;
    return layer;
}

//=============================================================================
//
// AddAlignString()
//
// Purpose:     Adds a string to the stack with alignment
//
// Parameters:  str         - [in] the CString to add
//              alignment   - [in] the string alignment (one of enum StringAlign)
//                                 relative to the frame's rectangle
//              offset      - [in] shrink the bounding rectangle by this amount
//              clr         - [in] sting color
//              size        - [in] vertical size of the string
//              style       - [in] the font style (one of enum FontStyles)
//              name        - [in] Font Family name string
//
// Returns:     index to layer added
//
int Stack::AddAlignString(CString str, int alignment, SPoint offset, Clr clr,
                          int size, int style, WCHAR* name)
{
    TEXTINFO ti;
    ::ZeroMemory(&ti, sizeof(TEXTINFO));
    memcpy(ti.fname, name, 2 * wcslen(name));
    ti.fsize = size;
    ti.fstyle = style;
    ti.align = alignment;
    ti.foffset.X = (float)offset.point.X;
    ti.foffset.Y = (float)offset.point.Y;
#ifdef _MBCS
    // convert the CString to wstring
    size_t cssize = strlen(str) + 1;
    size_t wcsize = cssize * sizeof(wchar_t);
    ti.string.reserve(wcsize);
    wchar_t *pwstr = (wchar_t*)malloc(wcsize);
    MultiByteToWideChar(CP_ACP, 0, str, (int)cssize, pwstr, (int)wcsize);
    ti.string = pwstr;
    m_Strings.push_back(ti);
    free(pwstr);
#else
    ti.string = str;
    m_Strings.push_back(ti);
#endif
    int layer = AddLayer();
    m_Layers[layer].LayerType = STRING;
    m_Layers[layer].strIndex = (int)(m_Strings.size() - 1);
    m_Layers[layer].clr1 = clr.value;
    return layer;
}


//=============================================================================
//
// AddAlignString()
//
// Purpose:     Adds a string to the stack with alignment
//
// Parameters:  sr          - [in] the bounding rectangle
//              str         - [in] the CString to add
//              alignment   - [in] the string alignment (one of enum StringAlign)
//                                 relative to the passed rectangle
//              offset      - [in] shrink the bounding rectangle by this amount
//              clr         - [in] sting color
//              size        - [in] vertical size of the string
//              style       - [in] the font style (one of enum FontStyles)
//              name        - [in] Font Family name string
//
// Returns:     index to layer added
//
int Stack::AddAlignString(SRect sr, CString str, int alignment, SPoint offset, Clr clr,
                          int size, int style, WCHAR* name)
{
    TEXTINFO ti;
    ::ZeroMemory(&ti, sizeof(TEXTINFO));
    memcpy(ti.fname, name, 2 * wcslen(name));
    ti.fsize = size;
    ti.fstyle = style;
    ti.align = alignment;
#ifdef _MBCS
    // convert the CString to wstring
    size_t cssize = strlen(str) + 1;
    size_t wcsize = cssize * sizeof(wchar_t);
    ti.string.reserve(wcsize);
    wchar_t *pwstr = (wchar_t*)malloc(wcsize);
    MultiByteToWideChar(CP_ACP, 0, str, (int)cssize, pwstr, (int)wcsize);
    ti.string = pwstr;
    m_Strings.push_back(ti);
    free(pwstr);
#else
    ti.string = str;
    m_Strings.push_back(ti);
#endif
    int layer = AddLayer();
    m_Layers[layer].lrect = sr.rect;
    m_Layers[layer].LayerType = STRING;
    m_Layers[layer].strIndex = (int)(m_Strings.size() - 1);
    m_Layers[layer].clr1 = clr.value;
    return layer;
}

//=============================================================================
//
// AddEffectString()
//
// Purpose:     Adds a string to the stack with alignment
//
// Parameters:  str         - [in] the CString to add
//              offset      - [in] shrink the bounding rectangle by this amount
//              effect      = [in] one of enum StringEffects
//              size        - [in] vertical size of the string
//              style       - [in] the font style (one of enum FontStyles)
//              name        - [in] Font Family name string
//              clr1        - [in] sting face color
//              clr2        - [in] first effect color
//              width2      - [in] size of first effect
//              clr3        - [in] second effect color [optional] - depends on effect
//              width3      - [in] size of second effect [optional] - depends on effect
//
// Returns:     index to layer added
//
int Stack::AddEffectString(CString str, SPoint offset, int effect,
                           int size, int style, WCHAR* name,
                           Clr clr1, Clr clr2, int width2, Clr clr3, int width3)
{
    TEXTINFO ti;
    ::ZeroMemory(&ti, sizeof(TEXTINFO));
    memcpy(ti.fname, name, 2 * wcslen(name));
    ti.fsize = size;
    ti.fstyle = style;
    ti.foffset.X = (float)offset.point.X;
    ti.foffset.Y = (float)offset.point.Y;
#ifdef _MBCS
    // convert the CString to wstring
    size_t cssize = strlen(str) + 1;
    size_t wcsize = cssize * sizeof(wchar_t);
    ti.string.reserve(wcsize);
    wchar_t *pwstr = (wchar_t*)malloc(wcsize);
    MultiByteToWideChar(CP_ACP, 0, str, (int)cssize, pwstr, (int)wcsize);
    ti.string = pwstr;
    m_Strings.push_back(ti);
    free(pwstr);
#else
    ti.string = str;
    m_Strings.push_back(ti);
#endif
    int layer = AddLayer();
    //m_Layers[layer].lrect = sr.rect;
    m_Layers[layer].LayerType = EFFECTSTRING;
    m_Layers[layer].strIndex = (int)(m_Strings.size() - 1);
    m_Layers[layer].clr1 = clr1.value;
    m_Layers[layer].clr2 = clr2.value;
    m_Layers[layer].clr3 = clr3.value;
    m_Layers[layer].rParams[0] = (float)effect;
    m_Layers[layer].rParams[1] = (float)width2;
    m_Layers[layer].rParams[2] = (float)width3;
    return layer;
}


//=============================================================================
//
// AddEffectString()
//
// Purpose:     Adds a string to the stack with alignment
//
// Parameters:  sr          - [in] the bounding rectangle
//              str         - [in] the CString to add
//              offset      - [in] shrink the bounding rectangle by this amount
//              effect      = [in] one of enum StringEffects
//              size        - [in] vertical size of the string
//              style       - [in] the font style (one of enum FontStyles)
//              name        - [in] Font Family name string
//              clr1        - [in] sting face color
//              clr2        - [in] first effect color
//              width2      - [in] size of first effect
//              clr3        - [in] second effect color [optional] - depends on effect
//              width3      - [in] size of second effect [optional] - depends on effect
//
// Returns:     index to layer added
//
int Stack::AddEffectString(SRect sr, CString str, SPoint offset, int effect,
                           int size, int style, WCHAR* name,
                           Clr clr1, Clr clr2, int width2, Clr clr3, int width3)
{
    TEXTINFO ti;
    ::ZeroMemory(&ti, sizeof(TEXTINFO));
    memcpy(ti.fname, name, 2 * wcslen(name));
    ti.fsize = size;
    ti.fstyle = style;
    ti.foffset.X = (float)offset.point.X;
    ti.foffset.Y = (float)offset.point.Y;
#ifdef _MBCS
    // convert the CString to wstring
    size_t cssize = strlen(str) + 1;
    size_t wcsize = cssize * sizeof(wchar_t);
    ti.string.reserve(wcsize);
    wchar_t *pwstr = (wchar_t*)malloc(wcsize);
    MultiByteToWideChar(CP_ACP, 0, str, (int)cssize, pwstr, (int)wcsize);
    ti.string = pwstr;
    m_Strings.push_back(ti);
    free(pwstr);
#else
    ti.string = str;
    m_Strings.push_back(ti);
#endif
    int layer = AddLayer();
    m_Layers[layer].lrect = sr.rect;
    m_Layers[layer].LayerType = EFFECTSTRING;
    m_Layers[layer].strIndex = (int)(m_Strings.size() - 1);
    m_Layers[layer].clr1 = clr1.value;
    m_Layers[layer].clr2 = clr2.value;
    m_Layers[layer].clr3 = clr3.value;
    m_Layers[layer].rParams[0] = (float)effect;
    m_Layers[layer].rParams[1] = (float)width2;
    m_Layers[layer].rParams[2] = (float)width3;
    return layer;
}


//=============================================================================
//
// ApplyTransform()
//
// Purpose:     Set the current smoothing mode
//
// Parameters:  xform   - [in] one of LayerXForms
//
// Returns:     index to layer added
//
int Stack::ApplyTransform(int xform)
{
    int layer = AddLayer();
    m_Layers[layer].LayerType = APPLYXFORM;
    m_Layers[layer].gradMode = xform;
    return layer;
}