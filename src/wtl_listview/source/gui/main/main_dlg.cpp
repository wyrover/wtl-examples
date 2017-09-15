/*
    @author Ilnaz Nizametdinov

    @project HelloYandex

    @description
        Implementation of the CMainDlg class.
 */

#include "stdafx.h"

#include "resource/resource.h"
#include "main_dlg.h"

#include <stdlib.h> // rand
#include <time.h>

// Global icon names
LPTSTR g_lpszNames[3] = { _TEXT("Поис"), _TEXT("Диск"), _TEXT("Деньги")};

LRESULT CMainDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    WindowIcon_Init();
    DlgResize_Init();
    CenterWindow();
    // Initialize random generator
    srand(static_cast<unsigned int>(time(NULL)));
    // Load button icons
    CButton buttonAdd = GetDlgItem(IDADD);
    CButton buttonDel = GetDlgItem(IDDEL);
    buttonAdd.SetIcon(LoadImage<HICON, IMAGE_ICON>(IDI_ADD, SM_CXSMICON, SM_CYSMICON));
    buttonDel.SetIcon(LoadImage<HICON, IMAGE_ICON>(IDI_DEL, SM_CXSMICON, SM_CYSMICON));
    // Initialize list with 4 columns...
    _list.SubclassWindow(GetDlgItem(IDC_LIST));
    _list.AddColumn(_TEXT("Column 1"), 0);
    _list.AddColumn(_TEXT("Column 2"), 1);
    _list.AddColumn(_TEXT("Column 3"), 2);
    _list.AddColumn(_TEXT("Column 4"), 3);

    // ... and 5 rows
    for (int i = 0; i < 5; ++i) {
        // Add row with random content
        AddRow(i);
    }

    _list.Update();
    // Force redraw to update the list
    DlgResize_UpdateLayout(0, 0);
    return TRUE;
}

LRESULT CMainDlg::OnAdd(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
    int nItem = _list.GetSelectedIndex();
    nItem = (-1 == nItem) ? _list.GetItemCount() : nItem + 1;
    // Add row with random content
    AddRow(nItem);
    // Update list
    _list.Update();
    _list.EnsureVisible(nItem, FALSE);
    return 0;
}

LRESULT CMainDlg::OnDelete(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
    int nItem = _list.GetSelectedIndex();

    if (-1 != nItem) {
        _list.DeleteItemMy(nItem);
        _list.Update();
    }

    return 0;
}

void CMainDlg::AddRow(int nItem)
{
    for (int j = 0; j < 4; ++j) {
        CCustomListCtrl::Item item;
        // Magic number for text/bmp selection
        int magic = rand() % 3;
        // Set text/bmp
        item.bText = rand() % 2;
        // Load bitmap & text
        item.hBmp  = LoadBitmap(
                         _Module.GetResourceInstance(),
                         MAKEINTRESOURCE(IDB_IMG_BASE + magic));
        item.lpszText = g_lpszNames[magic];
        // Add to list
        nItem = _list.AddItem(nItem, j, item);
    }
}
