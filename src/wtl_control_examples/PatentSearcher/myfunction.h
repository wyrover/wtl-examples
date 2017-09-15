#ifndef LRUNSQL
#define LRUNSQL


class LRunSql
{
public:
    LRunSql();
    ~LRunSql();
    bool RunSQL(CString sql);
    bool CheckSQLResult(CString sql);
public:
    static _ConnectionPtr m_database;

    static bool RollbackTrans();
    static bool CommitTrans();
    static bool BeginTrans();
    static bool Close();
    static bool InitConnectPtr();
    static bool ConnectDataBase();



    _RecordsetPtr m_recordset;
};



// _ConnectionPtr m_database;
#endif