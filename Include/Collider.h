#pragma once
#include "Component.h"
#include "value.h"

class CCollider :
	public CComponent
{
private:
	static WORD		m_iNextID;
	WORD			m_iColID;

	COLLIDER_TYPE	m_eColliderType;
	Vec3			m_vPos;

	Vec3			m_vCalOffset;	// 계산을 위한 Offset
	Vec3			m_vOffset;		// 출력을 위한 Offset;

	Vec2			m_vCalSize;		// 계산을 위한 Size
	Vec2			m_vSize;		// 출력을 위한 Size

	Vec3			m_vCalRot;		// 계산을 위한 회전값
	Vec3			m_vRot;			// 출력을 위한 회전값

	float			m_fRadius;

	Matrix			m_matCollider;
public:
	void SetPos(Vec3 _vPos)
	{
		m_vPos = _vPos;
	}

	void SetOffset(Vec3 _vOffset);
	void SetSize(Vec2 _vSize);
	void SetRot(Vec3 _vRot);

	void SetRadius(float _fRadius);

	void SetColliderType(COLLIDER_TYPE _eType)
	{
		m_eColliderType = _eType;
	}

public:
	Vec3 GetPos()
	{
		return m_vPos + m_vOffset;
	}

	Vec3 GetOffset()
	{
		return m_vOffset;
	}

	Vec2 GetSize()
	{
		return m_vSize;
	}
	
	Vec3 GetRot()
	{
		return m_vRot;
	 }

	float GetRadius()
	{
		return m_fRadius;
	}

	COLLIDER_TYPE GetColliderType()
	{
		return m_eColliderType;
	}

	Matrix GetColliderMatrix()
	{
		return m_matCollider;
	}

	WORD GetID()
	{
		return m_iColID;
	}

public:
	void Awake();
	void Start();
	int Update();
	int LateUpdate();

public:
	void OnCollisionEnter(CCollider* _pOther);
	void OnCollision(CCollider* _pOther);
	void OnCollisionExit(CCollider* _pOther);

public:
	virtual CComponent* Clone()
	{
		return new CCollider(*this);
	}

public:
	CCollider();
	virtual ~CCollider();
};

