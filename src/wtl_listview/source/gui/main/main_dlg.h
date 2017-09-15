/*
    @author Ilnaz Nizametdinov

    @project HelloYandex

    @description
        Interface of the CMainDlg class.
 */

#ifndef __GUI_MAIN_DLG_H__
#define __GUI_MAIN_DLG_H__

#include "gui/mixins/wnd_icon.h"
#include "gui/mixins/dialog_close.h"
#include "gui/controls/custom_list.h"

class CMainDlg : public CDialogImpl<CMainDlg>,
    public CWindowIcon<CMainDlg, IDI_MAIN>,
    public CDialogClose<CMainDlg>,
    public CDialogResize<CMainDlg>
{
    typedef CDialogClose<CMainDlg> CDialogCloseBase;
    typedef CDialogResize<CMainDlg> CDialogResizeBase;

public:
    enum { IDD = IDD_MAIN };

    BEGIN_MSG_MAP(CMainDlg)
    MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
    COMMAND_ID_HANDLER(IDADD, OnAdd)
    COMMAND_ID_HANDLER(IDDEL, OnDelete)
    CHAIN_MSG_MAP(CDialogCloseBase)
    CHAIN_MSG_MAP(CDialogResizeBase)
    REFLECT_NOTIFICATIONS() // need for OwnerDraw
    END_MSG_MAP()

    BEGIN_DLGRESIZE_MAP(CMainDlg)
    DLGRESIZE_CONTROL(IDC_LIST, DLSZ_SIZE_X | DLSZ_SIZE_Y)
    DLGRESIZE_CONTROL(IDADD, DLSZ_MOVE_Y)
    DLGRESIZE_CONTROL(IDDEL, DLSZ_MOVE_Y)
    END_DLGRESIZE_MAP()

    LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnAdd(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
    LRESULT OnDelete(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

    // Helper function
    void AddRow(int nItem);

protected:
    CCustomListCtrl _list;
};

#endif // __GUI_MAIN_DLG_H__
