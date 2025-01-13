#include "stdafx.h"
#include "MoveScript.h"

#include "GameObject.h"
#include "Transform.h"
#include "BulletScript.h"

#include "ResMgr.h"
#include "KeyMgr.h"
#include "SoundMgr.h"

CMoveScript::CMoveScript()
	: m_vPos(Vec3(0.f, 0.f, 0.f))
	, m_vScale(Vec3(1.f, 1.f, 0.f))
	, m_vRot(Vec3(0.f, 0.f, 0.f))
{
}


CMoveScript::~CMoveScript()
{
	
}

void CMoveScript::Start()
{
	m_vPos = Vec3(0.f, 0.f, 100.f);
	m_vScale = Vec3(100.f, 100.f, 0.f);

	TRANSFORM->SetPos(m_vPos);
	TRANSFORM->SetScale(m_vScale);
	TRANSFORM->SetRot(m_vRot);

	m_pBulletPrefab = CResMgr::GetInst()->GetPrefab(L"Bullet_1");
}

int CMoveScript::Update()
{
	CScript::Update();

	CSoundMgr::GetInst()->PlayStream(L"FreedomDive");

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_vPos.x -= 200 * m_fTime;
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_vPos.x += 200 * m_fTime;
	}
	else if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_vPos.y += 200 * m_fTime;
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_vPos.y -= 200 * m_fTime;
	}

	if (GetAsyncKeyState('X') & 0x8000)
	{
		m_vRot.x += D3DX_PI * m_fTime;
	}
	else if (GetAsyncKeyState('Y') & 0x8000)
	{
		m_vRot.y += D3DX_PI * m_fTime;
	}
	else if (GetAsyncKeyState('Z') & 0x8000)
	{
		m_vRot.z += D3DX_PI * m_fTime;
	}

	if (KEY(VK_SPACE, STATE_PUSH))
	{
		Vec3 vPos = TRANSFORM->GetPos();
		vPos.x += 100;
		CGameObject* pGameObj = Instantiate(m_pBulletPrefab, vPos);
		CBulletScript* pBulletScript = (CBulletScript*)pGameObj->GetComponent<CBulletScript>();

		Vec3 Dir = Vec3(1.f, 0.f, 0.f);
		D3DXVec3Normalize(&Dir, &Dir);

		pBulletScript->SetBulletDir(Dir);

	}

	TRANSFORM->SetPos(m_vPos);
	TRANSFORM->SetScale(m_vScale);
	TRANSFORM->SetRot(m_vRot);

	return 0;
}

int CMoveScript::LateUpdate()
{
	return 0;
}
