#pragma once
#include "Script.h"
class CMoveScript :
	public CScript
{
private:
	Vec3 m_vPos;
	Vec3 m_vScale;
	Vec3 m_vRot;

	CGameObject*		m_pBulletPrefab;

public:
	virtual void Start();
	virtual int Update();
	virtual int LateUpdate();

public:
	virtual CComponent* Clone()
	{
		return new CMoveScript(*this);
	}

public:
	CMoveScript();
	~CMoveScript();
};

