// CGraphExampleView.h : interface of the CCGraphExampleView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CGRAPHEXAMPLEVIEW_H__19320CFB_D222_4E31_AA36_7DAB89F4FE70__INCLUDED_)
#define AFX_CGRAPHEXAMPLEVIEW_H__19320CFB_D222_4E31_AA36_7DAB89F4FE70__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000

#include "GraphObject.h"


class CCGraphExampleView : public CView
{
protected: // create from serialization only
    CCGraphExampleView();
    DECLARE_DYNCREATE(CCGraphExampleView)

// Attributes
public:
    CCGraphExampleDoc* GetDocument();

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CCGraphExampleView)
public:
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    virtual void OnInitialUpdate();
protected:
    virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
    virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
    virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CCGraphExampleView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    CGraphObject* m_pGraphObject1;
    CGraphObject* m_pGraphObject2;
    CGraphObject* m_pGraphObject3;
    CGraphObject* m_pGraphObject4;
    CGraphObject* m_pGraphObject5;
    CGraphObject* m_pGraphObject6;
    CGraphObject* m_pGraphObject7;
    CGraphObject* m_pGraphObject8;
    CGraphObject* m_pGraphObject9;
    CGraphObject* m_pGraphObject10;
    CGraphObject* m_pGraphObject11;
    CGraphObject* m_pGraphObject12;

// Generated message map functions
protected:
    //{{AFX_MSG(CCGraphExampleView)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CGraphExampleView.cpp
inline CCGraphExampleDoc* CCGraphExampleView::GetDocument()
{
    return (CCGraphExampleDoc*)m_pDocument;
}
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CGRAPHEXAMPLEVIEW_H__19320CFB_D222_4E31_AA36_7DAB89F4FE70__INCLUDED_)
