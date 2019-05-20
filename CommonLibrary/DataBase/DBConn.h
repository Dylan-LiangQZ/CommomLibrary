#pragma once

#include <afx.h>
#include <string>
#include <vector>
#include "..\CommonLib.h"

#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF","adoEOF") rename("BOF","adoBOF")

class COMMON_DLL_SPEC CDBConn
{
protected:
	_ConnectionPtr   m_pConn;

	CString			m_szServerName;
	CString			m_szUser;
	CString			m_szPassword;

protected:
	CString			m_szLastErrInfo;

public:
	static CDBConn* Instance();
    
protected:
	CDBConn(void);
	~CDBConn(void);

public:
	BOOL InitDataBase(CString szDataBaseName);

	BOOL CreateTable(CString szTableName, const std::vector<CString>& TableColumnNameV);
	BOOL AddTableRecord(CString szTableName, const std::vector<CString>& TableColumnNameV, const std::vector<CString>& TableRowDataV);
	BOOL AlterTableRecord(CString szTableName, const std::vector<CString>& TableColumnNameV, const std::vector<CString>& TableRowDataV, CString szConditionSQLCmd);

	CString GetLastErrInfo() { return m_szLastErrInfo; }

public: // SQL inquiry 
	BOOL SQLCommandQuery(CString szTableName, CString szSQLCmd, _RecordsetPtr& pRecordset);
};