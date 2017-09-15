#if !defined(AFX_CWINLISTBOX_H__97A2000C_5D56_4299_AD61_4437DD00A3BF__INCLUDED_)
#define AFX_CWINLISTBOX_H__97A2000C_5D56_4299_AD61_4437DD00A3BF__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000
// CWinListBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////

#define C_CWINLISTBOX_CLASSNAME _T("MFC_CCWinListBox")

#include <afxtempl.h>

/////////////////////////////////////////////////////////////////////////////
// CCWinListBox window

class CCWinListBox : public CWnd
{
// Construction
public:
    CCWinListBox();

// Attributes
protected:
    // Item class
    class CListBoxItem : public CObject
    {
    public:
        CListBoxItem()
        {
            csLabel.Empty();
            rItem.SetRectEmpty();
            bSelected   = FALSE;
        }

        virtual ~CListBoxItem()
        {
            csLabel.Empty();
        }

        CString     csLabel;
        COLORREF    crFace;
        CRect       rItem;
        BOOL        bSelected;
    };

    // Listbox item storage
    CTypedPtrArray < CObArray, CListBoxItem* >  m_tpaItems;
    int                                         m_iTotalItems;

    // Font
    CFont       m_Font;

    // Colors
    COLORREF    m_crText, m_crSelText, m_crSelBorder1, m_crSelBorder2, m_crSelTextBk;
    COLORREF    m_crBorder1, m_crBorder2, m_crBkFrom, m_crBkTo;
    COLORREF    m_crSB_Text, m_crSB_Bk, m_crSB_Border1, m_crSB_Border2;

    // ListBox item dimensions
    int         m_iItemHeight;
    int         m_iColumnWidth;

    int         m_iDisplayColumn;
    int         m_iMaxColumn;

    // Scrollbar divisions
    class CScrollBarDiv : public CObject
    {
    public:
        CScrollBarDiv()
        {
            csLabel.Empty();
            rItem.SetRectEmpty();
            bPressed = FALSE;
        }

        virtual ~CScrollBarDiv()
        {
            csLabel.Empty();
        }

        CString     csLabel;
        CRect       rItem;
        BOOL        bPressed;
    };

    CTypedPtrArray < CObArray, CScrollBarDiv* > m_tpaSB;
    BOOL                                        m_bCalculateSB_Div;

// Operations
protected:
    BOOL        RegisterWindowClass();
    void        DrawGradientBackground(CDC* pDC, CRect rRect, COLORREF crFrom, COLORREF crTo);
    void        CalculateSBDivisions(CRect rSBRect);
    void        DrawSB_ShiftColumn(CDC *pDC, CRect rSBArea);

// Operations
public:
    virtual CCWinListBox&   SetTextFont(LONG nHeight, bool bBold, bool bItalic, CString csFaceName);

    virtual CCWinListBox&   SetBorderColor(COLORREF crBorder1, COLORREF crBorder2);

    virtual CCWinListBox&   SetBkColor(COLORREF crBkFrom, COLORREF crBkTo);

    virtual CCWinListBox&   SetDefaultTextColor(COLORREF crText);

    virtual CCWinListBox&   SetSelectedColors(COLORREF crSelText, COLORREF crSelTextBk,
            COLORREF crSelBorder1, COLORREF crSelBorder2);

    virtual CCWinListBox&   SetSBColors(COLORREF crText, COLORREF crBk,
                                        COLORREF crBorder1, COLORREF crBorder2);

    virtual CCWinListBox&   SetColumnWidth(int iNumberOfCharacters, BOOL bInvalidate = TRUE);

    void        RemoveAll(BOOL bInvalidate = TRUE);
    void        AddString(CString csLabel);
    void        AddStringWithColor(CString csLabel, COLORREF crFace);
    void        InsertString(int iIndex, CString csLabel);
    void        InsertStringWithColor(int iIndex, CString csLabel, COLORREF crFace);
    void        RemoveAt(int iIndex);
    void        ChangeStringAt(int iIndex, CString csLabel);
    void        ChangeColorAt(int iIndex, COLORREF crFace);
    void        ChangeStringAndColorAt(int iIndex, CString csLabel, COLORREF crFace);
    int         GetCount();
    CString     GetStringAt(int iIndex);
    COLORREF    GetColorAt(int iIndex);
    int         GetSelectedItem();

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CCWinListBox)
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CCWinListBox();

    // Generated message map functions
protected:
    //{{AFX_MSG(CCWinListBox)
    afx_msg void OnPaint();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnTimer(UINT nIDEvent);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CWINLISTBOX_H__97A2000C_5D56_4299_AD61_4437DD00A3BF__INCLUDED_)
