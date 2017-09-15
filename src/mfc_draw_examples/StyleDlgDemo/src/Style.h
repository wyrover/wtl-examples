//
// Style.h: header file for the Style class and Stack classes.
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

#pragma once

#include "Layers.h"

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^//
//      Stack - API for class Layers
//==========================================================================================//
class Stack : public Layers
{
public:
    Stack() {};
    ~Stack(void) {};

    // constructors
    Stack(SRect rect);
    Stack(SRect rect, Clr clr);

    // operators
    Stack& operator=(const Stack& other);
    Stack& operator+=(const Stack& other);
    friend Stack operator+(const Stack& lhs, const Stack& rhs);

    int  AddLayer();
    int  AddLayer(SRect sr, Clr clr);

    void    SetRect(SRect rect);
    void    SetPosition(int x, int y);
    void    SetShape(int shape, int xradius = 0);

    void    Regenerate(int layerIdx = -1);

    void    SetOuterBorder(int width, Clr clr);
    void    SetOuterBorder(int width, Clr clr, Clr brClr);

    void    SetMiddleBorder(int width, Clr clr);
    void    SetMiddleBorder(int width, Clr clr, Clr brClr);

    void    SetInnerBorder(int width, Clr clr);
    void    SetInnerBorder(int width, Clr clr, Clr brClr);

    int     FillSolid(Clr clr);
    int     FillSolid(SRect sr, Clr clr);

    int     FillRadial(Clr clr1, Clr clr2 = Clr(0, RGB(0, 0, 0)));
    int     FillRadial(SRect sr, Clr clr1, Clr clr2 = Clr(0, RGB(0, 0, 0)));

    int     FillGrad2(int style, Clr clr1, Clr clr2, float diffpt = 0.0);
    int     FillGrad2(SRect sr, int style, Clr clr1, Clr clr2, float diffpt = 0.0);

    int     FillGrad3(int style, Clr clr1, Clr clr2, Clr clr3, float diffpt = 0.5);
    int     FillGrad3(SRect sr, int style, Clr clr1, Clr clr2, Clr clr3, float diffpt = 0.5);

    int     FillBar(int type, int width, Clr tlclr, Clr brclr);
    int     FillBar(SRect sr, int type, int width, Clr tlclr, Clr brclr);

    int     FillBar(int type, int width, Clr clr1, Clr clr2, Clr clr3, float *profile);
    int     FillBar(SRect sr, int type, int width, Clr clr1, Clr clr2, Clr clr3, float *profile);

    int     FillWrap(int type, int width, Clr clr1, Clr clr2, Clr clr3);
    int     FillWrap(SRect sr, int type, int width, Clr clr1, Clr clr2, Clr clr3);

    int     FillBlur(int region, Clr clr, int amount);

    int     AddImage(SPoint dest, UINT id, LPCTSTR type, BOOL clip = FALSE,
                     int xform = NOXFORM);

    int     AddImage(SPoint dest, SPoint src, UINT id, LPCTSTR type,
                     BOOL clip = FALSE, int xform = NOXFORM);

    int     AddString(CString str, SPoint offset, Clr clr, int size = 12,
                      int style = FONT_REG, WCHAR* name = L"Tahoma");

    int     AddAlignString(CString str, int alignment, SPoint offset, Clr clr, int size = 12,
                           int style = FONT_REG, WCHAR* name = L"Tahoma");

    int     AddAlignString(SRect sr, CString str, int alignment, SPoint offset, Clr clr,
                           int size = 12, int style = FONT_REG, WCHAR* name = L"Tahoma");

    int     AddEffectString(CString str, SPoint offset, int effect,
                            int size, int style, WCHAR* name, Clr clr1, Clr clr2,
                            int width1, Clr clr3 = Clr(0, RGB(0, 0, 0)), int width3 = 0);

    int     AddEffectString(SRect sr, CString str, SPoint offset, int effect,
                            int size, int style, WCHAR* name, Clr clr1, Clr clr2,
                            int width1, Clr clr3 = Clr(0, RGB(0, 0, 0)), int width3 = 0);

    int     CreateRgn(SRect sr, int shape = RECTANGLE);

    int     CombineRgnModify(int resultRgn, int combineRgn, int mode);

    int     CombineRgnCreate(int rgn1, int rgn2, int mode);

    int     RestoreClipRgn();

    int     ApplyClipRgn(int region);

    int     SetSmoothing(int mode);

    int     RestoreSmoothing();

    int     ApplyTransform(int xform);

};


class Style
{

public:
    Style();
    virtual ~Style();

public:

    int     AddStack(Stack& stack);

    void    PaintStyle(CDC* pDC, CRect rect);

    void    SetPosition(int x, int y);
    void    Regenerate();

    int     GetTopIndex();

    vector<Stack>           m_Stacks;
    vector<Stack>::iterator stack;
};
