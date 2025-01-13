#include "stdafx.h"
#include "StartScene.h"

#include "GameObject.h"

#include "CollisionMgr.h"
#include "ResMgr.h"
#include "PathMgr.h"

#include "MainButtonScript.h"


CStartScene::CStartScene()
{
}


CStartScene::~CStartScene()
{
}

void CStartScene::Init()
{
	// Scene 초기화시 해야할 것들.
	// 1. 필요한 레이어를 모두 만들어 둔다. 
	// 2. 레이어끼리의 충돌관계를 정해둔다. 
	// 3. 화면에 띄울 오브젝트를 만든다. 

	CreateLayer(L"UILayer");
	
	CCollisionMgr::GetInst()->CollisionCheckLayer(L"UILayer", L"UILayer");
	
	wstring path = CPathMgr::GetResourcesPath();
	
	// 필요한 오브젝트 생성 

	CGameObject* pObj = new CGameObject;
	pObj->AddComponent<CRenderer>(new CRenderer);
	pObj->Renderer()->SetTex(CResMgr::GetInst()->GetTexture(L"MainButton"));
	pObj->AddComponent<CTransform>(new CTransform);
	pObj->Transform()->SetScale(Vec3(500.f, 500.f, 1.f));
	pObj->AddComponent<CScript>(new CMainButtonScript);
	pObj->AddComponent<CCollider>(new CCollider);
	pObj->Collider()->SetColliderType(COLLIDER_TYPE::COLLIDER_CIRCLE);
	pObj->Collider()->SetRadius(250.f);
	pObj->SetTag(L"MainButton");

	AddGameObject(pObj, L"UILayer");
	
	//StartScene은 맨 처음 바로 만들어 주기 때문에 여기서 바로 초기화가 끝났다고 알려줘야 한다. 
	SetInit(true);
}