

    Gui, +LastFound
    guiID := WinExist()
    Gui, Color, EEAA99
    Gui, Margin, 0, 0
    Gui, Show, x0 y0 w500 h500, AniGif demo 
    global maindlg_hwnd := CreateMainDlg(guiID, 0, 0, 500, 500)
    If maindlg_hwnd is not integer
        MsgBox %maindlg_hwnd%

    OnMessage(0x0003, "WM_MOVE")
return

GuiClose:    
    ;DestoryMainDlg(maindlg_hwnd)
    GoSub, _Exit
return

_Exit:
    ExitApp
return


WM_MOVE(wParam, lParam, nMsg, hWnd)
{
    ;MsgBox, 111
}

CreateMainDlg(parent_hwnd, x, y, w, h)
{
    static first_call := true
    local hModule, maindlg_hwnd
    if (first_call) {
        first_call := false
        hModule := DllCall("LoadLibrary", "Str", "wtl_windows_dll.dll")
        if (!hModule) {
            ExitApp    
        }
    }

    maindlg_hwnd := DLLCall("wtl_windows_dll.dll\init_maindlg", "UInt", parent_hwnd, "Int", x, "Int", y, "Int", w, "Int", h)

    if (ErrorLevel != 0 or maindlg_hwnd = 0) {
        return 0
    }

    return maindlg_hwnd
}

DestoryMainDlg(hwnd)
{
    if (hwnd != 0) {
        DllCall("DestroyWindow", "UInt", hwnd)
    }
}
