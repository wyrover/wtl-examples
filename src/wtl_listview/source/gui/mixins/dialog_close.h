/*
    @author Ilnaz Nizametdinov

    @project HelloYandex

    @description
        Implementation of the closable dialog window.
 */

#ifndef __GUI_MIXINS_CLOSABLE_DLG_H__
#define __GUI_MIXINS_CLOSABLE_DLG_H__

template <class T>
class CDialogClose
{
public:
    BEGIN_MSG_MAP(CDialogClose)
    MESSAGE_HANDLER(WM_SYSCOMMAND, OnSysCommand)
    END_MSG_MAP()

    LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        if (SC_CLOSE == wParam) {
            PostQuitMessage(WM_QUIT);
        }

        // Process default action
        bHandled = FALSE;
        return 0;
    }
};

#endif // __GUI_MIXINS_CLOSABLE_DLG_H__
