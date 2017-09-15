// ChooseColorsDlg.cpp: implementation of the CChooseColorsDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "kibbles.h"
#include "ChooseColorsDlg.h"

//////////////////////////////////////////////////////////////////////
// Construction

CChooseColorsDlg::CChooseColorsDlg()
{
}


//////////////////////////////////////////////////////////////////////
// Message handlers

BOOL CChooseColorsDlg::OnInitDialog(HWND hwndFocus, LPARAM lParam)
{
    DoDataExchange();
    CenterWindow();
    // Set up the color buttons
    m_btnBkClr.SetDefaultText(IDS_COLORBTN_DEFAULT);
    m_btnBkClr.SetCustomText(IDS_COLORBTN_MORECOLORS);
    m_btnDownloadedOutlineClr.SetDefaultText(IDS_COLORBTN_DEFAULT);
    m_btnDownloadedOutlineClr.SetCustomText(IDS_COLORBTN_MORECOLORS);
    m_btnRemainingOutlineClr.SetDefaultText(IDS_COLORBTN_DEFAULT);
    m_btnRemainingOutlineClr.SetCustomText(IDS_COLORBTN_MORECOLORS);
    m_btnRemainingFillClr.SetDefaultText(IDS_COLORBTN_DEFAULT);
    m_btnRemainingFillClr.SetCustomText(IDS_COLORBTN_MORECOLORS);
    m_btnBkClr.SetDefaultColor(g_crBkgndDefault);
    m_btnDownloadedOutlineClr.SetDefaultColor(g_crDownloadedPartPenDefault);
    m_btnRemainingOutlineClr.SetDefaultColor(g_crRemainingPartPenDefault);
    m_btnRemainingFillClr.SetDefaultColor(g_crRemainingPartFillDefault);
    m_btnBkClr.SetColor(m_crBkgnd);
    m_btnDownloadedOutlineClr.SetColor(m_crDownloadedOutline);
    m_btnRemainingOutlineClr.SetColor(m_crRemainingOutline);
    m_btnRemainingFillClr.SetColor(m_crRemainingFill);
    return TRUE;
}


//////////////////////////////////////////////////////////////////////
// Command handlers

void CChooseColorsDlg::OnChooseTextColor(UINT uCode, int nID, HWND hwndCtrl)
{
    CColorDialog cd(m_crText, CC_ANYCOLOR | CC_FULLOPEN);

    if (IDOK == cd.DoModal(*this))
        m_crText = cd.GetColor();
}

void CChooseColorsDlg::OnOK(UINT uCode, int nID, HWND hwndCtrl)
{
    m_crBkgnd = m_btnBkClr.GetColor();
    m_crDownloadedOutline = m_btnDownloadedOutlineClr.GetColor();
    m_crRemainingOutline = m_btnRemainingOutlineClr.GetColor();
    m_crRemainingFill = m_btnRemainingFillClr.GetColor();

    if (CLR_DEFAULT == m_crBkgnd)
        m_crBkgnd = m_btnBkClr.GetDefaultColor();

    if (CLR_DEFAULT == m_crDownloadedOutline)
        m_crDownloadedOutline = m_btnDownloadedOutlineClr.GetDefaultColor();

    if (CLR_DEFAULT == m_crRemainingOutline)
        m_crRemainingOutline = m_btnRemainingOutlineClr.GetDefaultColor();

    if (CLR_DEFAULT == m_crRemainingFill)
        m_crRemainingFill = m_btnRemainingFillClr.GetDefaultColor();

    EndDialog(nID);
}

void CChooseColorsDlg::OnCancel(UINT uCode, int nID, HWND hwndCtrl)
{
    EndDialog(nID);
}
