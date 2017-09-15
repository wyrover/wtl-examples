// SkinWindowView.h : interface of the CSkinWindowView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKINWINDOWVIEW_H__A9993768_316B_4271_AE12_86D1051E4FC1__INCLUDED_)
#define AFX_SKINWINDOWVIEW_H__A9993768_316B_4271_AE12_86D1051E4FC1__INCLUDED_

#if _MSC_VER >= 1000
    #pragma once
#endif // _MSC_VER >= 1000

class CSkinWindowView : public CWindowImpl<CSkinWindowView, CEdit>
{
public:
    DECLARE_WND_SUPERCLASS(NULL, CEdit::GetWndClassName())

    BOOL PreTranslateMessage(MSG* pMsg);

    BEGIN_MSG_MAP(CSkinWindowView)
    END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//  LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//  LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//  LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKINWINDOWVIEW_H__A9993768_316B_4271_AE12_86D1051E4FC1__INCLUDED_)
