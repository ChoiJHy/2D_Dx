#include "stdafx.h"
#include "MainButtonScript.h"

#include "GameObject.h"

#include "SceneMgr.h"
#include "KeyMgr.h"
#include "SoundMgr.h"

CMainButtonScript::CMainButtonScript()
	: m_fDelayTime(0.0f)
	, m_bClickOn(false)
{
}

CMainButtonScript::~CMainButtonScript()
{
}

void CMainButtonScript::Start()
{
	m_vScale = TRANSFORM->GetScale();
	m_vCalScale = m_vScale;
}

int CMainButtonScript::Update()
{
	CScript::Update();
	m_fDelayTime += m_fTime;

	m_vCalScale.x += 60 * m_fTime;
	m_vCalScale.y += 60 * m_fTime;
	
	TRANSFORM->SetScale(m_vCalScale);

	if (0.5f <= m_fDelayTime)
	{
		m_vCalScale = m_vScale;
		m_fDelayTime = 0.f;
	}
	
	 
	return 0;
}

int CMainButtonScript::LateUpdate()
{
	
	return 0;
}

void CMainButtonScript::OnCollisionEnter(CCollider * _pOther)
{
	CSoundMgr::GetInst()->PlaySound(SD_MENU_HIT);
}

void CMainButtonScript::OnCollision(CCollider * _pOther)
{
	if (CKeyMgr::GetInst()->GetKey(VK_LBUTTON, STATE_TAP))
	{
		CSoundMgr::GetInst()->PlaySound(SD_MENU_CLICK);
		CSceneMgr::GetInst()->SceneChange(L"TestScene");
	}
}

CComponent * CMainButtonScript::Clone()
{
	return new CMainButtonScript(*this);
}
