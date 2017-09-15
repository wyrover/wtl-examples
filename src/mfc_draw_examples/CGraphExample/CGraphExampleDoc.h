// CGraphExampleDoc.h : interface of the CCGraphExampleDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CGRAPHEXAMPLEDOC_H__FF171B8A_F20C_47A8_8072_AE411396FF80__INCLUDED_)
#define AFX_CGRAPHEXAMPLEDOC_H__FF171B8A_F20C_47A8_8072_AE411396FF80__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000


class CCGraphExampleDoc : public CDocument
{
protected: // create from serialization only
    CCGraphExampleDoc();
    DECLARE_DYNCREATE(CCGraphExampleDoc)

// Attributes
public:

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CCGraphExampleDoc)
public:
    virtual BOOL OnNewDocument();
    virtual void Serialize(CArchive& ar);
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CCGraphExampleDoc();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
    //{{AFX_MSG(CCGraphExampleDoc)
    // NOTE - the ClassWizard will add and remove member functions here.
    //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CGRAPHEXAMPLEDOC_H__FF171B8A_F20C_47A8_8072_AE411396FF80__INCLUDED_)
