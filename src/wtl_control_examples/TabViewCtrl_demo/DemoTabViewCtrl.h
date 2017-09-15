// DemoTabViewCtrl.h: interface for the DemoTabViewCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CDEMOTABVIEWCTRL_H__D0C97675_A3D6_459A_BAE5_C40DE83A361A__INCLUDED_)
#define AFX_CDEMOTABVIEWCTRL_H__D0C97675_A3D6_459A_BAE5_C40DE83A361A__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

#include "WTLTabViewCtrl.h"
#include "TabViewDemoView.h"
#include "TabDemoView1.h"
#include "TabDemoView2.h"


//==============================================================================
/**
 *      @class CDemoTabViewCtrl
 *
 *      This class inherits from CWTLTabViewCtrl and implements the instance
 *      of the tab control used by the demo application. It adds various tab
 *      windows to the tab control. It uses the param member of each tab to
 *      store a pointer to the dynamically created window class that manages
 *      the window or "view" on each tab. This dynamically created pointer
 *      is deleted in the OnTabRemoved virtual method when a tab is removed.
 *
 *      It uses the image index to determine the type of window to be deleted.
 */
//==============================================================================
class CDemoTabViewCtrl : public CWTLTabViewCtrl
{
    //==============================================================================
    //  Enums
    //==============================================================================

protected:

    enum {
        TABWINDOW_HELP  = 0,
        TABWINDOW_VIEW1 = 1,
        TABWINDOW_VIEW2 = 2,
    };


    //==============================================================================
    //  Methods
    //==============================================================================

public:

    CDemoTabViewCtrl()
    {
    }

    virtual ~CDemoTabViewCtrl()
    {
    }

    void AddHelpTab()
    {
        TCHAR theFileName[ MAX_PATH ];
        ::GetModuleFileName(_Module.m_hInst, theFileName, sizeof(theFileName));
        CString theUrlString;
        theUrlString.Format("res://%s/23/TabViewCtrl.html", theFileName);
        CTabViewDemoView*   theDemoView = new CTabViewDemoView;
        theDemoView->Create(*this, rcDefault, theUrlString, WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_HSCROLL | WS_VSCROLL, WS_EX_CLIENTEDGE);
        AddTab("Help", *theDemoView, TRUE, TABWINDOW_HELP, (LPARAM) theDemoView);
    }

    void AddDemoView1Tab(LPCTSTR inTabName)
    {
        CTabDemoView1*  theDemoView = new CTabDemoView1;
        theDemoView->Create(*this);
        AddTab(inTabName, *theDemoView, FALSE, TABWINDOW_VIEW1, (LPARAM) theDemoView);
    }

    void AddDemoView2Tab(LPCTSTR inTabName)
    {
        CTabDemoView2*  theDemoView = new CTabDemoView2;
        theDemoView->Create(*this, rcDefault, NULL, WS_CHILD, WS_EX_STATICEDGE);
        AddTab(inTabName, *theDemoView, TRUE, TABWINDOW_VIEW2, (LPARAM) theDemoView);
    }

    virtual void OnTabRemoved(int inTabIndex)
    {
        LPARAM theTabParam = GetTabParam(inTabIndex);

        if (theTabParam != 0) {
            int theTabImage = GetTabImage(inTabIndex);

            switch (theTabImage) {
            case TABWINDOW_HELP: {
                CTabViewDemoView* theWindowPtr = reinterpret_cast<CTabViewDemoView*>(theTabParam);
                theWindowPtr->DestroyWindow();
                delete theWindowPtr;
                break;
            }

            case TABWINDOW_VIEW1: {
                CTabDemoView1* theWindowPtr = reinterpret_cast<CTabDemoView1*>(theTabParam);
                theWindowPtr->DestroyWindow();
                delete theWindowPtr;
                break;
            }

            case TABWINDOW_VIEW2: {
                CTabDemoView2* theWindowPtr = reinterpret_cast<CTabDemoView2*>(theTabParam);
                theWindowPtr->DestroyWindow();
                delete theWindowPtr;
                break;
            }
            }
        }
    }


    //==============================================================================
    //  WTL
    //==============================================================================

public:
    DECLARE_WND_SUPERCLASS(NULL, CWTLTabViewCtrl::GetWndClassName())

    BOOL PreTranslateMessage(MSG* pMsg)
    {
        pMsg;
        return FALSE;
    }

    BEGIN_MSG_MAP_EX(CDemoTabViewCtrl)
    CHAIN_MSG_MAP(CWTLTabViewCtrl)
    END_MSG_MAP()
};

#endif // !defined(AFX_CDEMOTABVIEWCTRL_H__D0C97675_A3D6_459A_BAE5_C40DE83A361A__INCLUDED_)
