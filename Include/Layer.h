#pragma once

class CGameObject;
class CLayer
{
private:
	list<CGameObject*>		m_listObj;
	wstring					m_strLayerName;

	set<CGameObject*>		m_setParentObject; // 최상위 부모를 가지고 있을 set

public:
	void SetLayerName(const wstring& _strName)
	{
		m_strLayerName = _strName;
	}

public:
	const wstring& GetLayerName()
	{
		return m_strLayerName;
	}

	const list<CGameObject*>& GetObjList_const()
	{
		return m_listObj;
	}

	list<CGameObject*>& GetObjList()
	{
		return m_listObj;
	}

	set<CGameObject*>& GetParentObjList()
	{
		return m_setParentObject;
	}

public:
	void AddGameObject(CGameObject* _pObj);
	void RemoveParent(CGameObject* _pObj);

public:
	void Awake();
	void Start();

	int Update();
	int LateUpdate();
	void Render();

public:
	CLayer();
	~CLayer();
};

