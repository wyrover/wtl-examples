// SkinManager.h: interface for the CSkinManager class.
//
//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
//
// SkinManager.h
// 版权所有：G-Net
// 作者：XuYu
// 创建日期：2007-5-28
// 更新日期：2007-5-28
// 描述：皮肤管理器。用于初始化皮肤参数文件路径，输出皮肤参数等操作。
// 更新记录：
//  2007-5-28 - 创建了基本的功能
//
///////////////////////////////////////////////////////////////////
#if !defined(AFX_SKINMANAGER_H__5239F6E5_2013_4928_9160_4B9598B35F9C__INCLUDED_)
#define AFX_SKINMANAGER_H__5239F6E5_2013_4928_9160_4B9598B35F9C__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000


class CSkinManager
{
public:
    CSkinManager();
    virtual ~CSkinManager();

    static CSkinManager* Init(LPCTSTR lpctSkinName = NULL);
    BOOL ChangeSkin(LPCTSTR lpctSkinName);
    COLORREF GetColor(LPCTSTR lpctSection, LPCTSTR lpctKey, COLORREF clrDefault);
    DWORD GetPicturePath(LPCTSTR lpctSection, LPCTSTR lpctKey, LPTSTR lptValue, int iValueLen, LPCTSTR lpctDefault = NULL);
    int GetInt(LPCTSTR lpctSection, LPCTSTR lpctKey, int iDefault);
    BOOL GetBool(LPCTSTR lpctSection, LPCTSTR lpctKey, BOOL bDefault = TRUE);
    LPCTSTR GetCurrentSkinName();

private:
    static CIni m_skinINI;              //皮肤参数INI文件
    static CSkinManager* m_pInstance;   //唯一实例句柄
    static CString m_pszCurrentSkin;    //当前皮肤名称

};

#endif // !defined(AFX_SKINMANAGER_H__5239F6E5_2013_4928_9160_4B9598B35F9C__INCLUDED_)
