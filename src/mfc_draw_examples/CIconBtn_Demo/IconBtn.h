#pragma once


// CIconBtn

class CIconBtn : public CButton
{
    DECLARE_DYNAMIC(CIconBtn)

public:
    CIconBtn();
    virtual ~CIconBtn();
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    virtual void PreSubclassWindow();
    virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);

    enum {
        IBTN_ICON_LEFT_TEXT_RIGHT = 0,  // Left:Icon   Right:Text
        IBTN_ICON_RIGHT_TEXT_LEFT,      // Right:Icon  Left:Text
        IBTN_ICON_TOP_TEXT_BOTTOM,      // Top:Icon    Bottom:Text
        IBTN_ICON_BOTTOM_TEXT_TOP       // Bottom:Icon Top:Text
    };

protected:
    void DrawBackground();
    void DrawBorder();
    void Draw3DBorderForRect(CDC *pDC, CRect *pRect);
    void DrawFocusRect();
    void DrawIcon();
    void DrawText();
    void PrepareDrawIconAndText();

public:
    BOOL SetIcon(int nIcon, int nCxDesired = 0, int nCyDesired = 0);
    BOOL SetAlign(BYTE byAlign);

private:
    BYTE  m_byAlign;            // text与icon的对齐方式
    CDC*  m_pDC;                // dc handle pointer
    CRect m_rcBtn;              // 按钮rect
    bool  m_bIsFocused;         // 按钮是否获得焦点
    bool  m_bIsPressed;         // 按钮是否被按下
    bool  m_bIsDisabled;        // 按钮是否Disable

    HICON m_hIcon;              // Icon handle
    int   m_nIconWidth;         // Icon width
    int   m_nIconHeight;        // Icon height

    int   m_nFocusRectOffset;   // 焦点矩形的偏移量
    int   m_nCxIconStart;       // Draw icon的起始点x坐标
    int   m_nCyIconStart;       // Draw icon的起始点y坐标
    RECT  m_rcText;             // Draw text的矩形区域

protected:
    DECLARE_MESSAGE_MAP()
};


