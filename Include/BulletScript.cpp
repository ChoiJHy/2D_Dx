#include "stdafx.h"
#include "BulletScript.h"

#include "GameObject.h"
#include "Transform.h"

#include "SceneMgr.h"

CBulletScript::CBulletScript()
{
}


CBulletScript::~CBulletScript()
{
}

void CBulletScript::FindTarget()
{
	if (NULL != m_pTarget)
		return;

	m_pTarget = CSceneMgr::GetInst()->FindGameObject(L"Monster");
}

void CBulletScript::RotateDir()
{
	int iDir = 0; //회전할 방향

	//회전 방향을 알아낸다.
	if (NULL != m_pTarget)
	{
		Vec3 vTargetDir = m_pTarget->Transform()->GetPos() - TRANSFORM->GetPos();
		D3DXVec3Normalize(&vTargetDir, &vTargetDir);

		Vec3 vCrossOut;
		D3DXVec3Cross(&vCrossOut, &m_vDir,&vTargetDir); // 내가 바라보는 방향과 타겟쪽으로의 방향을 외적하여 어느 쪽으로 회전할지 정한다.
		if (vCrossOut.z < 0)
			iDir = -1;
		else
			iDir = 1;
	}

	// m_vDir(미사일 방향벡터) 를 결정 된 회전 방향으로 조금씩 회전한다.
	Matrix matRotZ;
	D3DXMatrixRotationZ(&matRotZ, m_fRotSpeed * m_fTime * iDir);
	D3DXVec3TransformNormal(&m_vDir, &m_vDir, &matRotZ);
	
	float fDot = D3DXVec3Dot(&Vec3(1.f, 0.f, 0.f), &m_vDir);
	if (fDot > 1.f)
		fDot = 1.f;
	else if (fDot < -1.f)
		fDot = -1.f;

	float fRot = acos(fDot);
	if (m_vDir.y < 0)
		fRot = D3DX_PI * 2.f - fRot;

	TRANSFORM->SetRot(Vec3(0.f, 0.f, fRot));
}

void CBulletScript::MoveDir()
{
	m_vPos += m_vDir * m_fTime * 500.f;
	TRANSFORM->SetPos(m_vPos);
}

void CBulletScript::Start()
{
	m_vPos = TRANSFORM->GetPos();
	TRANSFORM->SetScale(Vec3(100.f, 33.f, 0.f));

	m_fRotSpeed = D3DX_PI;
}

int CBulletScript::Update()
{
	CScript::Update();

	FindTarget();

	RotateDir();

	MoveDir();

	return 0;
}

int CBulletScript::LateUpdate()
{
	return 0;
}