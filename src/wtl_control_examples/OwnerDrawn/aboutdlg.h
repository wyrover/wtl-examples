// aboutdlg.h : interface of the CAboutDlg class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ABOUTDLG_H__2F32A889_12AC_4F7A_B81D_5E994A837A51__INCLUDED_)
#define AFX_ABOUTDLG_H__2F32A889_12AC_4F7A_B81D_5E994A837A51__INCLUDED_

class CAboutDlg : public CDialogImpl<CAboutDlg>
{
public:
    enum { IDD = IDD_ABOUTBOX };

    BEGIN_MSG_MAP(CAboutDlg)
    MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
    COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
    COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
    END_MSG_MAP()

    LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        CenterWindow(GetParent());
        return TRUE;
    }

    LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        EndDialog(wID);
        return 0;
    }
};

#endif // !defined(AFX_ABOUTDLG_H__2F32A889_12AC_4F7A_B81D_5E994A837A51__INCLUDED_)
