// TabViewDemoView.h : interface of the CTabViewDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TABVIEWDEMOVIEW_H__846BA7F1_847B_11D6_B650_0020780D200B__INCLUDED_)
#define AFX_TABVIEWDEMOVIEW_H__846BA7F1_847B_11D6_B650_0020780D200B__INCLUDED_

#if _MSC_VER >= 1000
    #pragma once
#endif // _MSC_VER >= 1000

class CTabViewDemoView : public CWindowImpl<CTabViewDemoView, CAxWindow>
{
public:
    DECLARE_WND_SUPERCLASS(NULL, CAxWindow::GetWndClassName())

    BOOL PreTranslateMessage(MSG* pMsg)
    {
        if ((pMsg->message < WM_KEYFIRST || pMsg->message > WM_KEYLAST) &&
            (pMsg->message < WM_MOUSEFIRST || pMsg->message > WM_MOUSELAST))
            return FALSE;

        // give HTML page a chance to translate this message
        return (BOOL)SendMessage(WM_FORWARDMSG, 0, (LPARAM)pMsg);
    }

    BEGIN_MSG_MAP(CTabViewDemoView)
    END_MSG_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABVIEWDEMOVIEW_H__846BA7F1_847B_11D6_B650_0020780D200B__INCLUDED_)
