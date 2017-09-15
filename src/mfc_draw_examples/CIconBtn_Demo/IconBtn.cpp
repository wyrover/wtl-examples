// IconBtn.cpp : implementation file
//

#include "stdafx.h"
#include "CIconBtn_Demo.h"
#include "IconBtn.h"


// CIconBtn

IMPLEMENT_DYNAMIC(CIconBtn, CButton)

CIconBtn::CIconBtn()
    : m_hIcon(NULL), m_nIconWidth(0), m_nIconHeight(0), m_nFocusRectOffset(4),
      m_nCxIconStart(0), m_nCyIconStart(0), m_rcBtn(0, 0, 0, 0),
      m_bIsFocused(false), m_bIsPressed(false), m_bIsDisabled(false),
      m_byAlign(IBTN_ICON_LEFT_TEXT_RIGHT)
{
    m_rcText.left = 0;
    m_rcText.top = 0;
    m_rcText.right = 0;
    m_rcText.bottom = 0;
}

CIconBtn::~CIconBtn()
{
    if (m_hIcon)
        ::DestroyIcon(m_hIcon);
}


BEGIN_MESSAGE_MAP(CIconBtn, CButton)
END_MESSAGE_MAP()

BOOL CIconBtn::PreTranslateMessage(MSG* pMsg)
{
    // TODO: Add your specialized code here and/or call the base class
    if (pMsg->message == WM_LBUTTONDBLCLK)
        pMsg->message = WM_LBUTTONDOWN;

    return CButton::PreTranslateMessage(pMsg);
}

void CIconBtn::PreSubclassWindow()
{
    // TODO: Add your specialized code here and/or call the base class
    ModifyStyle(BS_TYPEMASK, BS_OWNERDRAW, SWP_FRAMECHANGED);
    CButton::PreSubclassWindow();
}

void CIconBtn::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    // 获取DC及按钮大小
    m_pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
    m_pDC->SetBkMode(TRANSPARENT);
    m_rcBtn = lpDrawItemStruct->rcItem;
    // 监测按钮状态
    m_bIsFocused  = lpDrawItemStruct->itemState & ODS_FOCUS;
    m_bIsPressed  = lpDrawItemStruct->itemState & ODS_SELECTED;
    m_bIsDisabled = lpDrawItemStruct->itemState & ODS_DISABLED;
    // Draw background
    this->DrawBackground();
    // Draw border
    this->DrawBorder();
    // Draw focus rect
    this->DrawFocusRect();
    // 计算Draw icon的位置及Draw text的矩形
    this->PrepareDrawIconAndText();

    // Draw icon
    if (m_hIcon)
        this->DrawIcon();

    // Draw text
    CString strText;
    GetWindowText(strText);

    if (!strText.IsEmpty())
        this->DrawText();
}

//
// Draw background
//
void CIconBtn::DrawBackground()
{
    CBrush brushBk(::GetSysColor(COLOR_BTNFACE));

    if (m_bIsFocused) {
        m_rcBtn.DeflateRect(1, 1);
        m_pDC->FillRect(&m_rcBtn, &brushBk);
        m_rcBtn.DeflateRect(-1, -1);
        CBrush brushFrame(RGB(0, 0, 0));
        m_pDC->FrameRect(&m_rcBtn, &brushFrame);
    } else {
        m_pDC->FillRect(&m_rcBtn, &brushBk);
    }
}

//
// Draw border
//
void CIconBtn::DrawBorder()
{
    if (m_bIsPressed) {
        m_rcBtn.DeflateRect(1, 1);
        CBrush brBtnShadow(::GetSysColor(COLOR_BTNSHADOW));
        m_pDC->FrameRect(&m_rcBtn, &brBtnShadow);
        m_rcBtn.DeflateRect(-1, -1);
    } else if (m_bIsFocused) {
        m_rcBtn.DeflateRect(1, 1);
        this->Draw3DBorderForRect(m_pDC, &m_rcBtn);
        m_rcBtn.DeflateRect(-1, -1);
    } else {
        this->Draw3DBorderForRect(m_pDC, &m_rcBtn);
    }
}

//
// 为pRect绘制3D边框
//
void CIconBtn::Draw3DBorderForRect(CDC *pDC, CRect *pRect)
{
    CPen penBtnHiLight(PS_SOLID, 0, GetSysColor(COLOR_BTNHILIGHT)); // White
    CPen pen3DLight(PS_SOLID, 0, GetSysColor(COLOR_3DLIGHT));       // Light gray
    CPen penBtnShadow(PS_SOLID, 0, GetSysColor(COLOR_BTNSHADOW));   // Dark gray
    CPen pen3DDKShadow(PS_SOLID, 0, GetSysColor(COLOR_3DDKSHADOW)); // Black
    // Draw top-left borders
    // White line
    CPen* pOldPen = pDC->SelectObject(&penBtnHiLight);
    pDC->MoveTo(pRect->left, pRect->bottom - 1);
    pDC->LineTo(pRect->left, pRect->top);
    pDC->LineTo(pRect->right, pRect->top);
    // Light gray line
    pDC->SelectObject(pen3DLight);
    pDC->MoveTo(pRect->left + 1, pRect->bottom - 1);
    pDC->LineTo(pRect->left + 1, pRect->top + 1);
    pDC->LineTo(pRect->right, pRect->top + 1);
    // Draw bottom-right borders
    // Black line
    pDC->SelectObject(pen3DDKShadow);
    pDC->MoveTo(pRect->left, pRect->bottom - 1);
    pDC->LineTo(pRect->right - 1, pRect->bottom - 1);
    pDC->LineTo(pRect->right - 1, pRect->top - 1);
    // Dark gray line
    pDC->SelectObject(penBtnShadow);
    pDC->MoveTo(pRect->left + 1, pRect->bottom - 2);
    pDC->LineTo(pRect->right - 2, pRect->bottom - 2);
    pDC->LineTo(pRect->right - 2, pRect->top);
    //
    pDC->SelectObject(pOldPen);
}

//
// 绘制焦点矩形
//
void CIconBtn::DrawFocusRect()
{
    if (m_bIsFocused) {
        m_rcBtn.DeflateRect(m_nFocusRectOffset, m_nFocusRectOffset);
        m_pDC->DrawFocusRect(&m_rcBtn);
        m_rcBtn.DeflateRect(-m_nFocusRectOffset, -m_nFocusRectOffset);
    }
}

//
// 计算绘制icon与text的位置
//
void CIconBtn::PrepareDrawIconAndText()
{
    // 判断有无text与icon
    bool bIsHasText = false;
    bool bIsHasIcon  = false;
    CString cstrCaption;
    this->GetWindowText(cstrCaption);
    bIsHasText = !cstrCaption.IsEmpty();

    if (m_hIcon)
        bIsHasIcon = true;

    // 计算绘制icon与text的位置
    if (bIsHasText && bIsHasIcon) { //既有text又有icon
        switch (m_byAlign) {
        case IBTN_ICON_LEFT_TEXT_RIGHT: {
            m_nCxIconStart = m_rcBtn.left + m_nFocusRectOffset;
            m_nCyIconStart = m_rcBtn.top + (m_rcBtn.Height() - m_nIconHeight) / 2;
            m_rcText.left = m_rcBtn.left + m_nFocusRectOffset + m_nIconWidth;
            m_rcText.top = m_rcBtn.top + m_nFocusRectOffset;
            m_rcText.right = m_rcBtn.right - m_nFocusRectOffset;
            m_rcText.bottom = m_rcBtn.bottom - m_nFocusRectOffset;
        }
        break;

        case IBTN_ICON_RIGHT_TEXT_LEFT: {
            m_nCxIconStart = m_rcBtn.right - m_nFocusRectOffset - m_nIconWidth;
            m_nCyIconStart = m_rcBtn.top + (m_rcBtn.Height() - m_nIconHeight) / 2;
            m_rcText.left = m_rcBtn.left + m_nFocusRectOffset;
            m_rcText.top = m_rcBtn.top + m_nFocusRectOffset;
            m_rcText.right = m_rcBtn.right - m_nFocusRectOffset - m_nIconWidth;
            m_rcText.bottom = m_rcBtn.bottom - m_nFocusRectOffset;
        }
        break;

        case IBTN_ICON_TOP_TEXT_BOTTOM: {
            m_nCxIconStart = m_rcBtn.left + (m_rcBtn.Width() - m_nIconWidth) / 2;
            m_nCyIconStart = m_rcBtn.top + m_nFocusRectOffset;
            m_rcText.left = m_rcBtn.left + m_nFocusRectOffset;
            m_rcText.top = m_rcBtn.top + m_nFocusRectOffset + m_nIconHeight;
            m_rcText.right = m_rcBtn.right - m_nFocusRectOffset;
            m_rcText.bottom = m_rcBtn.bottom - m_nFocusRectOffset;
        }
        break;

        case IBTN_ICON_BOTTOM_TEXT_TOP: {
            m_nCxIconStart = m_rcBtn.left + (m_rcBtn.Width() - m_nIconWidth) / 2;
            m_nCyIconStart = m_rcBtn.bottom - m_nFocusRectOffset - m_nIconHeight;
            m_rcText.left = m_rcBtn.left + m_nFocusRectOffset;
            m_rcText.top = m_rcBtn.top + m_nFocusRectOffset;
            m_rcText.right = m_rcBtn.right - m_nFocusRectOffset;
            m_rcText.bottom = m_rcBtn.bottom - m_nFocusRectOffset - m_nIconHeight;
        }
        break;

        default:
            break;
        }
    } else if (!bIsHasText && bIsHasIcon) { //没有text只有icon
        m_nCxIconStart = m_rcBtn.left + (m_rcBtn.Width() - m_nIconWidth) / 2;
        m_nCyIconStart = m_rcBtn.top + (m_rcBtn.Height() - m_nIconHeight) / 2;
        m_rcText.left = 0;
        m_rcText.top = 0;
        m_rcText.right = 0;
        m_rcText.bottom = 0;
    } else if (bIsHasText && !bIsHasIcon) { //只有text没有icon
        m_nCxIconStart = 0;
        m_nCyIconStart = 0;
        m_rcText.left = m_rcBtn.left;
        m_rcText.top = m_rcBtn.top;
        m_rcText.right = m_rcBtn.right;
        m_rcText.bottom = m_rcBtn.bottom;
    } else {
        m_nCxIconStart = 0;
        m_nCyIconStart = 0;
        m_rcText.left = 0;
        m_rcText.top = 0;
        m_rcText.right = 0;
        m_rcText.bottom = 0;
    }
}

//
// 绘制ICON
//
void CIconBtn::DrawIcon()
{
    // 判断有无icon
    if (!m_hIcon)
        return;

    // 如果Disabled则灰掉
    // 如果Pressed则icon向右及向下各移1格
    UINT flag = DST_ICON | (m_bIsDisabled ? DSS_DISABLED : DSS_NORMAL);
    int nCxIconStart = m_bIsPressed ? m_nCxIconStart + 1 : m_nCxIconStart;
    int nCyIconStart = m_bIsPressed ? m_nCyIconStart + 1 : m_nCyIconStart;
    // Draw icon
    ::DrawState(m_pDC->m_hDC, NULL, NULL, (LPARAM)m_hIcon, NULL,
                nCxIconStart, nCyIconStart, m_nIconWidth, m_nIconHeight, flag);
}

//
// 绘制Text
//
void CIconBtn::DrawText()
{
    // 判断有无text
    CString strText;
    GetWindowText(strText);

    if (strText.IsEmpty())
        return;

    // 如果按下则text向右及向下各移动一格
    if (m_bIsPressed) {
        m_rcText.left += 2;
    } else {
        m_rcText.bottom -= 2; // 使text真正垂直居中
    }

    // Draw text
    if (m_bIsDisabled) { //draw text并灰掉text
        CRect rcText(&m_rcText);
        rcText.OffsetRect(1, 1);
        m_pDC->SetTextColor(::GetSysColor(COLOR_3DHILIGHT));
        m_pDC->DrawText(strText, &rcText, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
        rcText.OffsetRect(-1, -1);
        m_pDC->SetTextColor(::GetSysColor(COLOR_3DSHADOW));
        m_pDC->DrawText(strText, &rcText, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
    } else { // draw text
        m_pDC->DrawText(strText, &m_rcText, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
    }
}

//
// 设定Icon
//
BOOL CIconBtn::SetIcon(int nIcon, int nCxDesired, int nCyDesired)
{
    HICON hIcon = (HICON)::LoadImage(::GetModuleHandle(NULL), MAKEINTRESOURCE(nIcon),
                                     IMAGE_ICON, nCxDesired, nCyDesired, 0);

    if (hIcon) {
        // 先释放先前的ICON
        ::DestroyIcon(m_hIcon);
        //
        m_hIcon = hIcon;
        // Get icon size
        ICONINFO ici;
        ::GetIconInfo(m_hIcon, &ici);
        BITMAP bm;
        ::GetObject(ici.hbmColor, sizeof(BITMAP), &bm);
        m_nIconWidth = bm.bmWidth;
        m_nIconHeight = bm.bmHeight;
        ::DeleteObject(ici.hbmColor);
        ::DeleteObject(ici.hbmMask);
        return TRUE;
    } else
        return FALSE;
}

//
// 设定Icon与Text的对齐方式
//
BOOL CIconBtn::SetAlign(BYTE byAlign)
{
    switch (byAlign) {
    case IBTN_ICON_LEFT_TEXT_RIGHT:
    case IBTN_ICON_RIGHT_TEXT_LEFT:
    case IBTN_ICON_TOP_TEXT_BOTTOM:
    case IBTN_ICON_BOTTOM_TEXT_TOP:
        m_byAlign = byAlign;

    default:
        return FALSE;
    }

    return TRUE;
}

// CIconBtn message handlers
