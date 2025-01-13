#include "stdafx.h"
#include "TestScene.h"

#include "CollisionMgr.h"
#include "PathMgr.h"
#include "ResMgr.h"

#include "GameObject.h"
#include "PlayScript.h"

CTestScene::CTestScene()
{
}


CTestScene::~CTestScene()
{
}

void CTestScene::Init()
{
	CreateLayer(L"UILayer");

	CCollisionMgr::GetInst()->CollisionCheckLayer(L"UILayer", L"UILayer");

	wstring path = CPathMgr::GetResourcesPath();

	// 필요한 오브젝트 생성 

	CGameObject* pObj = new CGameObject;
	pObj->AddComponent<CScript>(new CPlayScript);
	pObj->SetTag(L"PlayScript");

	AddGameObject(pObj, L"UILayer");

}