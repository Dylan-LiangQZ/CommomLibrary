#pragma once

#include <afx.h>
#include "tinyxml.h"
#include <string>

#include "..\CommonLib.h"

class COMMON_DLL_SPEC CXMLElementHandle : public TiXmlHandle
{
public:
	CXMLElementHandle(TiXmlNode* _node);
	~CXMLElementHandle();

protected:
	CXMLElementHandle(TiXmlHandle& ref);
	CXMLElementHandle& operator=(const CXMLElementHandle& ref);

public:
	CXMLElementHandle operator [](const CString& szKey);
	CXMLElementHandle AddChild(const CString& szChild);
	void GetStr(const CString& szKey, CString& szValue);
	void SetStr(const CString& szKey, const CString szValue);
	void GetInt(const CString& szKey, int& nValue);
	void SetInt(const CString& szKey, int nValue);
	void GetDouble(const CString& szKey, double& dValue);
	void SetDouble(const CString& szKey, double dValue);

	CXMLElementHandle AddText(const CString& szText);
};


class COMMON_DLL_SPEC CXMLFile
{
protected:
	TiXmlDocument m_doc;
	CString		  m_szRootElement;

private:
	CXMLFile();

public:
	CXMLFile(const CString szRootElement);
	~CXMLFile();

public:
	int Load(const CString& szFile);
	int Save(const CString& szFile);

	TiXmlElement* Root();
};



inline std::wstring UTF8ToUTF16(const char *szIn)
{
	std::wstring strResult;

	if (szIn)
	{
		wchar_t *wszUTF16;
		int len = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)szIn, -1, NULL, 0);
		wszUTF16 = new wchar_t[len + 1];
		memset(wszUTF16, 0, len * 2 + 2);
		MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)szIn, -1, (LPWSTR)wszUTF16, len);
		strResult = std::wstring(wszUTF16);
		delete[]wszUTF16;
	}

	return strResult;
}

inline void GBKToUTF8(char* &szOut)
{
	char* strGBK = szOut;

	int len = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)strGBK, -1, NULL, 0);
	unsigned short * wszUtf8 = new unsigned short[len + 1];
	memset(wszUtf8, 0, len * 2 + 2);
	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)strGBK, -1, (LPWSTR)wszUtf8, len);

	len = WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)wszUtf8, -1, NULL, 0, NULL, NULL);
	char *szUtf8 = new char[len + 1];
	memset(szUtf8, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)wszUtf8, -1, szUtf8, len, NULL, NULL);

	//szOut = szUtf8;
	memset(szOut, '/0', strlen(szUtf8) + 1);
	memcpy(szOut, szUtf8, strlen(szUtf8) + 1);

	delete[] szUtf8;
	delete[] wszUtf8;
}
