#pragma once

#include "DBConn.h"
#include "..\Tinyxml\tinyxml.h"

CDBConn::CDBConn(void)
{
	m_pConn = NULL;
	m_szServerName = "142.252.252.98,1433";
	m_szUser = "sa";
	m_szPassword = "lm123654789";

	::CoInitialize(NULL);
}


CDBConn::~CDBConn(void)
{
	if (m_pConn != NULL)
	{
		m_pConn->Close();
		m_pConn = NULL;
	}

	::CoUninitialize();
}


CDBConn* CDBConn::Instance()
{
	static CDBConn instance;

    return &instance;  
}


BOOL CDBConn::InitDataBase(CString szDataBaseName)
{
	BOOL bReply = TRUE;

	try
	{
		                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
		CString szSql;

		HRESULT hRelt = m_pConn.CreateInstance("ADODB.Connection");
		if (SUCCEEDED(hRelt))
		{
			szSql.Format("Driver={SQL Server};Server=%s;Uid=%s;Pwd=%s;", m_szServerName , m_szUser, m_szPassword);
			hRelt = m_pConn->Open(_bstr_t(szSql), _bstr_t(m_szUser), _bstr_t(m_szPassword), adModeUnknown);
			bReply = SUCCEEDED(hRelt);
		}

		szSql.Format("IF NOT EXISTS (SELECT name FROM sys.databases WHERE name = N'%s') CREATE DATABASE %s", szDataBaseName, szDataBaseName);
		m_pConn->Execute(_bstr_t(szSql), NULL, adCmdText);
		m_pConn->Close();
		m_pConn = NULL; 

		// Open database
		hRelt = m_pConn.CreateInstance("ADODB.Connection");
		if (SUCCEEDED(hRelt))
		{
			szSql.Format("Driver={SQL Server};Server=%s;Database=%s;Uid=%s;Pwd=%s;", m_szServerName, szDataBaseName, m_szUser, m_szPassword);
			hRelt = m_pConn->Open(_bstr_t(szSql), _bstr_t(m_szUser), _bstr_t(m_szPassword), adModeUnknown);

			bReply = SUCCEEDED(hRelt);
		}
	}
	catch (_com_error& e)
	{
		m_szLastErrInfo.Format("%s() Description: %s\n", __FUNCTION__, (LPCTSTR)e.Description());
		TRACE(m_szLastErrInfo);
	}

	return bReply;
}


BOOL CDBConn::CreateTable(CString szTableName, const std::vector<CString>& TableColumnNameV)
{
	try
	{
		CString szTemp;
		CString szSql;
		szSql.Format("IF OBJECT_ID('dbo.%s', 'U') IS NULL ", szTableName);
		szTemp.Format("CREATE TABLE [dbo].[%s](", szTableName);
		szSql += "BEGIN ";
		szSql += szTemp;

		auto iter = TableColumnNameV.begin();
		szTemp.Format("[%s] VARCHAR(50) NOT NULL,", *iter, *iter);
		szSql += szTemp;
		for (++iter; iter != TableColumnNameV.end(); ++iter)
		{
			szTemp.Format("[%s] VARCHAR(50),", *iter);
			szSql += szTemp;
		}
		szSql += ")";
		szSql += " END";
		m_pConn->Execute(_bstr_t(szSql), NULL, adCmdText);
	}
	catch (_com_error& e)
	{
		m_szLastErrInfo.Format("%s() Description: %s\n", __FUNCTION__, (LPCTSTR)e.Description());
		TRACE(m_szLastErrInfo);

		return FALSE;
	}

	return TRUE;
}


BOOL CDBConn::AddTableRecord(CString szTableName, const std::vector<CString>& TableColumnNameV, const std::vector<CString>& TableRowDataV)
{
	try
	{
		CString szSql;
		CString szLine1;
		CString szLine2;
		CString szLine3;
		CString szTitle;
		CString szValue;
		szLine1.Format("INSERT INTO [dbo].[%s] ", szTableName);

		auto iterColumV = TableColumnNameV.begin();
		for (; iterColumV != TableColumnNameV.end(); iterColumV++)
		{
			szTitle += *iterColumV;
			szTitle += ", ";
		}
		szTitle = szTitle.Left(szTitle.GetLength() - 2);
		szLine2.Format("(%s) ", szTitle);

		auto iterWaferInfoV = TableRowDataV.begin();
		for (; iterWaferInfoV != TableRowDataV.end(); iterWaferInfoV++)
		{
			CString sz;
			sz.Format("'%s'", *iterWaferInfoV);
			szValue += sz;
			szValue += ", ";
		}
		szValue = szValue.Left(szValue.GetLength() - 2);
		szLine3.Format("VALUES (%s)", szValue);
		szSql = szLine1 + szLine2 + szLine3;
		m_pConn->Execute(_bstr_t(szSql), NULL, adCmdText);
	}
	catch (_com_error& e)
	{
		m_szLastErrInfo.Format("%s() Description: %s\n", __FUNCTION__, (LPCTSTR)e.Description());
		TRACE(m_szLastErrInfo);

		return FALSE;
	}

	return TRUE;
}


BOOL CDBConn::SQLCommandExecute(CString szSQLCmd)
{
	try
	{
		m_pConn->Execute(_bstr_t(szSQLCmd), NULL, adCmdText);
	}
	catch (_com_error& e)
	{
		m_szLastErrInfo.Format("%s() Description: %s\n", __FUNCTION__, (LPCTSTR)e.Description());
		TRACE(m_szLastErrInfo);

		return FALSE;
	}
	
	return TRUE;
}


BOOL CDBConn::SQLCommandQuery(CString szSQLCmd, _RecordsetPtr& pRecordset)
{
	try
	{
		pRecordset.CreateInstance(_uuidof(Recordset));

		pRecordset->Open(_bstr_t(szSQLCmd), m_pConn.GetInterfacePtr(), adOpenStatic, adLockOptimistic, adCmdText);
	}
	catch (_com_error& e)
	{
		m_szLastErrInfo.Format("%s() Description: %s\n", __FUNCTION__, (LPCTSTR)e.Description());
		TRACE(m_szLastErrInfo);

		return FALSE;
	}

	return TRUE;
}


