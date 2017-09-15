/*
    @author Ilnaz Nizametdinov

    @project HelloYandex

    @description
        Custom list control.
 */

#ifndef __GUI_CONTROLS_CUSTOM_LIST_H__
#define __GUI_CONTROLS_CUSTOM_LIST_H__

#include <vector>

class CCustomListCtrl : public CWindowImpl<CCustomListCtrl, CListViewCtrl>,
    public COwnerDraw<CCustomListCtrl>
{
public:
    typedef struct _Item {
        BOOL    bText; // either text or bitmap
        HBITMAP hBmp;
        LPTSTR  lpszText;

    } Item;

protected:
    typedef std::vector<Item> column_type;
    typedef std::vector<column_type> content_type;

    // Icon width & height
    static const int _iconSize = 32;

public:
    BEGIN_MSG_MAP(CCustomListCtrl)
    CHAIN_MSG_MAP_ALT(COwnerDraw<CCustomListCtrl>, 1)
    REFLECTED_NOTIFY_CODE_HANDLER(NM_CLICK, OnClick)
    DEFAULT_REFLECTION_HANDLER()
    END_MSG_MAP()

    // Overrides
    int AddColumn(LPCTSTR strItem, int nItem, int nSubItem = -1,
                  int nMask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM,
                  int nFmt = LVCFMT_LEFT)
    {
        ATLASSERT(nItem <= static_cast<int>(_content.size()));
        int iItem = CListViewCtrl::AddColumn(strItem, nItem, nSubItem, nMask, nFmt);

        if (-1 != iItem) {
            _content.insert(_content.begin() + nItem, column_type());
        }

        return iItem;
    }

    int AddItem(int nItem, int nSubItem, Item item)
    {
        ATLASSERT(nSubItem < static_cast<int>(_content.size()));
        ATLASSERT(nItem <= static_cast<int>(_content[nSubItem].size()));
        _content[nSubItem].insert(_content[nSubItem].begin() + nItem, item);
        return nItem;
    }

    void DeleteItemMy(int nItem)
    {
        ATLASSERT(nItem < static_cast<int>(_content[0].size()));

        for (int i = 0, c = static_cast<int>(_content.size()); i < c; ++i) {
            _content[i].erase(_content[i].begin() + nItem);
        }
    }

    void Update()
    {
        // Assume that all columns has the same number of rows
        SetItemCount(_content[0].size());
    }

    void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
    {
        CDCHandle dc = lpDrawItemStruct->hDC;
        dc.SaveDC();
        {
            RECT* rc = &(lpDrawItemStruct->rcItem); // alias
            // Clear area
            dc.FillRect(rc, COLOR_WINDOW);

            // Draw highlight mark
            if (lpDrawItemStruct->itemState & ODS_SELECTED) {
                CBrush highlight;
                highlight.CreateSolidBrush(GetSysColor(COLOR_HIGHLIGHT));
                dc.FrameRect(rc, highlight);
            }

            // Draw subitems
            for (int i = 0, c = static_cast<int>(_content.size()); i < c; ++i) {
                DrawSubItem(lpDrawItemStruct, i);
            }
        }
        dc.RestoreDC(-1);
    }

    void DrawSubItem(LPDRAWITEMSTRUCT lpDrawItemStruct, int nSubItem)
    {
        int nItem = lpDrawItemStruct->itemID; // alias
        // Determine subitem bounds
        RECT rc;
        GetSubItemRect(nItem, nSubItem, LVIR_BOUNDS, &rc);

        if (0 == nSubItem) {
            // Fix for 0th column
            rc.right = GetColumnWidth(0);
        }

        CDCHandle dc = lpDrawItemStruct->hDC;
        dc.SaveDC();
        {
            if (_content[nSubItem][nItem].bText) {
                // Draw text
                int width = GetStringWidth(_content[nSubItem][nItem].lpszText);
                TEXTMETRIC tm = { 0 };
                dc.GetTextMetrics(&tm);
                dc.TextOut(
                    // center horizontally & vertically
                    rc.left + (rc.right - rc.left - width) / 2 + 1,
                    rc.top + (rc.bottom - rc.top - tm.tmHeight) / 2 + 1,
                    _content[nSubItem][nItem].lpszText);
            } else {
                // Draw bitmap
                CDC dcMem;
                dcMem.CreateCompatibleDC(dc);
                dcMem.SelectBitmap(_content[nSubItem][nItem].hBmp);
                // Aplha-blend function
                BLENDFUNCTION bf;
                bf.BlendOp = AC_SRC_OVER;
                bf.BlendFlags = 0;
                bf.SourceConstantAlpha = 255;
                bf.AlphaFormat = AC_SRC_ALPHA;
                // Draw with transparency
                dc.AlphaBlend(
                    // center horizontally
                    rc.left + (rc.right - rc.left - _iconSize) / 2 + 1, rc.top + 1,
                    _iconSize, _iconSize, dcMem, 0, 0, _iconSize, _iconSize, bf);
            }
        }
        dc.RestoreDC(-1);
    }

    void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
    {
        lpMeasureItemStruct->itemHeight = _iconSize + 2 /* per pixel for border */ + 1;
    }

    // Avoid ambiguity
    void DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct)
    {
        // nothing
    }

    LRESULT OnClick(int idCtrl, LPNMHDR pNMHDR, BOOL& bHandled)
    {
        LPNMITEMACTIVATE pNMA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
        // Toggle state
        _content[pNMA->iSubItem][pNMA->iItem].bText = !_content[pNMA->iSubItem][pNMA->iItem].bText;
        RedrawItems(pNMA->iItem, pNMA->iItem);
        return 0;
    }

protected:
    content_type _content;
};

#endif // __GUI_CONTROLS_CUSTOM_LIST_H__
