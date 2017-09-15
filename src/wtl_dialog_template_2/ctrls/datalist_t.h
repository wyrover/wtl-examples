#ifndef _DATALIST_T_H_
#define _DATALIST_T_H_

#include <atlwin.h>
#include <atlctrls.h>
#include <atlframe.h>
#include <atlgdi.h>
#include <atlstr.h>

class CDevListBoxImpl : public CWindowImpl<CDevListBoxImpl, CListBox>,
    public COwnerDraw<CDevListBoxImpl>
{
public:
    CDevListBoxImpl()
    {
        m_nDivider = 200;
    }

    void GetTextEx(int nIndex, int sub, CString& rString)
    {
        GetText(nIndex, rString);
        int pos = rString.Find(_T(";"));

        if (pos != -1) {
            rString = rString.Left(pos);
            rString.TrimRight();
        }
    }

    BEGIN_MSG_MAP(CDevListBoxImpl)
    MESSAGE_HANDLER(WM_CREATE, OnCreate)
    CHAIN_MSG_MAP_ALT(COwnerDraw<CDevListBoxImpl>, 1)
    DEFAULT_REFLECTION_HANDLER()
    END_MSG_MAP()

    // overridden to provide proper initialization
    BOOL SubclassWindow(HWND hWnd)
    {
        BOOL bRet = CWindowImpl<CDevListBoxImpl, CListBox>::SubclassWindow(hWnd);

        if (bRet)
            Init();

        return bRet;
    }
    LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        // TODO : Add Code for message handler. Call DefWindowProc if necessary.
        Init();
        bHandled = FALSE;
        return 1;
    }
    // Implementation
    void Init()
    {
        // We need this style to prevent Windows from painting the button
        ModifyStyle(0, /*BS_OWNERDRAW |*/ LBS_OWNERDRAWFIXED | LBS_HASSTRINGS);
    }

    void DrawItem(LPDRAWITEMSTRUCT lpDIS)
    {
        CDCHandle dc = lpDIS->hDC;
        CRect rect = lpDIS->rcItem;

        if (m_nDivider == 0)
            m_nDivider = rect.Width() / 2;

        if (lpDIS->itemID != (UINT) - 1) {
            TCHAR sz[128] = { 0 };
            CListBox::GetText(lpDIS->itemID, sz);
            COLORREF oldColor;

            //draw two rectangles, one for each row column
            if ((lpDIS->itemState & ODS_SELECTED) == ODS_SELECTED) {
                dc.FillSolidRect(&lpDIS->rcItem, RGB(0, 0, 128));
                oldColor = dc.SetTextColor(RGB(255, 255, 255));
            } else {
                dc.FillSolidRect(&lpDIS->rcItem, RGB(255, 255, 255));
                oldColor = dc.SetTextColor(RGB(0, 0, 0));
            }

            dc.SetBkMode(TRANSPARENT);
            TCHAR * tok = ::_tcstok(sz, _T(";"));
            int index = 0;
            int old_div = m_nDivider;

            while (tok != NULL) {
                if (m_level.GetSize() > index) {
                    m_nDivider = m_level[index];
                }

                dc.DrawText(tok, lstrlen(tok), rect, DT_LEFT | DT_SINGLELINE);
                rect.left += m_nDivider;
                SIZE sz;
                dc.GetTextExtent(tok, -1, &sz);

                if (sz.cx >= 2 * m_nDivider) {
                    rect.left = rect.left - m_nDivider + sz.cx + 20;
                } else if (sz.cx >= m_nDivider) {
                    rect.left += m_nDivider;
                }

                tok = ::_tcstok(NULL, _T(";"));
                index++;
            }

            m_nDivider = old_div;
            dc.SetTextColor(oldColor);
        }

        SetMsgHandled(FALSE);
    }
    int m_nDivider;
    CSimpleValArray<int>    m_level;
};


template <typename TData>
class CDataListT : public CDevListBoxImpl//CListBoxT<ATL::CWindow>
{
public:
    CDataListT()
    { }
public:
    TData * GetCurSelData()
    {
        int index = GetCurSel();

        if (index == -1) {
            return NULL;
        }

        return (TData*)GetItemData(index);
    }
    int AddStringData(LPCTSTR lpszItem, TData * data)
    {
        int index = AddString(lpszItem);

        if (index != -1 && data != NULL) {
            SetItemData(index, (DWORD)data);
        }

        return index;
    }
    int DeleteStringData(UINT index)
    {
        if (index == -1)
            return -1;

        SetItemData(index, 0);
        return DeleteString(index);
    }
};


#endif