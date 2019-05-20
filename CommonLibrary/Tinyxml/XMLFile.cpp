
#include "XMLFile.h"


CXMLElementHandle::CXMLElementHandle(TiXmlNode* _node)
	                 :TiXmlHandle(_node)
{
}


CXMLElementHandle::~CXMLElementHandle()
{
}


CXMLElementHandle::CXMLElementHandle(TiXmlHandle& ref)
	                 :TiXmlHandle(ref)
{
}


CXMLElementHandle& CXMLElementHandle::operator=( const CXMLElementHandle& ref)
{
	return *this;
}


CXMLElementHandle CXMLElementHandle::operator [](const CString& szKey)
{
	TiXmlNode* pChildNode =  FirstChild(szKey).ToNode();
	if (!pChildNode)
	{
		TiXmlNode* pNode = Node();
		if (pNode)
		{
			TiXmlElement* pElement = new TiXmlElement(szKey);
			pNode->LinkEndChild(pElement);
		}
	}

	return CXMLElementHandle(FirstChild(szKey));
}


CXMLElementHandle CXMLElementHandle::AddChild(const CString& szChild)
{
	TiXmlNode* pNode = Node();
	if (pNode)
	{
		TiXmlElement* pElement = new TiXmlElement(szChild);
		pNode->LinkEndChild(pElement);

		return CXMLElementHandle(pElement);
	}
	else
	{
		return *this;
	}
}


void CXMLElementHandle::GetStr(const CString& szKey, CString& szValue)
{
	TiXmlElement* element = ToElement();

	if (element)
	{
		CString szAttr;
		szAttr = element->Attribute(szKey);

		if (szAttr.GetLength()) // check if has this attr or not
		{
			szValue = szAttr;
		}
	}
}


void CXMLElementHandle::SetStr(const CString& szKey, const CString szValue)
{
	TiXmlElement* element = ToElement();

	if (element)
	{
		element->SetAttribute(szKey, szValue);
	}
};
	        

void CXMLElementHandle::GetInt(const CString& szKey, int& nValue)
{
	TiXmlElement* element = ToElement();

	if (element)
	{
		CString szAttr;
		szAttr = element->Attribute(szKey, &nValue);
	}
}


void CXMLElementHandle::SetInt(const CString& szKey, int nValue)
{
	TiXmlElement* element = ToElement();

	if (element)
	{
		element->SetAttribute(szKey, nValue);
	}
}


void CXMLElementHandle::GetDouble(const CString& szKey, double& dValue)
{
	TiXmlElement* element = ToElement();

	if (element)
	{
		CString szAttr;
		szAttr = element->Attribute(szKey, &dValue);
	}
}


void CXMLElementHandle::SetDouble(const CString& szKey, double dValue)
{
	TiXmlElement* element = ToElement();

	if (element)
	{
		element->SetDoubleAttribute(szKey, dValue);
	}
}


CXMLElementHandle CXMLElementHandle::AddText(const CString& szText)
{
	TiXmlNode* pNode = Node();
	if (pNode)
	{
		TiXmlText* pTiXmlText = new TiXmlText(szText);
		pNode->LinkEndChild(pTiXmlText);

		return CXMLElementHandle(pTiXmlText);
	}
	else
	{
		return *this;
	}
}



//////////////////////////////////////////////////////////////////////////////////////



CXMLFile::CXMLFile(const CString szRootElement)
	        :m_szRootElement(szRootElement)
{
	TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "", "");
	TiXmlElement* TopElement = new TiXmlElement(m_szRootElement);
	m_doc.LinkEndChild(decl);
	m_doc.LinkEndChild(TopElement);
}


CXMLFile::~CXMLFile()
{
}


int CXMLFile::Load(const CString& szFile)
{
	m_doc.LoadFile(szFile);
	
	return 0;
}


int CXMLFile::Save(const CString& szFile)
{
	m_doc.SaveFile(szFile);

	return 0;
}


TiXmlElement* CXMLFile::Root()
{
	return m_doc.RootElement();
}
