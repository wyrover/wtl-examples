// CGraphExampleDoc.cpp : implementation of the CCGraphExampleDoc class
//

#include "stdafx.h"
#include "CGraphExample.h"

#include "CGraphExampleDoc.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCGraphExampleDoc

IMPLEMENT_DYNCREATE(CCGraphExampleDoc, CDocument)

BEGIN_MESSAGE_MAP(CCGraphExampleDoc, CDocument)
    //{{AFX_MSG_MAP(CCGraphExampleDoc)
    // NOTE - the ClassWizard will add and remove mapping macros here.
    //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCGraphExampleDoc construction/destruction

CCGraphExampleDoc::CCGraphExampleDoc()
{
    // TODO: add one-time construction code here
}

CCGraphExampleDoc::~CCGraphExampleDoc()
{
}

BOOL CCGraphExampleDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;

    // TODO: add reinitialization code here
    // (SDI documents will reuse this document)
    return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCGraphExampleDoc serialization

void CCGraphExampleDoc::Serialize(CArchive& ar)
{
    if (ar.IsStoring()) {
        // TODO: add storing code here
    } else {
        // TODO: add loading code here
    }
}

/////////////////////////////////////////////////////////////////////////////
// CCGraphExampleDoc diagnostics

#ifdef _DEBUG
void CCGraphExampleDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CCGraphExampleDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCGraphExampleDoc commands
