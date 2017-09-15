/*
    @author Ilnaz Nizametdinov

    @project HelloYandex

    @description
        –
 */

#ifndef __GUI_MIXINS_WND_ICON_H__
#define __GUI_MIXINS_WND_ICON_H__

template <class T, UINT uResID>
class CWindowIcon
{
public:
    void WindowIcon_Init()
    {
        T* _this = static_cast<T*>(this);
        HICON hIcon = LoadImage<HICON, IMAGE_ICON>(uResID, SM_CXICON, SM_CYICON);
        _this->SetIcon(hIcon, TRUE);
        HICON hIconSmall = LoadImage<HICON, IMAGE_ICON>(uResID, SM_CXSMICON, SM_CYSMICON);
        _this->SetIcon(hIconSmall, FALSE);
    }

    template<typename HImage, UINT TImage>
    static HImage LoadImage(UINT uResID, int smX, int smY, UINT uFlags = LR_DEFAULTCOLOR)
    {
        return LoadImage<HImage, TImage>(MAKEINTRESOURCE(uResID), smX, smY, uFlags);
    }

    template<typename HImage, UINT TImage>
    static HImage LoadImage(LPCTSTR name, int smX, int smY, UINT uFlags = LR_DEFAULTCOLOR)
    {
        HANDLE handle = ::LoadImage(
                            _Module.GetResourceInstance(),
                            name,
                            TImage,
                            ::GetSystemMetrics(smX), ::GetSystemMetrics(smY),
                            uFlags);
        return reinterpret_cast<HImage>(handle);
    }
};

#endif // __GUI_MIXINS_WND_ICON_H__
