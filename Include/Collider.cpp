#include "stdafx.h"
#include "Collider.h"
#include "GameObject.h"

WORD CCollider::m_iNextID = 0;

CCollider::CCollider()
	: m_eColliderType(COLLIDER_TYPE::COLLIDER_RECTANGLE)
	, m_vPos(Vec3(0.f, 0.f, 0.f))
	, m_vOffset(Vec3(0.f, 0.f, 0.f))
	, m_fRadius(0.f)
	, m_vSize(Vec2(0.f, 0.f))
	, m_vRot(Vec3(0.f, 0.f, 0.f))
{
	m_iColID = m_iNextID++;
}


CCollider::~CCollider()
{
}

void CCollider::Awake()
{
}

void CCollider::Start()
{
	Vec3 vObjScale = Vec3(1.f, 1.f, 1.f);
	GameObject()->Transform()->GetParentsScale(&vObjScale);

	vObjScale.x *= GameObject()->Transform()->GetScale().x;
	vObjScale.y *= GameObject()->Transform()->GetScale().y;
	vObjScale.z *= GameObject()->Transform()->GetScale().z;

	// 상쇄시키기 위해서 나누어준다.
	m_vCalSize.x = m_vSize.x / vObjScale.x;
	m_vCalSize.y = m_vSize.y / vObjScale.y;

	m_vCalOffset.x = m_vOffset.x / vObjScale.x;
	m_vCalOffset.y = m_vOffset.y / vObjScale.y;
	m_vCalOffset.z = m_vOffset.z / vObjScale.z;

	m_vCalRot.x = m_vRot.z / vObjScale.x;
	m_vCalRot.y = m_vRot.z / vObjScale.y;
	m_vCalRot.z = m_vRot.z / vObjScale.z;
}

int CCollider::Update()
{
	return 0;
}

int CCollider::LateUpdate()
{
	Matrix matTrans;
	D3DXMatrixTranslation(&matTrans, m_vCalOffset.x, m_vCalOffset.y, m_vCalOffset.z);

	Matrix matScale;
	D3DXMatrixScaling(&matScale, m_vCalSize.x, m_vCalSize.y, 0.f);

	Matrix matRot;
	D3DXMatrixRotationZ(&matRot, m_vCalRot.z);

	m_matCollider = matScale*matRot*matTrans;
	m_matCollider *= GameObject()->Transform()->GetWorldMat();

	// 부모의 매트릭스를 곱해주기때문에 사실상  Collider의 Pos는 의미가 없다.
	// Offset만 설정해 주면 될듯 . 
	return 0;
}


void CCollider::SetOffset(Vec3 _vOffset)
{
	m_vOffset = _vOffset;

	Vec3 vObjScale = Vec3(1.f, 1.f, 1.f);
	GameObject()->Transform()->GetParentsScale(&vObjScale);

	vObjScale.x *= GameObject()->Transform()->GetScale().x;
	vObjScale.y *= GameObject()->Transform()->GetScale().y;
	vObjScale.z *= GameObject()->Transform()->GetScale().z;

	m_vCalOffset.x = m_vOffset.x / vObjScale.x;
	m_vCalOffset.y = m_vOffset.y / vObjScale.y;
	m_vCalOffset.z = m_vOffset.z / vObjScale.z;
}

void CCollider::SetSize(Vec2 _vSize)
{
	m_vSize = _vSize;

	Vec3 vObjScale = Vec3(1.f, 1.f, 1.f);
	GameObject()->Transform()->GetParentsScale(&vObjScale);

	vObjScale.x *= GameObject()->Transform()->GetScale().x;
	vObjScale.y *= GameObject()->Transform()->GetScale().y;
	vObjScale.z *= GameObject()->Transform()->GetScale().z;

	m_vCalSize.x = m_vSize.x / vObjScale.x;
	m_vCalSize.y = m_vSize.y / vObjScale.y;

	m_fRadius = m_vSize.x/2;
}

void CCollider::SetRot(Vec3 _vRot)
{
	m_vRot = _vRot;

	Vec3 vObjScale = Vec3(1.f, 1.f, 1.f);
	GameObject()->Transform()->GetParentsScale(&vObjScale);

	vObjScale.x *= GameObject()->Transform()->GetScale().x;
	vObjScale.y *= GameObject()->Transform()->GetScale().y;
	vObjScale.z *= GameObject()->Transform()->GetScale().z;

	m_vCalRot.x = m_vRot.z / vObjScale.x;
	m_vCalRot.y = m_vRot.z / vObjScale.y;
	m_vCalRot.z = m_vRot.z / vObjScale.z;
}

void CCollider::SetRadius(float _fRadius)
{
	m_fRadius = _fRadius;

	Vec2 vSize;
	vSize.x = m_fRadius * 2.f;
	vSize.y = m_fRadius * 2.f;

	SetSize(vSize);
}


//==================
// 충돌 검사 함수
//==================

void CCollider::OnCollisionEnter(CCollider * _pOther)
{
	list<CScript*>& ScriptList = GameObject()->GetScriptList();
	list<CScript*>::iterator iter = ScriptList.begin();
	list<CScript*>::iterator iterEnd = ScriptList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->OnCollisionEnter(_pOther);
	}
}

void CCollider::OnCollision(CCollider * _pOther)
{
	list<CScript*>& ScriptList = GameObject()->GetScriptList();
	list<CScript*>::iterator iter = ScriptList.begin();
	list<CScript*>::iterator iterEnd = ScriptList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->OnCollision(_pOther);
	}
}

void CCollider::OnCollisionExit(CCollider * _pOther)
{
	list<CScript*>& ScriptList = GameObject()->GetScriptList();
	list<CScript*>::iterator iter = ScriptList.begin();
	list<CScript*>::iterator iterEnd = ScriptList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->OnCollisionExit(_pOther);
	}
}
