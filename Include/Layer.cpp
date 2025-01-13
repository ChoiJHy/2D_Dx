#include "stdafx.h"
#include "Layer.h"

#include "GameObject.h"

CLayer::CLayer()
{
}


CLayer::~CLayer()
{
	list<CGameObject*>::iterator iter = m_listObj.begin();
	list<CGameObject*>::iterator iterEnd = m_listObj.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetTag() == L"Mouse")
			continue;
		SAFE_DELETE(*iter);
	}
}

void CLayer::AddGameObject(CGameObject * _pObj)
{
	if (_pObj == NULL)
		return;

	m_listObj.push_back(_pObj);
	_pObj->SetLayerName(m_strLayerName);

	if (_pObj->GetParent() == NULL)
		m_setParentObject.insert(_pObj);

	const list<CGameObject*>& objList = _pObj->GetChildList();
	list<CGameObject*>::const_iterator iter = objList.begin();
	for (; iter != objList.end(); ++iter)
		AddGameObject((*iter));
}

void CLayer::RemoveParent(CGameObject * _pObj)
{
	set<CGameObject*>::iterator iter = m_setParentObject.find(_pObj);
	if (iter != m_setParentObject.end())
	{
		m_setParentObject.erase(iter);
	}
}

void CLayer::Awake()
{
	set<CGameObject*>::iterator iter = m_setParentObject.begin();
	set<CGameObject*>::iterator iterEnd = m_setParentObject.end();
	for (; iter != iterEnd; ++iter)
	{
		(*iter)->Awake();
	}
}

void CLayer::Start()
{
	set<CGameObject*>::iterator iter = m_setParentObject.begin();
	set<CGameObject*>::iterator iterEnd = m_setParentObject.end();
	for (; iter != iterEnd; ++iter)
	{
		(*iter)->Start();
	}
}

int CLayer::Update()
{
	set<CGameObject*>::iterator iter = m_setParentObject.begin();
	set<CGameObject*>::iterator iterEnd = m_setParentObject.end();
	for (; iter != iterEnd; ++iter)
	{
		(*iter)->Update();
	}
	return 0;
}

int CLayer::LateUpdate()
{
	set<CGameObject*>::iterator iter = m_setParentObject.begin();
	set<CGameObject*>::iterator iterEnd = m_setParentObject.end();
	for (; iter != iterEnd; ++iter)
	{
		(*iter)->LateUpdate();
	}
	return 0;
}

void CLayer::Render()
{
	set<CGameObject*>::iterator iter = m_setParentObject.begin();
	set<CGameObject*>::iterator iterEnd = m_setParentObject.end();
	for (; iter != iterEnd; ++iter)
	{
		(*iter)->Render();
	}
}
