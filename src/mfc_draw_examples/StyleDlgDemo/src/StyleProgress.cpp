//
// StyleProgress.cpp : Version 1.0 - see article at CodeProject.com
//
// Author:  Darren Sessions
//
//
// Description:
//     StyleProgress is a CProgressCtrl derived control that uses the Style class
//     and GDI+ to support different styles
//
// History
//     Version 1.0 - 2008 June 20
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
#include "StyleProgress.h"

StyleProgress::StyleProgress(void)
{
    m_bCreated  = FALSE;
    // default gray
    m_BackColor = RGB(0xC9, 0xC9, 0xC9);
    // default green
    m_ForeColor = RGB(0x00, 0xd3, 0x28);
    m_Lower = 0;
    m_Upper = 100;
    m_Pos = 50;
    m_Step = 5;
    // default will step the bottom layer of the second stack
    m_StepStackIdx = -1;
    m_StepLayerIdx = 0;
    m_StepLayerWidth = 0;
}

StyleProgress::~StyleProgress(void)
{
}

BEGIN_MESSAGE_MAP(StyleProgress, CProgressCtrl)
    ON_WM_ERASEBKGND()
    ON_WM_PAINT()
    ON_WM_NCPAINT()
END_MESSAGE_MAP()

void StyleProgress::OnPaint()
{
    CPaintDC dc(this); // device context for painting

    // need to create if default
    if (!m_bCreated) CreateDefaultStack();

    m_Style.PaintStyle(&dc, m_ProgRect);
}

BOOL StyleProgress::OnEraseBkgnd(CDC* pDC)
{
    return TRUE;
}

void StyleProgress::OnNcPaint()
{
    // Needed to stop the base from painting the border
}

void StyleProgress::AddStack(Stack stack)
{
    m_Style.AddStack(stack);
}

void StyleProgress::AddStepStack(Stack stack)
{
    // this function must get called, so get m_ProgRect here
    GetClientRect(m_ProgRect);
    m_StepStackIdx = m_Style.AddStack(stack);
    // default layer is zero - over ridden in SetStepLayer
    m_StepLayerWidth = m_Style.m_Stacks[m_StepStackIdx].m_Layers[0].lrect.Width;
    // the step layer needs to have its rect defined
    // e.g. use the rect version FillSolid(rect, Blue) instead of FillSolid(Blue)
    ASSERT(m_StepLayerWidth != 0);
    m_bCreated = TRUE;
}

void StyleProgress:: SetStepLayer(int layerIdx)
{
    // AddStepStack needs to be called before this funtion is called
    ASSERT(m_StepStackIdx != -1);
    m_StepLayerIdx = layerIdx;
    m_StepLayerWidth = m_Style.m_Stacks[m_StepStackIdx].m_Layers[layerIdx].lrect.Width;
}

void StyleProgress::SetForeColor(COLORREF color, int Alpha)
{
    m_ForeColor = color;
    m_ForeAlpha = Alpha;
}

void StyleProgress::SetBackColor(COLORREF color, int Alpha)
{
    m_BackColor = color;
    m_BackAlpha = Alpha;
}

void StyleProgress::UpdateStack()
{
    Rect frc, lrc;
    CRect crc;
    float ratio;
    int width;
    // AddStepStack needs to be called for 1 stack
    ASSERT(m_StepStackIdx != -1);
    // get the frame rect
    frc = m_Style.m_Stacks[m_StepStackIdx].Frame.frect;
    // calculate step position
    ratio = float(m_Pos) / float(m_Upper - m_Lower);
    width = (int)(ratio * m_StepLayerWidth);
    // adjust the rects
    frc.Width = width;
    lrc.Width = width;
    // set the new rects
    m_Style.m_Stacks[m_StepStackIdx].Frame.frect = frc;
    m_Style.m_Stacks[m_StepStackIdx].Regenerate(m_StepLayerIdx);

    // need to regenerate any stacks above this one
    for (int i = (m_StepStackIdx + 1); i < (int)m_Style.m_Stacks.size(); i++) {
        m_Style.m_Stacks[i].Regenerate();
    }
}

int StyleProgress::SetStep(int step)
{
    if (step <= m_Upper) {
        m_Step = step;
    }

    return m_Step;
}

void StyleProgress::SetRange(int lower, int upper)
{
    // negative range values not implemented
    ASSERT(lower >= 0 && upper > 0);

    if (upper > lower) {
        m_Upper = upper;
        m_Lower = lower;
    }
}
int StyleProgress::SetPos(int pos)
{
    if (pos <= m_Lower)    m_Pos = m_Lower;
    else if (pos >= m_Upper)    m_Pos = m_Upper;
    else                        m_Pos = pos;

    if (!m_bCreated) CreateDefaultStack();

    UpdateStack();
    Invalidate();
    return m_Pos;
}

int StyleProgress::StepIt()
{
    int newPos = m_Pos + m_Step;

    if (m_Pos == m_Upper)  m_Pos = m_Step;
    else if (newPos > m_Upper)  m_Pos = m_Upper;
    else                        m_Pos = newPos;

    if (m_bCreated) {
        UpdateStack();
        Invalidate();
    }

    return m_Pos;
}

////////////////////////////////////////
/// DEFAULT PROGRESS CONTOL STACK //////
////////////////////////////////////////
void StyleProgress::CreateDefaultStack()
{
    // define the rects
    GetClientRect(m_ProgRect);
    CRect EffRect(m_ProgRect);
    CRect TopRect(m_ProgRect);
    // some adustments
    EffRect.DeflateRect(1, 1);
    TopRect.DeflateRect(1, 1);
    //=============== Background Layers ===================//
    Stack ProgressBack(m_ProgRect, m_BackColor);
    ProgressBack.SetShape(ROUNDRECT, 1);
    ProgressBack.SetOuterBorder(1, RGB(0xB2, 0xB2, 0xB2));
    ProgressBack.SetMiddleBorder(1, Clr(100, White));
    ProgressBack.FillBar(EffRect, LEFT_EDGE, 8, Clr(40, Black), Clr(0, Black));
    ProgressBack.FillBar(EffRect, RIGHT_EDGE, 8, Clr(0, Black), Clr(40, Black));
    float btprof[3] = { 0.0f, 0.20f, 1.0f };
    ProgressBack.FillBar(EffRect, TOP_EDGE, 6, Clr(200, White), Clr(241, White), Clr(40, White), btprof);
    float bbprof[3] = { 0.0f, 0.80f, 1.0f };
    ProgressBack.FillBar(EffRect, BOTTOM_EDGE, 6, Clr(0, White), Clr(100, White), Clr(80, White), bbprof);
    //=========== Foreground Layers ======================//
    Stack ProgressFront(TopRect);
    ProgressFront.FillSolid(TopRect, m_ForeColor);
    // top and bottom
    float tprof[3] = { 0.0f, 0.15f, 1.0f };
    ProgressFront.FillBar(TopRect, TOP_EDGE, 6, Clr(180, White), Clr(200, White), Clr(128, White), tprof);
    ProgressFront.FillBar(TopRect, BOTTOM_EDGE, 6, Clr(0, White), Clr(100, White));
    float lprof[3] = { 0.0f, 0.15f, 1.0f };
    float rprof[3] = { 0.0f, 0.85f, 1.0f };
    ProgressFront.FillBar(TopRect, LEFT_EDGE, 20, Clr(20, Black), Clr(40, Black), Clr(0, Black), lprof);
    ProgressFront.FillBar(TopRect, RIGHT_EDGE, 20, Clr(0, Black), Clr(40, Black), Clr(20, Black), rprof);
    // add it to the style
    AddStack(ProgressBack);
    AddStepStack(ProgressFront);
}
