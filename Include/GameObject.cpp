#include "stdafx.h"
#include "GameObject.h"


#include "Component.h"
#include "Renderer.h"



CGameObject::CGameObject()
{
	memset(m_arrComponent, 0, sizeof(void*) * COM_END);
}

CGameObject::CGameObject(const CGameObject & _Obj)
{
	m_strLayerName = _Obj.m_strLayerName;
	m_strTag = _Obj.m_strTag;

	memset(m_arrComponent, 0, sizeof(void*) * COM_END);

	for (int i = 0; i < COM_END; ++i)
	{
		if (NULL != _Obj.m_arrComponent[i])
		{
			m_arrComponent[i] = _Obj.m_arrComponent[i]->Clone();
			m_arrComponent[i]->SetGameObject(this);
		}
	}

	list<CScript*>::const_iterator iter = _Obj.m_listScript.begin();
	list<CScript*>::const_iterator iterEnd = _Obj.m_listScript.end();

	for (; iter != iterEnd; ++iter)
	{
		CScript* pScript = (CScript*)(*iter)->Clone();
		pScript->SetGameObject(this);
		m_listScript.push_back(pScript);
	}
}


CGameObject::~CGameObject()
{
	for (int i = 0; i < COM_END; ++i)
	{
		SAFE_DELETE(m_arrComponent[i]);
	}

	list<CScript*>::iterator iter = m_listScript.begin();
	list<CScript*>::iterator iterEnd = m_listScript.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(*iter);
	}
}

void CGameObject::Awake()
{

	list<CScript*>::iterator iter = m_listScript.begin();
	list<CScript*>::iterator iterEnd = m_listScript.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->Awake();
	}

	for (int i = 0; i < COM_END; ++i)
	{
		if (NULL != m_arrComponent[i])
			m_arrComponent[i]->Awake();
	}

	

	// 자식들의 함수를 부모가 돌려준다.
	list<CGameObject*>::iterator objIter = m_listChildObj.begin();
	list<CGameObject*>::iterator objIterEnd = m_listChildObj.end();

	for (; objIter != objIterEnd; ++objIter)
	{
		(*objIter)->Awake();
	}

}

void CGameObject::Start()
{

	list<CScript*>::iterator iter = m_listScript.begin();
	list<CScript*>::iterator iterEnd = m_listScript.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->Start();
	}

	for (int i = 0; i < COM_END; ++i)
	{
		if (NULL != m_arrComponent[i])
			m_arrComponent[i]->Start();
	}

	// 자식들의 함수를 부모가 돌려준다.
	list<CGameObject*>::iterator objIter = m_listChildObj.begin();
	list<CGameObject*>::iterator objIterEnd = m_listChildObj.end();

	for (; objIter != objIterEnd; ++objIter)
	{
		(*objIter)->Start();
	}
}

int CGameObject::Update()
{
	list<CScript*>::iterator iter = m_listScript.begin();
	list<CScript*>::iterator iterEnd = m_listScript.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->IsEnable())
		{
			(*iter)->Update();
		}
	}

	for (int i = 0; i < COM_END; ++i)
	{
		if (NULL != m_arrComponent[i] && m_arrComponent[i]->IsEnable())
			m_arrComponent[i]->Update();
	}

	// 자식들의 함수를 부모가 돌려준다.
	list<CGameObject*>::iterator objIter = m_listChildObj.begin();
	list<CGameObject*>::iterator objIterEnd = m_listChildObj.end();

	for (; objIter != objIterEnd; ++objIter)
	{
		(*objIter)->Update();
	}
	return 0;
}

int CGameObject::LateUpdate()
{
	list<CScript*>::iterator iter = m_listScript.begin();
	list<CScript*>::iterator iterEnd = m_listScript.end();

	for (; iter != iterEnd; ++iter)
	{
		if((*iter)->IsEnable())
			(*iter)->LateUpdate();
	}

	for (int i = 0; i < COM_END; ++i)
	{
		if (NULL != m_arrComponent[i] && m_arrComponent[i]->IsEnable())
			m_arrComponent[i]->LateUpdate();
	}

	// 자식들의 함수를 부모가 돌려준다.
	list<CGameObject*>::iterator objIter = m_listChildObj.begin();
	list<CGameObject*>::iterator objIterEnd = m_listChildObj.end();

	for (; objIter != objIterEnd; ++objIter)
	{
		(*objIter)->LateUpdate();
	}
	return 0;
}

void CGameObject::Render()
{
	if (NULL != m_arrComponent[COM_RENDERER])
	{
		if (m_arrComponent[COM_RENDERER]->IsEnable())
			((CRenderer*)m_arrComponent[COM_RENDERER])->Render();
	}

	// 자식들의 함수를 부모가 돌려준다.
	list<CGameObject*>::iterator objIter = m_listChildObj.begin();
	list<CGameObject*>::iterator objIterEnd = m_listChildObj.end();

	for (; objIter != objIterEnd; ++objIter)
	{
		(*objIter)->Render();
	}
}

void CGameObject::AddChild(CGameObject * _pObj)
{
	if (NULL != _pObj)
	{
		m_listChildObj.push_back(_pObj);
		_pObj->SetParent(this);
	}
}

bool CGameObject::IsMouseOn(Vec2 _vWorldPos)
{
	// 만약 이 오브젝트가 자식인 경우에 
	// 이렇게 가져오는 크기와 위치값은 보정된 값이다. 
	// 그렇기 때문에 Transform에도 계산용 변수와 리턴용 변수를
	// 따로 두는 것이 좋다.
	if (NULL != Transform())
	{
		Vec3 vScale = Transform()->GetScale();
		Vec3 vPos = Transform()->GetPos();

		if (vPos.x - vScale.x / 2.f <= _vWorldPos.x && _vWorldPos.x <= vPos.x + vScale.x / 2.f
			&& vPos.y - vScale.y / 2.f <= _vWorldPos.y && _vWorldPos.y <= vPos.y + vScale.y / 2.f)
			return true;
	}

	return false;
}

CGameObject * CGameObject::Clone()
{
	return new CGameObject(*this);
}
