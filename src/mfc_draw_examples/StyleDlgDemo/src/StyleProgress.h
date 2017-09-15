//
// StyleProgress.h : Version 1.0 - see article at CodeProject.com
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

#pragma once

#include "style.h"

class StyleProgress : public CProgressCtrl
{

public:
    StyleProgress(void);
    ~StyleProgress(void);

    // for custom bar
    void AddStack(Stack stack);
    void AddStepStack(Stack stack);
    void SetStepLayer(int layerIdx);

    // for default bar
    void SetBackColor(COLORREF color, int Alpha = 255);
    void SetForeColor(COLORREF color, int Alpha = 255);

    COLORREF    m_ForeColor;
    COLORREF    m_BackColor;
    int         m_ForeAlpha;
    int         m_BackAlpha;

    int     StepIt();
    int     SetPos(int pos);
    int     SetStep(int step);
    void    SetRange(int lower, int upper);

    void    CreateDefaultStack();

    Style       m_Style;
protected:
    DECLARE_MESSAGE_MAP()
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnPaint();
    afx_msg void OnNcPaint();

    void    UpdateStack();

private:

    int         m_Pos;
    int         m_Step;
    int         m_Upper;
    int         m_Lower;

    CRect       m_ProgRect;
    BOOL        m_bCreated;

    int         m_StepStackIdx;
    int         m_StepLayerIdx;
    int         m_StepLayerWidth;
};
