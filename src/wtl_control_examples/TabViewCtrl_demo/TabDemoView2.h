// TabDemoView2.h : interface of the CTabDemoView2 class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TabDemoView2_H__DFA8FA02_AB85_4E96_BB9B_C4EDBE0A5687__INCLUDED_)
#define AFX_TabDemoView2_H__DFA8FA02_AB85_4E96_BB9B_C4EDBE0A5687__INCLUDED_

#if _MSC_VER >= 1000
    #pragma once
#endif // _MSC_VER >= 1000

class CTabDemoView2 : public CWindowImpl<CTabDemoView2, CListViewCtrl>
{
public:
    DECLARE_WND_SUPERCLASS(NULL, CListViewCtrl::GetWndClassName())

    BOOL PreTranslateMessage(MSG* pMsg)
    {
        pMsg;
        return FALSE;
    }

    BEGIN_MSG_MAP(CTabDemoView2)
    MESSAGE_HANDLER(WM_CREATE, OnCreate)
    END_MSG_MAP()

    LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL&)
    {
        LRESULT lRet = DefWindowProc(uMsg, wParam, lParam);
        ModifyStyle(0, LVS_REPORT);
        InsertColumn(0, "Demo Column", LVCFMT_LEFT, 200, -1);
        InsertItem(32768, "Demo Row 1");
        InsertItem(32768, "Demo Row 2");
        InsertItem(32768, "Demo Row 3");
        InsertItem(32768, "Demo Row 4");
        InsertItem(32768, "Demo Row 5");
        InsertItem(32768, "Demo Row 6");
        return lRet;
    }
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TabDemoView2_H__DFA8FA02_AB85_4E96_BB9B_C4EDBE0A5687__INCLUDED_)
