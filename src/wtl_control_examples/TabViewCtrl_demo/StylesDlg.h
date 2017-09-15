// StylesDlg.h: interface for the CStylesDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STYLESDLG_H__F0F278A6_7120_4A60_8E85_AA526292F490__INCLUDED_)
#define AFX_STYLESDLG_H__F0F278A6_7120_4A60_8E85_AA526292F490__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000

#include "resource.h"


//==============================================================================
// Style List
//==============================================================================

typedef struct _TStyleEntry {
    LONG m_Flag;
    LONG m_ControlId;

}  TStyleEntry;

const TStyleEntry g_StyleList[] = {
    { TCS_BOTTOM, IDC_TCS_BOTTOM },
    { TCS_BUTTONS, IDC_TCS_BUTTONS },
    { TCS_FIXEDWIDTH, IDC_TCS_FIXEDWIDTH },
    { TCS_FLATBUTTONS, IDC_TCS_FLATBUTTONS },
    { TCS_FOCUSNEVER, IDC_TCS_FOCUSNEVER },
    { TCS_FOCUSONBUTTONDOWN, IDC_TCS_FOCUSONBUTTONDOWN },
    { TCS_FORCEICONLEFT, IDC_TCS_FORCEICONLEFT },
    { TCS_FORCELABELLEFT, IDC_TCS_FORCELABELLEFT },
    { TCS_HOTTRACK, IDC_TCS_HOTTRACK },
    { TCS_MULTILINE, IDC_TCS_MULTILINE },
    { TCS_MULTISELECT, IDC_TCS_MULTISELECT },
    { TCS_OWNERDRAWFIXED, IDC_TCS_OWNERDRAWFIXED },
    { TCS_RAGGEDRIGHT, IDC_TCS_RAGGEDRIGHT },
    { TCS_RIGHT, IDC_TCS_RIGHT },
    { TCS_RIGHTJUSTIFY, IDC_TCS_RIGHTJUSTIFY },
    { TCS_SCROLLOPPOSITE, IDC_TCS_SCROLLOPPOSITE },
    { TCS_SINGLELINE, IDC_TCS_SINGLELINE },
    { TCS_TABS, IDC_TCS_TABS },
    { TCS_TOOLTIPS, IDC_TCS_TOOLTIPS },
    { TCS_VERTICAL, IDC_TCS_VERTICAL },
};

const LONG g_StyleListLength = sizeof(g_StyleList) / sizeof(TStyleEntry);


//==============================================================================
/**
 *      @class CStylesDlg   This dialog sets all tabs control styles.
 *
 *      This dialog contains a set of check boxes that represent the style
 *      bits of a tab control. The Apply and OK buttons return the new
 *      style bit settings through the OnStyleApply method of the CStylesBridge
 *      class.  This class does not try to manage settings for styles that
 *      are mutually exclusive, incompatible or require other styles to
 *      function properly.
 */
//==============================================================================
class CStylesDlg: public CDialogImpl<CStylesDlg>
{
    // Internal Classes
public:

    class CStylesBridge
    {
    public:
        virtual void OnStyleApply(ULONG inAddStyleBits, ULONG inRemoveStyleBits, ULONG* outNewStyleBits) = 0;
    };

    // Field Variables
protected:

    ULONG           m_StyleBits;        ///< The current styles
    ULONG           m_AddStyleBits;     ///< The styles to add
    ULONG           m_RemoveStyleBits;  ///< The styles to remove
    CStylesBridge*  m_StylesBridge;     ///< The callback bridge for changes


    // Constructors
public:

    CStylesDlg(ULONG inStyleBits, CStylesBridge* inStyleBridge = NULL) :
        m_StyleBits(inStyleBits),
        m_StylesBridge(inStyleBridge),
        m_AddStyleBits(0),
        m_RemoveStyleBits(0)
    { }

    virtual ~CStylesDlg() { }

    // WTL Stuff
public:

    enum { IDD = IDD_STYLES_DIALOG };

protected:

    BEGIN_MSG_MAP(CAboutDlg)
    MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
    COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
    COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
    COMMAND_ID_HANDLER(IDAPPLY, OnApply)
    END_MSG_MAP()

    // Implementation
protected:

    void CalcStyleChanges()
    {
        m_AddStyleBits = 0;
        m_RemoveStyleBits = 0;

        for (LONG theIndex = 0; theIndex < g_StyleListLength; theIndex++) {
            if (IsDlgButtonChecked(g_StyleList[ theIndex ].m_ControlId)) {
                if (m_StyleBits & g_StyleList[ theIndex ].m_Flag) {
                    // Do nothing, no change
                } else {
                    m_AddStyleBits |= g_StyleList[ theIndex ].m_Flag;
                }
            } else {
                if (m_StyleBits & g_StyleList[ theIndex ].m_Flag) {
                    m_RemoveStyleBits |= g_StyleList[ theIndex ].m_Flag;
                } else {
                    // Do nothing, no change
                }
            }
        }
    }

    void UpdateStyleCheckBoxes()
    {
        for (LONG theIndex = 0; theIndex < g_StyleListLength; theIndex++) {
            if (g_StyleList[ theIndex ].m_Flag & m_StyleBits) {
                CheckDlgButton(g_StyleList[ theIndex ].m_ControlId, BST_CHECKED);
            }
        }
    }

    LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        CenterWindow(GetParent());
        UpdateStyleCheckBoxes();
        return TRUE;
    }

    LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        if (wID == IDOK) {
            CalcStyleChanges();

            if (m_StylesBridge != NULL) {
                m_StylesBridge->OnStyleApply(m_AddStyleBits, m_RemoveStyleBits, &m_StyleBits);
            }
        }

        EndDialog(wID);
        return 0;
    }

    LRESULT OnApply(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        CalcStyleChanges();

        if (m_StylesBridge != NULL) {
            m_StylesBridge->OnStyleApply(m_AddStyleBits, m_RemoveStyleBits, &m_StyleBits);
        }

        UpdateStyleCheckBoxes();
        return 0;
    }
};

#endif // !defined(AFX_STYLESDLG_H__F0F278A6_7120_4A60_8E85_AA526292F490__INCLUDED_)
