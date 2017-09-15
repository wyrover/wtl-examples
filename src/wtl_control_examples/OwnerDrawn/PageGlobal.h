//////////////////////////////////////////////////////////////////////////////////////////
//      Project: PinkYeti
//   $Workfile:: PageGlobal.h                                         $   - Title
//
//  Description: This class will handle the settings for global information
//               These settings do not depend on the channel selected.
//
//       Author: Jay Giganti
// Date Created: 2/10/2001
//     $Author:: Jay                                                   $   - Reviewer
//    $Modtime:: 4/02/01 3:50p                                         $   - Date Reviewed
//
//  This code may be used in compiled form in any way you desire. This
//  file may be redistributed unmodified by any means PROVIDING it is
//  not sold for profit without the authors written consent, and
//  providing that this notice and the authors name and all copyright
//  notices remains intact.
//
//  Email JGiganti@hotmail.com letting him know how you are using it would be nice as well.
//
//  Most of this code has been modified from other exaples on Code Project to do what I
//  need it to do and/or ported to use WTL
//
//
//     $Archive:: /Code/Apps/PinkYeti/PageGlobal.h                                      $
//
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef __PAGE_GLOBAL_H__
#define __PAGE_GLOBAL_H__

#include <AtlDlgs.h>
#include "Resource.h"
#include "ui_ToolTipDlg.h"

class CPageGlobal : public CPropertyPageImpl<CPageGlobal>
{
public:
    enum {IDD = IDD_PAGE_GLOBAL};

    CPageGlobal();
    virtual ~CPageGlobal();

    BEGIN_MSG_MAP(CPageGlobal)
    MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
    END_MSG_MAP()

protected:
    LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    CButton         m_AutoLogIn;
    CButton         m_AutoRun;
    CButton         m_AutoDownLoad;
    CButton         m_DisplayTrayMsg;
    ui_ToolTipDlg   m_TipDlg;

private:                                                //Disable these
    CPageGlobal(const CPageGlobal& rhs);                //Copy constructor
    CPageGlobal& operator =(const CPageGlobal& rhs);    //Assignment
};

#endif //__PAGE_GLOBAL_H__
