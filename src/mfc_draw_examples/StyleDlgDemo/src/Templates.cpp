#include "stdafx.h"
#include "Templates.h"

/////////////////////////////////////////
///////// VISTA BUTTON STYLE 1 //////////
/////////////////////////////////////////
VistaButton1::VistaButton1(CRect rect)
{
    // define some colors
    COLORREF ButtonOuterBorder  = RGB(0x75, 0x7D, 0x95);
    COLORREF ButtonBorder       = RGB(0x03, 0x07, 0x0D);
    COLORREF ButtonInnerBorder  = RGB(0xBF, 0xC4, 0xCE);
    COLORREF GlowColor          = RGB(0x30, 0x73, 0xCE);;
    COLORREF CheckedGlow        = RGB(0x57, 0xC6, 0xEF);
    COLORREF GlossyEffectNorth  = RGB(0x68, 0x7C, 0xAC);
    COLORREF GlossyEffectSouth  = RGB(0xAA, 0xB5, 0xD0);
    COLORREF CheckedButtonFill  = RGB(0x18, 0x38, 0x9E);
    // some temporary stacks
    Stack VB1Base, VB1Base2, VB1Hover, VB1Pressed, VB1Glow;
    Stack VB1Checked, VB1CheckedGlow;
    // the main rect
    CRect vrect(rect), nrect(rect);
    nrect.bottom = rect.top + rect.Height() / 2;
    // define the glow rect
    CRect glr(rect);
    glr.InflateRect(90, 10);
    glr.OffsetRect(0, vrect.Height() / 2);
    //--------------------- Create Face Layers ----------------------//
    // create the Face
    VB1Base.SetRect(vrect);
    VB1Base.FillSolid(Black);
    // set the OuterBorder size and color
    VB1Base.SetOuterBorder(1, ButtonOuterBorder);
    // set the radius
    VB1Base.SetShape(ROUNDRECT, 2);
    // another layer for glossy effect
    // GDI+ creates an artifact here, so use the alternate method below
    //VB1Base.FillGrad2(nrect, VERT, GlossyEffectNorth, Clr(85,GlossyEffectSouth));
    float profile[3] = { 0.0f, 0.99f, 1.0f };
    VB1Base.FillBar(TOP_EDGE, vrect.Height() / 2, GlossyEffectNorth,
                    Clr(85, GlossyEffectSouth), Clr(85, GlossyEffectSouth), profile);
    //--------------------- Create Face2 Layers ----------------------//
    VB1Base2 = VB1Base;
    VB1Base2.SetShape(ROUNDRECT, 2);
    // set the MiddleBorder size and color
    VB1Base2.SetMiddleBorder(1, ButtonBorder);
    // set the InnerBorder size and color
    VB1Base2.SetInnerBorder(1, ButtonInnerBorder);
    //--------------------- Hover Layer ----------------------//
    VB1Hover.SetRect(vrect);
    VB1Hover.FillBar(vrect, TOP_EDGE, vrect.Height() / 2, Clr(60, ButtonInnerBorder),
                     Clr(20, ButtonInnerBorder));
    //-------------------- Pressed Layer ---------------------//
    VB1Pressed.SetRect(vrect);
    VB1Pressed.FillBar(vrect, TOP_EDGE, vrect.Height() / 2, Clr(150, Black), Clr(100, Black));
    //--------------------- Glow Layer ----------------------//
    VB1Glow.SetRect(vrect);
    VB1Glow.FillRadial(glr, GlowColor);
    //--------------------- Checked Layer ----------------------//
    VB1Checked.SetRect(vrect);
    VB1Checked.FillSolid(CheckedButtonFill);
    VB1Checked.FillBar(vrect, TOP_EDGE, vrect.Height() / 2, GlossyEffectNorth,
                       Clr(85, GlossyEffectSouth));
    //--------------------- Checked Glow Layer -----------------//
    VB1CheckedGlow.SetRect(vrect);
    VB1CheckedGlow.FillRadial(glr, CheckedGlow);
    //==========================================================//
    //              Create the final groups                     //
    //==========================================================//
    // create standard group
    VBStd = VB1Base;
    // create the hot group
    VBHot = VB1Base2 + VB1Hover + VB1Glow;
    // create the pressed group
    VBPress = VB1Base2 + VB1Pressed + VB1Glow;
    // create the alt group
    VBAlt = VB1Base2 + VB1Checked + VB1Hover + VB1CheckedGlow;
}

/////////////////////////////////////////
///////// VISTA BUTTON STYLE 2 //////////
/////////////////////////////////////////
VistaButton2::VistaButton2(CRect rect, Clr color)
{
    // some temporary stacks
    Stack VB2Base, VB2Glow;
    // the main rect
    CRect vrect(rect), nrect;
    // define the glow rect
    CRect glr(rect);
    glr.InflateRect(60, 10);
    glr.OffsetRect(0, vrect.Height() / 2);
    //--------------------- Create Face Stack ----------------------//
    // create the Face
    VB2Base.SetRect(vrect);
    VB2Base.FillSolid(color);
    UINT32 gclr = color.value.GetValue();
    gclr |= 0xff000000;
    // set the OuterBorder size and color
    VB2Base.SetOuterBorder(1, gclr);
    VB2Base.SetMiddleBorder(1, White);
    // set the radius
    VB2Base.SetShape(ROUNDRECT, 2);
    //--------------------- Glow Layer ----------------------//
    VB2Glow.SetRect(vrect);
    VB2Glow.FillRadial(glr, gclr);
    //==========================================================//
    //              Create the final Groups                     //
    //==========================================================//
    // create standard stack
    VBStd = VB2Base;
    // create the hot stack
    VBHot = VB2Base + VB2Glow;
    // create the pressed stack
//  VBPress = VB2Base2 + VB2Pressed + VB2Glow;
}


/////////////////////////////////////////
///////// AQUA BUTTON STYLE /////////////
/////////////////////////////////////////
AquaButton::AquaButton(CRect rect, Clr face, Clr hot, Clr outerstroke, CString str, int size)
{
    // some temporary stacks
    Stack Base, StdFill, HotFill, Face, Dome;
    Rect r = SRect(rect).rect;
    // all the following paramaters assume the origin
    ASSERT(r.X == 0 && r.Y == 0);
    int width = r.Width;
    int height = r.Height;
    int margin = 2;
    int buttonwidth = width - (margin * 2);
    int buttonheight = height - (margin * 2);
    int borderwidth = min(width, height) / 20;
    int buttoncolorx = margin + borderwidth;
    int buttoncolory = margin + borderwidth;
    int buttoncolorwidth = buttonwidth - borderwidth * 2 - 1;
    int buttoncolorheight = buttonheight - borderwidth * 2 - 1;
    int highlightx = width / 4;
    int highlighty = borderwidth + (height - 2 * borderwidth) / 8;
    int highlightwidth = width / 2;
    int highlightheight = (height - 2 * borderwidth) * 3 / 8 - highlighty;
    Clr bordercolor(RGB(143, 190, 232));
    Base.SetRect(r);
    Base.SetShape(ELLIPSE);
    Base.SetOuterBorder(1, outerstroke);
    // create a rect for the radial fill
    Rect radrect = r;
    int side = radrect.Width;
    radrect.X -= side;
    radrect.Y -= side;
    radrect.Width *= 2;
    radrect.Height *= 2;
    radrect.Offset(side / 4, side / 4);
    Base.FillRadial(radrect, bordercolor, Black);
    // create the button fill color
    Rect btn(buttoncolorx, buttoncolory, buttoncolorwidth, buttoncolorheight);
    StdFill.SetRect(r);
    StdFill.SetShape(ELLIPSE);
    StdFill.FillSolid(btn, face);
    HotFill.SetRect(r);
    HotFill.SetShape(ELLIPSE);
    HotFill.FillSolid(btn, hot);
    Face.SetRect(r);
    Face.SetShape(ELLIPSE);
    // add the text
    Face.AddAlignString(str, ALIGN_CENTER, CPoint(0, 0), 0, Blue, size);
    // create a region slightly larger than the button face
    Rect zbtn = btn;
    zbtn.Inflate(2, 2);
    int zbutton = Face.CreateRgn(zbtn, ELLIPSE);
    // define not left sickle
    Rect shiftx = zbtn;
    shiftx.Offset(8, 0);
    int notLeftSickle = Face.CreateRgn(shiftx, ELLIPSE);
    // create the left sickle
    int LeftSickle = Face.CombineRgnCreate(zbutton, notLeftSickle, EXCLUDE);
    // define not top sickle
    Rect shifty = zbtn;
    shifty.Offset(0, 20);
    int notTopSickle = Face.CreateRgn(shifty, ELLIPSE);
    // create the top sickle
    int TopSickle = Face.CombineRgnCreate(zbutton, notTopSickle, EXCLUDE);
    // create region equal to the button
    int button = Face.CreateRgn(btn, ELLIPSE);
    // blur into button but not border
    Face.ApplyClipRgn(button);
    Face.FillBlur(LeftSickle, Clr(64, Black), 10);
    Face.FillBlur(TopSickle, Clr(64, Black), 20);
    Face.RestoreClipRgn();
    // highlight rect
    Rect hlt(highlightx, highlighty, highlightwidth, highlightheight);
    Dome.SetRect(r);
    Dome.SetShape(ELLIPSE);
    // add the highlight
    Dome.FillGrad2(hlt, VERT, Clr(210, White), Clr(0, White));
    StdStack = Base + StdFill + Face + Dome;
    // this is the standard button style
    Std.AddStack(Base + StdFill + Face + Dome);
    // the hot style
    Hot.AddStack(Base + HotFill + Face + Dome);
    // the pressed style
    Press.AddStack(Base + StdFill + Face);
}


/////////////////////////////////////////
///////// RAISED FRAME STACK ////////////
/////////////////////////////////////////
RaisedFrame::RaisedFrame(CRect rect, Clr border, Clr highlight, int bwidth)
{
    RFrame.SetRect(rect);
    int outer = RFrame.CreateRgn(rect);
    CRect irect =  rect;
    irect.DeflateRect(bwidth, bwidth);
    int inner = RFrame.CreateRgn(irect);
    RFrame.CombineRgnModify(outer, inner, EXCLUDE);
    RFrame.ApplyClipRgn(outer);
    RFrame.FillSolid(border);
    RFrame.RestoreClipRgn();
    Clr tledge = Clr(40,  highlight.GetRGB());
    Clr peak = Clr(200, highlight.GetRGB());
    Clr bredge = Clr(60, Black);
    float tlprofile[3] = { 0.0f, 0.55f, 1.0f };
    RFrame.FillBar(rect, TOP_EDGE_BEVEL,  bwidth, tledge, peak, CLEAR, tlprofile);
    RFrame.FillBar(rect, LEFT_EDGE_BEVEL, bwidth, tledge, peak, CLEAR, tlprofile);
    float brprofile[3] = { 0.0f, 0.4f, 1.0f };
    RFrame.FillBar(rect, BOTTOM_EDGE_BEVEL, bwidth, CLEAR, peak, bredge, brprofile);
    RFrame.FillBar(rect, RIGHT_EDGE_BEVEL,  bwidth, CLEAR, peak, bredge, brprofile);
}


/////////////////////////////////////////
///////// RAISED DIALOG FRAME ///////////
/////////////////////////////////////////
RaisedDlgFrame::RaisedDlgFrame(CRect drect, CRect crect, Clr border, Clr highlight, int bwidth)
{
    // set the main stack
    DlgFrame.SetRect(drect);
    // Disable smothing mode
    DlgFrame.SetSmoothing(NONE);
    // dlg frame
    int outer = DlgFrame.CreateRgn(drect);
    // inner frame
    CRect irect = drect;
    irect.DeflateRect(bwidth, bwidth);
    int inner = DlgFrame.CreateRgn(irect);
    // cut the client area
    DlgFrame.CombineRgnModify(outer, inner, EXCLUDE);
    // fill the frame region
    DlgFrame.ApplyClipRgn(outer);
    DlgFrame.FillSolid(border);
    DlgFrame.RestoreClipRgn();
    Clr tledge = Clr(40,  highlight.GetRGB());
    Clr peak = Clr(200, highlight.GetRGB());
    Clr bredge = Clr(60, Black);
    float tlprofile[3] = { 0.0f, 0.55f, 1.0f };
    DlgFrame.FillBar(drect, TOP_EDGE_BEVEL,  bwidth, tledge, peak, CLEAR, tlprofile);
    DlgFrame.FillBar(drect, LEFT_EDGE_BEVEL, bwidth, tledge, peak, CLEAR, tlprofile);
    float brprofile[3] = { 0.0f, 0.4f, 1.0f };
    DlgFrame.FillBar(drect, BOTTOM_EDGE_BEVEL, bwidth, CLEAR, peak, bredge, brprofile);
    DlgFrame.FillBar(drect, RIGHT_EDGE_BEVEL,  bwidth, CLEAR, peak, bredge, brprofile);
    int hwidth = bwidth / 2 + 1;
    CRect upper = drect;
    upper.top = crect.top - bwidth;
    upper.bottom = upper.top + hwidth;
    upper.left += (hwidth - 1);
    upper.right -= (hwidth - 1);
    // upper part of crossbar
    DlgFrame.FillBar(upper, BOTTOM_EDGE_BEVEL, hwidth, border, border);
    DlgFrame.FillBar(upper, BOTTOM_EDGE_BEVEL, hwidth, tledge, peak);
    CRect lower = upper;
    lower.OffsetRect(0, hwidth - 1);
    lower.left++;
    lower.right--;
    // lower part of crossbar
    DlgFrame.FillBar(lower, TOP_EDGE_BEVEL, hwidth, border, border);
    DlgFrame.FillBar(lower, TOP_EDGE_BEVEL, hwidth, peak, bredge);
    // since the peak overlaps, it needs to be repainted
    lower.bottom = lower.top + 1;
    Color b1 = border.Blend(peak.value);
    DlgFrame.FillSolid(lower, b1);
    // Restore smothing mode
    DlgFrame.RestoreSmoothing();
}
