#include "stdafx.h"
#include "Script.h"

#include "GameObject.h"
#include "Transform.h"
#include "Renderer.h"

#include "SceneMgr.h"
#include "Scene.h"

#include "TimeMgr.h"

CScript::CScript()
	: m_fTime(0.f)
{
}


CScript::~CScript()
{
}

int CScript::Update()
{
	m_fTime = CTimeMgr::GetInst()->DeltaTime();
	return 0;
}

CGameObject* CScript::Instantiate(CGameObject * _pObj, Vec3 _vPos, wstring _strLayerName)
{
	if (_strLayerName.length() == 0)
	{
		_strLayerName = GameObject()->GetLayerName();
	}

	CGameObject* pCopy = _pObj->Clone();

	pCopy->Transform()->SetPos(_vPos);

	pCopy->Awake();
	pCopy->Start();

	if (!CSceneMgr::GetInst()->GetCurScene()->AddGameObject(pCopy, _strLayerName))
		return NULL;

	return pCopy;
}