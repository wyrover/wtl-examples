//////////////////////////////////////////////////////////////////////////////////////////
//      Project: PinkYeti
//   $Workfile:: PageBlocks.h                                          $   - Title
//
//  Description: This class will handle the settings for what content that want to allow
//               based on how people have rated it for the type of information it holds
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
//     $Archive:: /Code/Apps/PinkYeti/PageBlocks.h                                       $
//
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef __PAGE_BLOCKS_H__
#define __PAGE_BLOCKS_H__

#include <AtlDlgs.h>
#include "Resource.h"
#include "ui_ToolTipDlg.h"


class CPageBlocks : public CPropertyPageImpl<CPageBlocks>
{
public:
    enum {IDD = IDD_PAGE_BLOCKS};

    CPageBlocks();
    virtual ~CPageBlocks();

    BEGIN_MSG_MAP(CPageBlocks)
    MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
    END_MSG_MAP()

protected:
    LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    CButton         m_Mature;
    CButton         m_Spam;
    CButton         m_Offensive;
    ui_ToolTipDlg   m_TipDlg;

    bool            m_bMature;
    bool            m_bSpam;
    bool            m_bOffensive;

private:                                                //Disable these
    CPageBlocks(const CPageBlocks& rhs);                //Copy constructor
    CPageBlocks& operator =(const CPageBlocks& rhs);    //Assignment
};

#endif //__PAGE_BLOCKS_H__

