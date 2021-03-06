/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED 'AS IS' WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.
   Author: Leon Finker  7/2003
**************************************************************************/

// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "resource.h"

#include "MainDlg.h"
#include "maindlg.h"
#include ".\maindlg.h"

#define RETURN_ON_ERROR(hr) if(hr != S_OK) { check_last_error();  return 0;}

const int MAX_PASS_LEN = 256;

void check_last_error()
{
	LPVOID lpMsgBuf;
	if (!FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR) &lpMsgBuf, 0, NULL ))
	{
		return;
	}
	MessageBox( NULL, (LPCTSTR)lpMsgBuf, _T("Error"), MB_OK | MB_ICONINFORMATION );
	LocalFree( lpMsgBuf );
}

LRESULT CMainDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// center the dialog on the screen
	CenterWindow();

	// set icons
	HICON hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
		IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
	SetIcon(hIcon, TRUE);
	HICON hIconSmall = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
		IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
	SetIcon(hIconSmall, FALSE);

	GetDlgItem(IDC_EDIT_PASSWORD1).SendMessage(EM_LIMITTEXT,MAX_PASS_LEN,0);
	GetDlgItem(IDC_EDIT_PASSWORD2).SendMessage(EM_LIMITTEXT,MAX_PASS_LEN,0);
	
	GetDlgItem(IDC_EDIT_OUTFILE).SendMessage(EM_LIMITTEXT,MAX_PATH,0);

	CString sFileName;
	if(GetModuleFileName(NULL, sFileName.GetBufferSetLength(MAX_PATH+1), MAX_PATH) == 0)
		return 0;
	int nPos = sFileName.ReverseFind(_T('\\'));
	if(nPos == -1)
		return 0;
	sFileName.Delete(nPos, sFileName.GetLength() - nPos);
	sFileName += _T("\\decr.exe");

	SetDlgItemText(IDC_EDIT_OUTFILE, (LPCTSTR)sFileName);

	SendDlgItemMessage(IDC_COMBO_ALGID, CB_ADDSTRING, 0, (LPARAM)_T("3DES"));
	SendDlgItemMessage(IDC_COMBO_ALGID, CB_ADDSTRING, 0, (LPARAM)_T("AES_256"));
	SendDlgItemMessage(IDC_COMBO_ALGID, CB_SETCURSEL, 0, 0);

	return TRUE;
}

LRESULT CMainDlg::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CSimpleDialog<IDD_ABOUTBOX, FALSE> dlg;
	dlg.DoModal();
	return 0;
}

LRESULT CMainDlg::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	EndDialog(wID);
	return 0;
}

LRESULT CMainDlg::OnBnClickedEncrypt(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CString sFileName;
	if(GetDlgItemText(IDC_EDIT_OUTFILE, sFileName) == 0 || sFileName.IsEmpty())
	{
		MessageBox(_T("Please set output file path"), _T("Error"), MB_OK|MB_ICONERROR);
		GetDlgItem(IDC_EDIT_OUTFILE).SetFocus();
		return 0;
	}
	CFileDialog dlgOpen(TRUE, 0, 0, OFN_HIDEREADONLY|OFN_EXPLORER|OFN_ENABLESIZING, _T("All Files (*.*)\0*.*\0"));
	if(dlgOpen.DoModal() != IDOK)
		return 0;

	CWaitCursor waitcur;
	CString sAlgID(_T("3DES"));
	GetDlgItemText(IDC_COMBO_ALGID, sAlgID);
	DWORD dwProviderType = PROV_RSA_FULL;
	LPCTSTR szProvider   = MS_ENHANCED_PROV;
	ALG_ID	algid = CALG_3DES;
	if(sAlgID == _T("3DES"))
	{
		dwProviderType = PROV_RSA_FULL;
		szProvider     = MS_ENHANCED_PROV;
		algid = CALG_3DES;
		sAlgID = _T("1");
	}
	else if(sAlgID == _T("AES_256"))
	{
		dwProviderType = PROV_RSA_AES;
		szProvider     = MS_ENH_RSA_AES_PROV;
		algid          = CALG_AES_256;
		sAlgID = _T("2");
	}
	else
		return 0;

	CCryptProv prov;
	HRESULT hr = prov.Initialize(dwProviderType, NULL, szProvider);
	if(hr == NTE_BAD_KEYSET)
		hr = prov.Initialize(dwProviderType, NULL, szProvider, CRYPT_NEWKEYSET);
	RETURN_ON_ERROR(hr);
	
	CCryptDerivedKey derKey;
    CCryptSHAHash sha;
    hr = sha.Initialize(prov);
	RETURN_ON_ERROR(hr);
    
	HWND hWndPwd1 =  ::GetDlgItem(m_hWnd, IDC_EDIT_PASSWORD1);
	HWND hWndPwd2 =  ::GetDlgItem(m_hWnd, IDC_EDIT_PASSWORD2);
	if(!hWndPwd1 || !hWndPwd2)
		return 0;

	TCHAR pPass1[MAX_PASS_LEN], 
		  pPass2[MAX_PASS_LEN];
	int  nPass1 = ::GetWindowText(hWndPwd1, pPass1, MAX_PASS_LEN);
	int  nPass2 = ::GetWindowText(hWndPwd2, pPass2, MAX_PASS_LEN);
	::SetWindowText(hWndPwd1, _T("********************"));
	::SetWindowText(hWndPwd2, _T("********************"));
	::SetWindowText(hWndPwd1, _T(""));
	::SetWindowText(hWndPwd2, _T(""));

	if(nPass1 < 8)
	{
		MessageBox(_T("Password must be 8 characters minimum"), _T("Error"), MB_OK|MB_ICONERROR);
		return 0;
	}
	if(nPass1 != nPass2 || memcmp(pPass1, pPass2, nPass1*sizeof(TCHAR)) != 0)
	{
		MessageBox(_T("Please Enter Identical Passwords"), _T("Error"), MB_OK|MB_ICONERROR);
		return 0;
	}

	hr = sha.AddData((BYTE*)pPass1, nPass1*sizeof(TCHAR));
	RETURN_ON_ERROR(hr);
	SecureZeroMemory(pPass1, MAX_PASS_LEN*sizeof(TCHAR));
	SecureZeroMemory(pPass2, MAX_PASS_LEN*sizeof(TCHAR));
	BYTE noise[] ={ 0xca, 0xed, 0x87, 0xfb, 0x92, 0x61, 0xa3, 0x09, 0x41, 0x0d, 0xaf, 0xbc, 0x9d, 
		            0x02, 0x42, 0x79, 0x7a, 0x50, 0x56, 0xd5, 0xa1, 0x56, 0x60, 0x1f, 0xaf, 0x42, 
					0x7f, 0x26, 0xc7, 0x81, 0xa3, 0x97, 0xe6, 0xae, 0xba, 0xba, 0x57, 0xfd, 0x0a, 
					0x35, 0xed, 0xca, 0x37, 0x4d, 0xdf, 0x78, 0xb9, 0xd6, 0xd0, 0x29, 0x55, 0xe7, 
					0xa7, 0x13, 0xec, 0xbf, 0x97, 0x81, 0x1a, 0x86};
	hr = sha.AddData(noise, sizeof(noise));
	RETURN_ON_ERROR(hr);

	BYTE tmpHash[20];
	DWORD dw=sizeof(tmpHash);
	for(int i=0; i<101; ++i)
	{
		hr = sha.GetValue(tmpHash, &dw);
		RETURN_ON_ERROR(hr);
		sha.Destroy();
		hr = sha.Initialize(prov);
		RETURN_ON_ERROR(hr);
		hr = sha.AddData(tmpHash, dw);
		RETURN_ON_ERROR(hr);
	}
	SecureZeroMemory(tmpHash, dw);

	hr = derKey.Initialize(prov,sha,algid);
	RETURN_ON_ERROR(hr);

    BYTE iv[16];
    hr = prov.GenRandom(16, iv);
    RETURN_ON_ERROR(hr);
    hr = derKey.SetIV(iv);
    RETURN_ON_ERROR(hr);
    hr = derKey.SetMode(CRYPT_MODE_CBC);
    RETURN_ON_ERROR(hr);
    hr = derKey.SetPadding(PKCS5_PADDING);
    RETURN_ON_ERROR(hr);

	HRSRC res = FindResource(NULL, MAKEINTRESOURCE(IDR_DUMMY), _T("dummy"));
	if(!res)
		return 0;
	HGLOBAL hGlobal = LoadResource(NULL, res);
	if(!hGlobal)
		return 0;
	int resLen = SizeofResource(NULL, res);
	void* buf = LockResource(hGlobal);
	if(!buf || resLen <= 0)
		return 0;

	FILE* file = _tfopen((LPCTSTR)sFileName, _T("wb"));
	if(!file)
		return 0;
	int nWritten = fwrite(buf, 1, resLen, file);
	fclose(file);
	if(nWritten != resLen)
		return 0;

	BOOL bRet = FALSE;
	HANDLE hUpdateRes = BeginUpdateResource(sFileName, FALSE);
	if(dlgOpen.m_szFileName[0] != '\0')
	{
		CAtlFile file;
		if(file.Create(dlgOpen.m_szFileName,GENERIC_READ, 0, OPEN_EXISTING) != S_OK)
		{
			MessageBox(_T("File Access Failed"), _T("Error"), MB_OK|MB_ICONERROR);
		}
		else
		{
			unsigned long long tempSize = 0;
			if(file.GetSize(tempSize) != S_OK || (tempSize >> 32) != 0) //UpdateResource takes DWORD
			{
				MessageBox(_T("File Access Failed"), _T("Error"), MB_OK|MB_ICONERROR);
			}
			else
			{
				DWORD dwFileSize = (DWORD)tempSize;
				CAtlFileMapping<char> filemap;
				HRESULT hrMap = filemap.MapFile(file, 0, 0, PAGE_READONLY, FILE_MAP_READ);
				CHeapPtr<char, CComAllocator> data;
				DWORD blocksize = 72;
				derKey.Encrypt(TRUE, NULL, &blocksize, 0);
				if(hrMap == S_OK && data.Allocate(dwFileSize + blocksize))
				{
					char* pMem = filemap;
					HRESULT hrEncr = E_FAIL;
					if(pMem)
					{
						memcpy(data.m_pData, pMem, dwFileSize);
						hrEncr = derKey.Encrypt(TRUE, (BYTE*)data.m_pData, &dwFileSize, dwFileSize + blocksize);
					}
					sha.Destroy();
					filemap.Unmap();
					file.Close();
					if(hrEncr != S_OK
						|| !UpdateResource(hUpdateRes, RT_RCDATA, _T("1"), MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), (void*)(LPCTSTR)sAlgID, sAlgID.GetLength()*sizeof(TCHAR))
						|| !UpdateResource(hUpdateRes, RT_RCDATA, _T("2"), MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), dlgOpen.m_szFileTitle, _tcslen(dlgOpen.m_szFileTitle)*sizeof(TCHAR))
						|| !UpdateResource(hUpdateRes, RT_RCDATA, _T("3"), MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), data.m_pData, dwFileSize)
                        || !UpdateResource(hUpdateRes, RT_RCDATA, _T("4"), MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), iv, sizeof(iv)))
					{
						check_last_error();
						MessageBox(_T("Failed to update resource"), _T("Error"), MB_OK|MB_ICONERROR);
					}
					else
						bRet = TRUE;
				}
			}
		}
	}
	if(EndUpdateResource(hUpdateRes, FALSE) && bRet)
		MessageBox(_T("Operation Successful"), _T("Info"), MB_OK|MB_ICONINFORMATION);

	::SetFocus(hWndPwd1);
	return 0;
}

LRESULT CMainDlg::OnBnClickedBtnOutfile(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CFolderDialog dlg;
	if(dlg.DoModal() == IDOK)
	{
		CString sFile = dlg.GetFolderPath();
		if(!sFile.IsEmpty())
		{
			if(sFile[sFile.GetLength()-1] != _T('\\'))
				sFile += _T('\\');
			SetDlgItemText(IDC_EDIT_OUTFILE, sFile + _T("decr.exe"));
		}
	}
	return 0;
}