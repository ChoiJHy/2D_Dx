#include "stdafx.h"
#include "PlayScript.h"

#include "SoundMgr.h"
#include "SceneMgr.h"
#include "KeyMgr.h"

CPlayScript::CPlayScript()
	: m_bPause(false)
{
}


CPlayScript::~CPlayScript()
{
}

void CPlayScript::Start()
{

}

int CPlayScript::Update()
{
	CSoundMgr::GetInst()->PlayStream(L"Shelter");

	if (CKeyMgr::GetInst()->GetKey(VK_ESCAPE, STATE_TAP))
	{
		if (!m_bPause)
			m_bPause = true;
		else
			m_bPause = false;

		CSoundMgr::GetInst()->SetPause(m_bPause);
	}

	if (CKeyMgr::GetInst()->GetKey('1', STATE_TAP))
	{
		CSoundMgr::GetInst()->PlaySound(SD_MENU_CLICK);
		CSoundMgr::GetInst()->StopStream();
		CSceneMgr::GetInst()->SceneChange(L"StartScene");

	}
	return 0;
}

int CPlayScript::LateUpdate()
{
	return 0;
}