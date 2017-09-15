// C_Button.cpp : implementation file
//

#include "stdafx.h"
#include "CustomListBox.h"
#include "C_Button.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CC_Button

CC_Button::CC_Button()
{
}

CC_Button::~CC_Button()
{
}


BEGIN_MESSAGE_MAP(CC_Button, CButton)
    //{{AFX_MSG_MAP(CC_Button)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CC_Button message handlers

void CC_Button::PreSubclassWindow()
{
    CButton::PreSubclassWindow();
    ModifyStyle(0, BS_OWNERDRAW);
}

void CC_Button::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
    CDC*    pDC     = CDC::FromHandle(lpDIS->hDC);
    CRect   rFrame  = lpDIS->rcItem;
    UINT    nState  = lpDIS->itemState;
    pDC->FillSolidRect(rFrame, DLG_COLOR_BACKGROUND);

    if (nState & ODS_SELECTED)
        pDC->Draw3dRect(rFrame, RGB(0, 0, 0), RGB(156, 156, 156));
    else
        pDC->Draw3dRect(rFrame, RGB(156, 156, 156), RGB(0, 0, 0));

    CString csText;
    GetWindowText(csText);
    int         iMode       = pDC->SetBkMode(TRANSPARENT);
    COLORREF    crOldColor  = pDC->SetTextColor(RGB(0, 0, 0));
    pDC->DrawText(csText, rFrame, DT_SINGLELINE | DT_VCENTER | SS_CENTER);
    pDC->SetBkMode(iMode);
    pDC->SetTextColor(crOldColor);
}
