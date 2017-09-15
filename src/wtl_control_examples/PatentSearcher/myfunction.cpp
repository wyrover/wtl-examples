#include "stdafx.h"
#include "myfunction.h"

_ConnectionPtr LRunSql::m_database;
HANDLE    hIOMutex = CreateMutex(NULL, FALSE, NULL);

//CRITICAL_SECTION sqlcsLock ;//互斥锁

LRunSql::LRunSql()
{
//  m_recordset.CreateInstance("ADODB.Recordset");
    m_recordset.CreateInstance(__uuidof(Recordset));
}
LRunSql::~LRunSql()
{
    ::CoUninitialize();
}

bool LRunSql::RunSQL(CString sql)
{
    try {
        WaitForSingleObject(hIOMutex, INFINITE);
        //::EnterCriticalSection( &sqlcsLock );
        m_recordset = m_database->Execute(_bstr_t(sql), NULL, adCmdText);
        ReleaseMutex(hIOMutex);
        //::LeaveCriticalSection( &sqlcsLock );
    } catch (_com_error& e) {
        ErrorsPtr pErrors = m_database->GetErrors();

        if (pErrors->GetCount() == 0) {
//          afxDump<<e.ErrorMessage();
        } else {
            for (int i = 0; i < pErrors->GetCount(); i++) {
                _bstr_t desc = pErrors->GetItem((long)i)->GetDescription();
//              afxDump<<(char*)desc;
            }
        }

        ReleaseMutex(hIOMutex);
        return false;
    }

    return true;
}
bool LRunSql::CheckSQLResult(CString sql)
{
    if (!this->RunSQL(sql))
        return false;
    else {
        if (!this->m_recordset->adoEOF)
            return true;
        else
            return false;
    }

    return true;
}

bool LRunSql::ConnectDataBase()
{
    try {
        // 获得当前路径
        TCHAR szFilePath[MAX_PATH + 1];
        GetModuleFileName(NULL, szFilePath, MAX_PATH);
        (_tcsrchr(szFilePath, _T('\\')))[1] = 0;
        CString currentPath = szFilePath;
        CString connect_string = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + currentPath + "data.mdb";
        m_database->Open((_bstr_t)connect_string, "", "", adModeUnknown);
    } catch (...) {
        //::ShellExecute(NULL,"open","AutoConfig.exe",NULL,NULL,SW_HIDE);
        return false;
    }

    return true;
}

bool LRunSql::InitConnectPtr()
{
    ::CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

    if (FAILED(m_database.CreateInstance(__uuidof(Connection))))
        return false;

    if (ConnectDataBase() == false) {
        //::Sleep(100);
        if (ConnectDataBase() == false) {
            MessageBox(NULL, L"数据库连接失败！", L"系统提示", MB_OK | MB_ICONSTOP);
            return false;
        }
    }

    return true;
}

bool LRunSql::Close()
{
    return (!FAILED(m_database->Close()));
}

bool LRunSql::BeginTrans()
{
    return (!FAILED(m_database->BeginTrans()));
}

bool LRunSql::CommitTrans()
{
    return (!FAILED(m_database->CommitTrans()));
}
bool LRunSql::RollbackTrans()
{
    return (!FAILED(m_database->RollbackTrans()));
}
