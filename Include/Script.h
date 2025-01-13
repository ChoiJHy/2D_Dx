#pragma once
#include "Component.h"

#define TRANSFORM	GameObject()->Transform()
#define RENDERER	GameObject()->Renderer();

class CCollider;
class CScript :
	public CComponent
{
protected:
	float		m_fTime;
public:
	virtual int Update();
	virtual int LateUpdate() = 0;
	virtual CComponent* Clone() = 0;

	virtual void OnCollisionEnter(CCollider* _pOther) {}
	virtual void OnCollision(CCollider* _pOther) {}
	virtual void OnCollisionExit(CCollider* _pOther) {}


protected:
	CGameObject* Instantiate(CGameObject* _pObj, Vec3 _vPos, wstring _strLayerName = L"");

public:
	CScript();
	virtual ~CScript();
};

