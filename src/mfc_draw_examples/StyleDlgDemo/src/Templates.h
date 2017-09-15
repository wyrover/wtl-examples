#pragma once

#include "Style.h"

// this button style comes from Jose Manuel Menéndez Poó's Article
// http://www.codeproject.com/KB/vista/WindowsVistaRenderer.aspx
// this is not an exact reproduction, but fairly close
class VistaButton1
{
public:

    VistaButton1(CRect rect);
    ~VistaButton1(void) {};

    Stack VBStd;
    Stack VBHot;
    Stack VBPress;
    Stack VBAlt;

};

class VistaButton2
{
public:

    VistaButton2(CRect rect, Clr color);
    ~VistaButton2(void) {};

    Stack VBStd;
    Stack VBHot;
    Stack VBPress;
    Stack VBAlt;
};


class AquaButton
{
public:

    AquaButton(CRect rect, Clr base, Clr hot, Clr outerstroke, CString str, int size = 16);
    ~AquaButton(void) {};

    Style Std;
    Stack StdStack;
    Style Hot;
    Style Press;
};

class RaisedFrame
{
public:

    RaisedFrame(CRect rect, Clr base, Clr border, int width);
    ~RaisedFrame(void) {};

    Stack RFrame;
};


class RaisedDlgFrame
{
public:

    RaisedDlgFrame(CRect drect, CRect crect, Clr base, Clr border, int width);
    ~RaisedDlgFrame(void) {};

    Stack DlgFrame;
};
