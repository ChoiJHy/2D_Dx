#pragma once
#include "value.h"

class CGameObject;
class CComponent
{
private:
	CGameObject*		m_pGameObj;
	bool				m_bEnable;

public:
	CGameObject* GameObject()
	{
		return m_pGameObj;
	}

	void SetGameObject(CGameObject* _pObj)
	{
		m_pGameObj = _pObj;
	}

	void SetEnable(bool _bEnable)
	{
		m_bEnable = _bEnable;
	}

public:
	bool IsEnable()
	{
		return m_bEnable;
	}

public:
	virtual void Awake() {}
	virtual void Start() {}
	virtual int Update() = 0;
	virtual int LateUpdate() = 0;
	virtual CComponent* Clone() = 0;

public:
	CComponent();
	virtual ~CComponent();
};

