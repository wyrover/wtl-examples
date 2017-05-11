// MyWindow.h : interface of the CMyWindow class
//
/////////////////////////////////////////////////////////////////////////////
#if !defined(VFC_MYWINDOW_H__A6EE62C8_6F52_4d6b_8810_64B204C94772__INCLUDED_)
#define VFC_MYWINDOW_H__A6EE62C8_6F52_4d6b_8810_64B204C94772__INCLUDED_

#if _MSC_VER >= 1000
    #pragma once
#endif // _MSC_VER >= 1000

typedef CWinTraits < WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, WS_EX_APPWINDOW > CMyWindowTraits;

class CMyWindow : public CWindowImpl<CMyWindow, CWindow, CMyWindowTraits>
{
public:
    DECLARE_WND_CLASS(_T("My Window Class"))
public:
    BEGIN_MSG_MAP(CMyWindow)
    MESSAGE_HANDLER(WM_CLOSE, OnClose)
    MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
    MESSAGE_HANDLER(WM_PAINT, OnPaint)
    END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//  LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//  LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//  LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

    LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        CPaintDC dc(m_hWnd);
        //TODO: Add your drawing code here
        return 0;
    }

    LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        DestroyWindow();
        return 0;
    }

    LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        PostQuitMessage(0);
        return 0;
    }
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// VisualFC AppWizard will insert additional declarations immediately before the previous line.
#endif // !defined(VFC_MYWINDOW_H__A6EE62C8_6F52_4d6b_8810_64B204C94772__INCLUDED_)
