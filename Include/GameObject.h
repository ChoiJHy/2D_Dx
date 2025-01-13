#pragma once
#include "value.h"
#include "Res.h"

#include "Transform.h"
#include "Renderer.h"
#include "Animator.h"
#include "Script.h"
#include "Collider.h"

class CComponent;

class CGameObject :
	public CRes
{
private:
	wstring				m_strTag;
	wstring				m_strLayerName;
	CComponent*			m_arrComponent[COM_END];
	list<CScript*>		m_listScript;

	CGameObject*		m_pParent;
	list<CGameObject*>	m_listChildObj;

public:
	void Awake();
	void Start();

	int Update();
	int LateUpdate();
	void Render();

public:
	void SetLayerName(const wstring& _strLayerName)
	{
		m_strLayerName = _strLayerName;
	}

	void SetTag(wchar_t* _pTagName)
	{
		m_strTag = _pTagName;
	}

public:
	const wstring& GetLayerName()
	{
		return m_strLayerName;
	}

	const wstring& GetTag()
	{
		return m_strTag;
	}

	CGameObject* GetParent()
	{
		return m_pParent;
	}
	const list<CGameObject*>& GetChildList()
	{
		return m_listChildObj;
	}

	list<CScript*>& GetScriptList()
	{
		return m_listScript;
	}

public:
	void AddChild(CGameObject* _pObj);

	// 마우스가 오브젝트 위에 있는지 알아보기 위한 함수
	// 나의 경우 마우스에 항상 마우스 오브젝트가 붙어서 
	// PointCollider를 가지고 있기 때문에 
	// 충돌로 처리가 가능하다. 
	// 선생님의 코드는 메쉬를 기반으로 해서 정사각형의 영역을 체크하기때문에
	// 원을 체크할 일이 많은 나에게는 맞지 않는다.
	bool IsMouseOn(Vec2 _vWorldPos);

private:
	void SetParent(CGameObject* _pParent)
	{
		m_pParent = _pParent;
	}

	//Component  관련

public:
	template<typename T>
	void AddComponent(CComponent* _pComponent);

	template<typename T>
	CComponent* GetComponent();

	CTransform* Transform()
	{
		return (CTransform*)m_arrComponent[COM_TRANSFORM];
	}

	CRenderer* Renderer()
	{
		return (CRenderer*)m_arrComponent[COM_RENDERER];
	}

	CAnimator* Animator()
	{
		return (CAnimator*)m_arrComponent[COM_ANIMATOR];
	}

	CCollider* Collider()
	{
		return (CCollider*)m_arrComponent[COM_COLLIDER];
	}

public:
	CGameObject* Clone();

public:
	CGameObject();
	CGameObject(const CGameObject& _Obj);
	~CGameObject();
};

template<typename T>
inline void CGameObject::AddComponent(CComponent* _pComponent)
{
	const type_info& type = typeid(T);

	if (type.hash_code() == typeid(CTransform).hash_code())
		m_arrComponent[COM_TRANSFORM] = _pComponent;
	else if (type.hash_code() == typeid(CRenderer).hash_code())
		m_arrComponent[COM_RENDERER] = _pComponent;
	else if (type.hash_code() == typeid(CAnimator).hash_code())
		m_arrComponent[COM_ANIMATOR] = _pComponent;
	else if (type.hash_code() == typeid(CCollider).hash_code())
		m_arrComponent[COM_COLLIDER] = _pComponent;
	else if (type.hash_code() == typeid(CScript).hash_code())
		m_listScript.push_back((CScript*)_pComponent);

	_pComponent->SetGameObject(this);
}

template<typename T>
inline CComponent * CGameObject::GetComponent()
{
	const type_info& type = typeid(T);

	if (type.hash_code() == typeid(CTransform).hash_code())
		return m_arrComponent[COM_TRANSFORM];
	else if (type.hash_code() == typeid(CAnimator).hash_code())
		return m_arrComponent[COM_ANIMATOR];
	else if (type.hash_code() == typeid(CRenderer).hash_code())
		return m_arrComponent[COM_RENDERER];
	else if (type.hash_code() == typeid(CCollider).hash_code())
		return m_arrComponent[COM_COLLIDER];

	list<CScript*>::iterator iter = m_listScript.begin();
	list<CScript*>::iterator iterEnd = m_listScript.end();

	for (; iter != iterEnd; ++iter)
	{
		if (NULL != dynamic_cast<T*>(*iter))
			return (*iter);
	}

	return NULL;
}
