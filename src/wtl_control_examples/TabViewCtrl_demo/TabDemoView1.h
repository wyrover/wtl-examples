// TabDemoView1.h : interface of the CTabDemoView1 class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TabDemoView1_H__DFA8FA02_AB85_4E96_BB9B_C4EDBE0A5687__INCLUDED_)
#define AFX_TabDemoView1_H__DFA8FA02_AB85_4E96_BB9B_C4EDBE0A5687__INCLUDED_

#if _MSC_VER >= 1000
    #pragma once
#endif // _MSC_VER >= 1000

class CTabDemoView1 : public CDialogImpl<CTabDemoView1>
{
public:
    enum { IDD = IDD_TABVIEWDEMO_FORM };

    BOOL PreTranslateMessage(MSG* pMsg)
    {
        return IsDialogMessage(pMsg);
    }

    BEGIN_MSG_MAP(CTabDemoView1)
    END_MSG_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TabDemoView1_H__DFA8FA02_AB85_4E96_BB9B_C4EDBE0A5687__INCLUDED_)
