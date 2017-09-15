// IconListBox.cpp : implementation file
//

#include "stdafx.h"
#include "CIconListBox_Demo.h"
#include "IconListBox.h"


// CIconListBox

IMPLEMENT_DYNAMIC(CIconListBox, CListBox)

CIconListBox::CIconListBox()
    : m_nIconHeight(0), m_nOffset(2)
{
}

CIconListBox::~CIconListBox()
{
}


BEGIN_MESSAGE_MAP(CIconListBox, CListBox)
END_MESSAGE_MAP()



// CIconListBox message handlers

void CIconListBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    // 准备工作
    CDC dc;
    dc.Attach(lpDrawItemStruct->hDC);
    dc.SetBkMode(TRANSPARENT);
    ASSERT(lpDrawItemStruct->CtlType == ODT_LISTBOX);
    CString cstrText;
    CListBox::GetText(lpDrawItemStruct->itemID, cstrText);
    ASSERT(!cstrText.IsEmpty());
    // 监测状态
    BOOL bIsSelected = (lpDrawItemStruct->itemAction | ODA_SELECT) &&
                       (lpDrawItemStruct->itemState & ODS_SELECTED);
    BOOL bIsFocused = (lpDrawItemStruct->itemAction | ODA_FOCUS) &&
                      (lpDrawItemStruct->itemState & ODS_FOCUS);

    // Draw背景
    if (bIsSelected) {
        CBrush brushBk(::GetSysColor(COLOR_HIGHLIGHT));
        dc.FillRect(&lpDrawItemStruct->rcItem, &brushBk);
    } else {
        CBrush brushBk(dc.GetBkColor());
        dc.FillRect(&lpDrawItemStruct->rcItem, &brushBk);
    }

    // Draw icon
    LBDATA *pLbData = (LBDATA*)CListBox::GetItemDataPtr(lpDrawItemStruct->itemID);

    if (NULL != pLbData && (LBDATA*) - 1 != pLbData
        && NULL != pLbData->hIcon) {
        UINT flag = DST_ICON;
        ::DrawState(lpDrawItemStruct->hDC, NULL, NULL, (LPARAM)pLbData->hIcon, NULL,
                    lpDrawItemStruct->rcItem.left + m_nOffset, lpDrawItemStruct->rcItem.top + m_nOffset,
                    pLbData->nIconWidth, pLbData->nIconHeight, flag);
    }

    // Draw text
    if (bIsSelected) {
        dc.SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
    } else {
        dc.SetTextColor(RGB(255, 0, 0));
    }

    CRect rcText;
    rcText.left = lpDrawItemStruct->rcItem.left + m_nOffset + pLbData->nIconWidth + m_nOffset;
    rcText.top = lpDrawItemStruct->rcItem.top + m_nOffset + m_nOffset;
    rcText.right = lpDrawItemStruct->rcItem.right - m_nOffset;
    rcText.bottom = lpDrawItemStruct->rcItem.bottom - m_nOffset;
    dc.DrawText(
        cstrText,
        &rcText,
        DT_LEFT | DT_SINGLELINE | DT_VCENTER);
    // 收尾工作
    dc.Detach();
}

//
// 确定ListBox中每一项应绘制的高度
//
void CIconListBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
    // 确定Text的高度
    ASSERT(lpMeasureItemStruct->CtlType == ODT_LISTBOX);
    LPCTSTR lpszText = (LPCTSTR) lpMeasureItemStruct->itemData;
    ASSERT(lpszText != NULL);
    CSize   sz;
    CDC*    pDC = GetDC();
    sz = pDC->GetTextExtent(lpszText);
    ReleaseDC(pDC);
    // 比较Text与Icon的高度,取大者
    int nItemHeight = 2 * sz.cy > m_nIconHeight + m_nOffset * 2 ? 2 * sz.cy : m_nIconHeight + m_nOffset * 2;
    lpMeasureItemStruct->itemHeight = nItemHeight;
}

int CIconListBox::AddString(LPCTSTR lpszItem, int nIcon)
{
    LBDATA *pLbData = NULL;
    m_nIconHeight = 0;
    // 加载Icon
    HICON hIcon = (HICON)::LoadImage(::GetModuleHandle(NULL), MAKEINTRESOURCE(nIcon),
                                     IMAGE_ICON, 0, 0, 0);

    if (hIcon != NULL) {
        pLbData = new LBDATA();
        ICONINFO ici;
        ::GetIconInfo(hIcon, &ici);
        BITMAP bm;
        ::GetObject(ici.hbmColor, sizeof(BITMAP), &bm);
        ::DeleteObject(ici.hbmColor);
        ::DeleteObject(ici.hbmMask);
        pLbData->hIcon = hIcon;
        pLbData->nIconHeight = bm.bmHeight;
        pLbData->nIconWidth = bm.bmWidth;
        m_nIconHeight = bm.bmHeight;
    }

    // Add string and lbdata
    int nIndex = CListBox::AddString(lpszItem);

    if (LB_ERR == nIndex || LB_ERRSPACE == nIndex) {
        if (NULL != pLbData) {
            delete pLbData;
            ::DestroyIcon(hIcon);
        }
    } else {
        CListBox::SetItemDataPtr(nIndex, pLbData);
    }

    return nIndex;
}

int CIconListBox::InsertString(int nIndex, LPCTSTR lpszItem, int nIcon)
{
    LBDATA *pLbData = NULL;
    m_nIconHeight = 0;
    // 加载Icon
    HICON hIcon = (HICON)::LoadImage(::GetModuleHandle(NULL), MAKEINTRESOURCE(nIcon),
                                     IMAGE_ICON, 0, 0, 0);

    if (hIcon != NULL) {
        pLbData = new LBDATA();
        ICONINFO ici;
        ::GetIconInfo(hIcon, &ici);
        BITMAP bm;
        ::GetObject(ici.hbmColor, sizeof(BITMAP), &bm);
        ::DeleteObject(ici.hbmColor);
        ::DeleteObject(ici.hbmMask);
        pLbData->hIcon = hIcon;
        pLbData->nIconHeight = bm.bmHeight;
        pLbData->nIconWidth = bm.bmWidth;
        m_nIconHeight = bm.bmHeight;
    }

    // Insert string and lbdata
    nIndex = CListBox::InsertString(nIndex, lpszItem);

    if (LB_ERR == nIndex || LB_ERRSPACE == nIndex) {
        if (NULL != pLbData) {
            ::DestroyIcon(hIcon);
            delete pLbData;
        }
    } else {
        CListBox::SetItemDataPtr(nIndex, pLbData);
    }

    return nIndex;
}

int CIconListBox::DeleteString(UINT nIndex)
{
    DeleteItemData(nIndex);
    return CListBox::DeleteString(nIndex);
}

void CIconListBox::DeleteItemData(UINT nIndex)
{
    LBDATA *pLbData = (LBDATA*) CListBox::GetItemDataPtr(nIndex);

    if ((LBDATA*) - 1 != pLbData && NULL != pLbData) {
        if (pLbData->hIcon)
            ::DestroyIcon(pLbData->hIcon);

        delete pLbData;
    }
}

void CIconListBox::ResetContent()
{
    int nCount = GetCount();

    for (int i = 0; i < nCount; ++i) {
        DeleteItemData(i);
    }

    CListBox::ResetContent();
}

//void CIconListBox::PreSubclassWindow()
//{
//  // TODO: Add your specialized code here and/or call the base class
//
//  //this->ModifyStyle(0, LBS_OWNERDRAWVARIABLE | LBS_HASSTRINGS | LBS_NOINTEGRALHEIGHT);
//
//  CListBox::PreSubclassWindow();
//}
