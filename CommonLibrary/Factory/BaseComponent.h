#pragma once
#include "ObjectFactory.h"

class CBaseComponent;

class CComponentFactory
{
public:
	static CBaseComponent* CreateComponet(CString szComponentName)
	{
		CBaseComponent* pComponent = NULL;
		pComponent = static_cast<CBaseComponent*>(CObjectFactory::CreateObject(szComponentName));
		return pComponent;
	}
};


class CBaseComponent
{
public:
	CBaseComponent();
	virtual ~CBaseComponent();
	virtual CBaseComponent* CreateComponent() = 0;

	virtual BOOL Start()=0;

private:
	static	CClassInfo*		m_classinfo;
};

