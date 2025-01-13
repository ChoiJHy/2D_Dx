#pragma once
#include "Script.h"

class CBulletScript :
	public CScript
{
private:
	Vec3	m_vPos;
	Vec3	m_vDir;

	float	m_fRotSpeed;
	float	m_fAngle;
	CGameObject*		m_pTarget;

private:
	void FindTarget();
	void RotateDir();
	void MoveDir();

public:
	void SetBulletDir(Vec3 _vDir)
	{
		m_vDir = _vDir;
	}

public:
	virtual void Start();
	virtual int Update();
	virtual int LateUpdate();

public:
	virtual CComponent* Clone()
	{
		return new CBulletScript(*this);
	}
	
public:
	CBulletScript();
	~CBulletScript();
};

