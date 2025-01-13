#pragma once
#include "Script.h"
class CMainButtonScript :
	public CScript
{
private:
	Vec3 m_vScale;
	Vec3 m_vCalScale;

	float m_fDelayTime;

	bool m_bClickOn;

public:
	virtual void Start();
	virtual int Update();
	virtual int LateUpdate();
	
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollision(CCollider* _pOther);

	virtual CComponent* Clone();

public:
	CMainButtonScript();
	~CMainButtonScript();
};

