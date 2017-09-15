// stdafx.cpp : source file that includes just the standard includes
//  Kibbles.pch will be the pre-compiled header
//  stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

#if (_ATL_VER < 0x0700)
    #include <atlimpl.cpp>
#endif //(_ATL_VER < 0x0700)

#if !defined(UNICODE) || !defined(_UNICODE)
    #error This program is written to be built as Unicode only.
#endif

/////////////////////////////////////////////////////////////////////////////

CUrlComponents::CUrlComponents()
{
    ZeroMemory(this, sizeof(this));
    dwStructSize      = sizeof(URL_COMPONENTS);
    lpszScheme        = szScheme;
    dwSchemeLength    = countof(szScheme);
    lpszHostName      = szHostName;
    dwHostNameLength  = countof(szHostName);
    lpszUserName      = szUserName;
    dwUserNameLength  = countof(szUserName);
    lpszPassword      = szPassword;
    dwPasswordLength  = countof(szPassword);
    lpszUrlPath       = szUrlPath;
    dwUrlPathLength   = countof(szUrlPath);
    lpszExtraInfo     = szExtraInfo;
    dwExtraInfoLength = countof(szExtraInfo);
}

CUrlComponents::~CUrlComponents()
{
    SecureZeroMemory(szUserName, sizeof(szUserName));
    SecureZeroMemory(szPassword, sizeof(szPassword));
}

/////////////////////////////////////////////////////////////////////////////

void CErrorDesc::CommonConstruct()
{
    LPVOID lpMsgBuf;
    CString sDesc;
    HMODULE hmodQmgr = NULL;
    DWORD dwRet;
    DWORD dwFlags = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
                    FORMAT_MESSAGE_IGNORE_INSERTS;
    // If qmgr.dll is loaded, we'll pass its handle to FormatMessage() so it
    // looks in qmgr's message table for error descriptions. If it's not loaded,
    // then GetModuleHandle() returns NULL, which is passed on to FormatMessage(),
    // which is the correct behavior.
    hmodQmgr = GetModuleHandle(_T("qmgr"));

    if (NULL != hmodQmgr)
        dwFlags |= FORMAT_MESSAGE_FROM_HMODULE;

    dwRet = FormatMessage(dwFlags, hmodQmgr, m_dwError,
                          m_langid, (LPTSTR) &lpMsgBuf, 0, NULL);

    if (0 == dwRet) {
        // FormatMessage() failed, if the error code is a failure HRESULT, try
        // to get a description of the Win32 error instead.
        if (FAILED(m_dwError) &&
            HRESULT_FACILITY(m_dwError) == FACILITY_WIN32) {
            dwRet = FormatMessage(dwFlags, hmodQmgr, HRESULT_CODE(m_dwError),
                                  m_langid, (LPTSTR) &lpMsgBuf, 0, NULL);
        }
    }

    sDesc = (LPCTSTR) lpMsgBuf;
    sDesc.TrimRight();
    LocalFree(lpMsgBuf);
    m_sDesc.Format(_T("0x%08X [%s]"), m_dwError, (LPCTSTR) sDesc);
}
