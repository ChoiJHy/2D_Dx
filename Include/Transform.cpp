#include "stdafx.h"
#include "Transform.h"

#include "GameObject.h"

CTransform::CTransform()
	: m_vPos(Vec3(0.f, 0.f, 0.f))
	, m_vScale(Vec3(1.f, 1.f, 1.f))
	, m_vRot(Vec3(0.f, 0.f, 0.f))
{
}


CTransform::~CTransform()
{
}

void CTransform::Awake()
{
	LateUpdate();
}

int CTransform::Update()
{
	return 0;
}

int CTransform::LateUpdate()
{
	Matrix matTrans;
	D3DXMatrixTranslation(&matTrans, m_vPos.x, m_vPos.y, m_vPos.z);

	Matrix matScale;
	D3DXMatrixScaling(&matScale, m_vScale.x, m_vScale.y, m_vScale.z);

	Matrix matRot;
	GetSpinMatrix(&matRot, m_vRot);

	Matrix matRevol;
	GetSpinMatrix(&matRevol, m_vRevol);

	m_matWorld = matScale * matRot * matTrans * matRevol;

	if (GameObject()->GetParent() != NULL)
	{
		Matrix ParentWorldMat = GameObject()->GetParent()->Transform()->GetWorldMat();
		m_matWorld *= ParentWorldMat;
	}

	return 0;
}

void CTransform::GetParentsScale(Vec3 * _vOut)
{
	if (GameObject()->GetParent() == NULL)
		return;

	Vec3 vScale = GameObject()->GetParent()->Transform()->GetScale();
	_vOut->x *= vScale.x;
	_vOut->y *= vScale.y;
	_vOut->z *= vScale.z;

	GameObject()->GetParent()->Transform()->GetParentsScale(_vOut);
}

void CTransform::SetScale(const Vec3 & _vScale)
{
	m_vScale = _vScale;
	if (NULL != GameObject()->Collider())
		GameObject()->Collider()->SetSize(Vec2(_vScale.x, _vScale.y));
}



void CTransform::SetPosWorld(Vec3 _vPos)
{
	if (NULL == GameObject()->GetParent())
	{
		SetPos(_vPos);
		return;
	}

	Vec3 vParentsScale(1.f, 1.f, 1.f);
	GetParentsScale(&vParentsScale);

	_vPos.x = (vParentsScale.x == 0.f) ? 0.f : _vPos.x / vParentsScale.x;
	_vPos.y = (vParentsScale.y == 0.f) ? 0.f : _vPos.y / vParentsScale.y;
	_vPos.z = (vParentsScale.z == 0.f) ? 0.f : _vPos.z / vParentsScale.z;

	SetPos(_vPos);
}

void CTransform::GetSpinMatrix(Matrix * _pOutMat, Vec3 _vSpin)
{
	Matrix matRotX;
	D3DXMatrixRotationX(&matRotX, _vSpin.x);

	Matrix matRotY;
	D3DXMatrixRotationY(&matRotY, _vSpin.y);

	Matrix matRotZ;
	D3DXMatrixRotationZ(&matRotZ, _vSpin.z);

	*_pOutMat = matRotX * matRotY * matRotZ;
}

