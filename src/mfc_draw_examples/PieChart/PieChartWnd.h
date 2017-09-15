#pragma once
#include <gdiplus.h>
#include <map>
#include <vector>
using namespace Gdiplus;
using namespace std;
// CPieChartWnd


struct pie_chart_element;
typedef pie_chart_element* PIECHARTITEM;

class CPieChartWnd : public CWnd
{
    DECLARE_DYNAMIC(CPieChartWnd)

public:
    CPieChartWnd();
    virtual ~CPieChartWnd();

protected:

    //+ Added to the previous
    enum pie_drawn_direction {      //Use to represent the drawing direction and position parameters for 3-D pir chart
        RIGHT_ANGLED,
        LEFT_ANGELD,
        PIE_LAST,
        PIE_FRONT,
        PIE_FRONT_RIGHT,
        PIE_FRONT_LEFT,
        PIE_LAST_RIGHT,
        PIE_LAST_LEFT,

    };

    //The structure used to hold the data elements used in 3-D style drawing
    struct pie_3d_properties {
        float f_InclineAngle;   //The transformed angle for 3-D pie chart
        BYTE i_alphaVal;        //+ The alpha value to set transparency
        PointF pt_Start;        //+ The start location point
        PointF pt_End;          //The end location point for a single element on upper face of pie
    };
private:
    //The basic data structure which holds the pie chart item data
    struct pie_chart_element {
        double d_value;
        float f_percentage;
        float f_angle;
        float f_ColorGradL;
        float f_ColorGradD;
        Color cr_GradientL;
        Color cr_GradientD;
        Color cr_Base;
        CString s_label;
        CString s_element;
        pie_3d_properties pie_3d_props;
        int i_ID;
        BOOL b_select;
        int i_distIndex;        //+ represent the distance from the center of the pie

    };
//The color lable properties, these are relatively resized.
    struct label_size {
        int wdth;
        int hght;
        int xGapLeft;
        int xGapRight;
        int yGap;
        CString sFont;
        INT fStyle;
        int fSize;
    };
    //The rectangle area which shows the % values of each pie item
    struct  label_rect_info {
        int lbRctHght;
        int lbIndex;
        int lbVisibleRectHght;
        Color lbTextColor;
        Color lbValueRectColor;
    };
//Background parameters
    struct background_params {
        Color cr_backgrnd;
        Color cr_GradientL;
        Color cr_GradientD;
        float f_ColorGradL;
        float f_ColorGradD;
        CString s_ChartTittle;
        CString sFont;
        INT fStyle;
        int i_HorizontalOffset;

    };
//Three pie chart styles
public:
    enum pie_chart_style {
        DoughnutStyle,
        TwoDStyle,
        ThreeDStyle,
    };

private:

    CScrollBar m_VscrollBar;
    int i_elementIndex; //The index value used in inserting elements
    float fl_startAngle;    //Starting angle for the pie elements
    float fl_startAngleIncline; //Transformed starting angle for 3-D pie
    float fl_InclineAngle;  //The inclination angle for 3-D pie
    float f_depth;      //The height for the 3-D pie
    double d_totalVal; //total value of all  pie items
    COLORREF cr_parentClr;  //Set this color to paint the outline of the window in the same color of parent
    label_size lb_param;
    label_rect_info lb_info;
    background_params bkg_params;
    int i_pieElement_front;     //key of the front drawn element
    int i_pieElement_last;      //key of the last drawn element

    Color cr_HighlightColor;
    CString s_saveImage;    //The image path to save the pie chart
    BOOL b_SaveFlag;    //Save flag set in to save the image
    BOOL b_ShowPercentages;
    map<int, pie_chart_element*> map_pChart;    //The map holds the pie elements
    ULONG_PTR m_gdiplusToken;
    pie_chart_style pie_ChartStyle;
    CRect pie_RectOverride;
    CRect pie_LabelRectOverride;

protected:
    DECLARE_MESSAGE_MAP()

private: //internal functions//
    //Drawing functions for 3 different styles
    void Draw2DStyle(CDC* pDc);
    void DrawDoughnutStyle(CDC* pDc);
    void Draw3DStyle(CDC* pDc);

    void DrawLabels(Graphics* graphics);    //Draw the color and % value labels
    int GetVerticalScrollPos(int iScrollPos, BOOL bDrag);   //Used to pre calculate the vertical position for the scroller
    void UpdatePieChart(void);  //Update the pie items percentages
    Color CalculateGradientLight(Color crBase, float fGrad);    //function to calculate the gradient light color for a given color, gradient value
    Color CalculateGradientDark(Color crBase, float fGrad);     //function to calculate the gradient dark color for a given color, gradient value
    void GetBoundRect(LPRECT rect, bool pieRect = false);   //The rectangle are of the pie chart alone
    void ResetItemScrollBar(void);  //Reset the scrollbar range and positions
    void CalculateLabelRect(void);  //Pre calculate the rectangle area of the % labels
    void DrawPiechartPecentages(Graphics* pGraphics, float flStartAngle);   //Drawing function for the % values on pie chart
    BOOL ReArrangeElementMap(void); //Function used to rearrange the element map in removing items.
    void DrawBackGround(Graphics* pGraphics);   //Drawing function for the background area
    void Get3DBounds(LPRECT rectTop, LPRECT rectBtm);   //Get the two bounding areas for 3-D style draw
    void CalcuatePieElemetPoints(void); //Calculate the lying angle intersections of pie elements on the pie
    void UpdatePiechartPoints(void);    //Update the pie element points in 3-D draw for starting angle and inclination changes.
    float CacluateInclineAngle(PointF ptElement, CRect rectTop);
    BOOL HasElement(CString sElement);  //Check the element exist by its element name ID
    BOOL SaveImageInternal(Bitmap* btImage);
    int SetSelectedPieElement(CPoint point);    //Find the element which lies on the clicked area

    //+ These functions used to draw the 3-D surfaces

    BOOL ConstructRectangularFace(Graphics* pGraphics, pie_chart_element pElement, PointF ptTopCenter, PointF ptClicked); //Sub 3-D face drawing function
    BOOL ConstructArcFace(Graphics* pGraphics, pie_chart_element* pElement, REAL flStart, RectF rect,  PointF ptClicked);   //Sub 3-D face drawing function
    BOOL ConstructSideFace(Graphics* pGraphics, pie_chart_element pElement, REAL flDisplace,                                            //Sub 3-D face drawing function
                           REAL flStart, PointF ptClicked);

    BOOL Construct3DElement(Graphics* pGraphics, pie_chart_element* pElement,   //The mainfunction to draw the 3-D shape elements
                            REAL flStart, pie_drawn_direction drawCase, PointF ptClicked);
    BOOL Construct3DElementSpecific(Graphics* pGraphics, pie_chart_element* pElement,   //Draw special cases of 3-D elements when the front element = last element
                                    REAL flStart, pie_drawn_direction drawCase, PointF ptClicked);

    //+ Function to find the 3-D element clicked
    BOOL FindClicked3DElement(PointF ptClicked);
    //+ Function to reset the Label properties & scrollbar
    void ResetLabelProperties();

public: //External functions//
    //Insert item function
    PIECHARTITEM InsertItem(CString sElement, CString sLabel, double dValue, Color crColor);
    //Remove item functions
    BOOL RemoveItem(CString sElement);
    BOOL RemoveItem(int iElementID);
    BOOL RemoveItem(PIECHARTITEM pItem);
    BOOL RemoveItemAll();
    //Item update functions
    BOOL UpdateItemLabel(PIECHARTITEM pItem, CString sLabel);
    BOOL UpdateItemValue(PIECHARTITEM pItem, double dVal);
    BOOL UpdateItemColor(PIECHARTITEM pItem, Color crItem);

    //Font set functions
    void SetLabelFont(LOGFONT lf);
    void SetTitleFont(LOGFONT sFontName);
    void SetLabelFontSizeOverride(int fSize);

    //Color set functions
    void SetLabelBoxColor(Color crTextColor);
    void SetBackgrndColor(Color crBkgColor);
    void SetLabelColor(Color crLbColor);
    void SetItemHighlightColor(Color crHighlightColor);
    //Use to set the window outline color to the same as parent
    void SetParentWindowColor(COLORREF crParent);
    //Gradient set functions
    BOOL SetPieElementGradientLight(PIECHARTITEM pItem, float flGradientVal);
    BOOL SetPieElementGradientDark(PIECHARTITEM pItem, float flGradientVal);
    BOOL SetBackGroundGradientLight(float flGradientVal);
    BOOL SetBackGroundGradientDark(float flGradientVal);
    BOOL SetPieElementGradientDarkAll(float flGradientVal);
    BOOL SetPieElementGradientLightAll(float flGradientVal);

    void SetPieChartTitle(CString sTittle);
    void SetPieChartStyle(pie_chart_style pChartStyle);
    void SetPieChartRectOverride(CRect rectPie);
    void SetLabalRectOverride(CRect rectLabel);
    void SetStartAngle(float flAngle);
    void SetInclineAngle(float flAngle);
    BOOL SetDepth(float fDepth);

    //+ functions to set distance and transparency
    BOOL SetDistanceIndex(PIECHARTITEM pItem, int iDistIndex);
    BOOL SetDistanceIndexAll(int iDistIndex);
    BOOL SetElementTransparency(PIECHARTITEM pItem, float flPercentage);
    BOOL SetElementTransparencyAll(float flPercentage);
    BOOL SetHorizontalOffset(int iHrzOffset);

    //Element arranging functions
    void sortPiechartElements(BOOL bClockWise);
    void SortToOrginalOrder(void);

    BOOL SaveImage(CString sPath);
    virtual BOOL Create(LPCTSTR lpCaption, const RECT& rect, CWnd* pParentWnd, UINT nID);

    //Disable or enable % vaules to be printed on top of pie
    void ShowPercentagesOnPie(BOOL bShow);

    //Getter functions
    PIECHARTITEM GetSelectedElement(void);
    PIECHARTITEM GetPieChartItem(CString sElement);
    int GetElementID(CString sElement);
    float GetBackGroungGrLight(void);
    float GetBackgroundGrDark(void);
    float GetElementGrLight(PIECHARTITEM pItem);
    float GetElementGrDark(PIECHARTITEM pItem);
    CString GetElementName(PIECHARTITEM pItem);

private:
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnPaint();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


