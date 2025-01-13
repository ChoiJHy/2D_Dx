#include "stdafx.h"
#include "SceneMgr.h"

#include "StartScene.h"
#include "TestScene.h"

#include "ResMgr.h"
#include "PathMgr.h"
#include "SoundMgr.h"
#include "CollisionMgr.h"
#include "TimeMgr.h"

#include "GameObject.h"
#include "Transform.h"
#include "Renderer.h"
#include "Animator.h"

#include "MoveScript.h"
#include "BulletScript.h"

#include "GameObject.h"
#include "Core.h"


CSceneMgr::CSceneMgr()
	: m_pCurScene(NULL)
	, m_pMouse(NULL)
	, m_vMousePos(Vec3(0.f, 0.f, 99.f))
	, m_bFadeOut(false)
{
}


CSceneMgr::~CSceneMgr()
{
	map<wstring, CScene*>::iterator iter = m_mapScene.begin();
	for (; iter != m_mapScene.end(); ++iter)
	{
		SAFE_DELETE(iter->second);
	}

	SAFE_DELETE(m_pMouse);
}

void CSceneMgr::CalMousePos()
{
	POINT mouse;
	GetCursorPos(&mouse);
	ScreenToClient(CCore::GetInst()->GetHWND(), &mouse);

	m_vMousePos.x = (float)mouse.x - WINSIZE_X * 0.5f;

	if (m_vMousePos.y < WINSIZE_Y * 0.5f)
		m_vMousePos.y = WINSIZE_Y * 0.5f - (float)mouse.y;
	else
		m_vMousePos.y = (float)mouse.y - WINSIZE_Y * 0.5f;

	//마우스가 화면 밖으로 나가지 못하도록 막는다.
	if (m_vMousePos.y < -450.f)
	{
		
	}
//	TCHAR str[256] = {0,};
//	wsprintf(str, _T("%d, %d\n"), (int)m_vMousePos.x, (int)m_vMousePos.y);
//
//	OutputDebugString(str);
}

CScene * CSceneMgr::GetScene(wchar_t * _strSceneName)
{
	map<wstring, CScene*>::iterator iter = m_mapScene.find(_strSceneName);

	if(iter == m_mapScene.end())
		return nullptr;

	return iter->second;
}

int CSceneMgr::Init()
{
	// CSceneMgr을 초기화 해주면서 해야 할 일
	// 1. CResMgr에 피룡한 텍스쳐 및 모든 음악 파일을 로드 해둔다.
	// 2. 만들어야 할 CScene을 만들어놓고 모두 m_mapScene에 추가해둔다.
	// 3. 현재 Scene으로 지정할 Scene을 현재 씬으로 지정해둔다. 
	// 4. 마우스 오브젝트를 만들어 두고 현재 씬의 레이어에 넣는다. 
	// 5. 미리 만들어둬야 할 Prefab을 모두 만들어서 등록해둔다. 

	//Texture Load
	wstring path = CPathMgr::GetResourcesPath();
	CResMgr::GetInst()->Load<CTexture>(path + L"Texture\\Background.bmp", L"Background");
	CResMgr::GetInst()->Load<CTexture>(path + L"Texture\\CuteMonster.png", L"CuteMonster");
	CResMgr::GetInst()->Load<CTexture>(path + L"Texture\\Missile.png", L"Missile");
	CResMgr::GetInst()->Load<CTexture>(path + L"Texture\\cursor.png", L"Cursor");
	CResMgr::GetInst()->Load<CTexture>(path + L"Texture\\Osu!Logo.png", L"MainButton");

	//효과음 추가
	CSoundMgr::GetInst()->SoundLoad(path + L"Sound\\Effects\\menuhit.wav", SD_MENU_HIT);
	CSoundMgr::GetInst()->SoundLoad(path + L"Sound\\Effects\\menuclick.wav", SD_MENU_CLICK);

	// 노래 추가 
	CSoundMgr::GetInst()->StreamLoad(path + L"Sound\\Songs\\FreedomDive.mp3", L"FreedomDive");
	CSoundMgr::GetInst()->StreamLoad(path + L"Sound\\Songs\\Shelter_Piano.mp3", L"Shelter");

	//Scene 새로 만들고 이름을 정해준 뒤 관리를 위한 map에 추가해준다. 
	CScene* pScene = new CStartScene;
	pScene->SetSceneName(L"StartScene");
	m_mapScene.insert(make_pair(pScene->GetSceneName(), pScene));

	pScene = new CTestScene;
	pScene->SetSceneName(L"TestScene");
	m_mapScene.insert(make_pair(pScene->GetSceneName(), pScene));

	
	//현재 Scene을 지정해준다.
	m_pCurScene = GetScene(L"StartScene");
	m_pCurScene->Init();

	//Layer 추가 
	m_pCurScene->CreateLayer(L"Monster");

	// 마우스 추가
	m_pMouse = new CGameObject;
	m_pMouse->AddComponent<CTransform>(new CTransform);
	m_pMouse->AddComponent<CRenderer>(new CRenderer);
	m_pMouse->AddComponent<CCollider>(new CCollider);
	m_pMouse->Collider()->SetColliderType(COLLIDER_TYPE::COLLIDER_POINT);
	m_pMouse->Renderer()->SetTex(CResMgr::GetInst()->GetTexture(L"Cursor"));
	m_pMouse->Transform()->SetScale(Vec3(60.f, 60.f, 1.f));
	m_pMouse->SetTag(L"Mouse");
	m_pCurScene->AddGameObject(m_pMouse, L"UILayer");

	//CGameObject* pObj = new CGameObject;

	//pObj->AddComponent<CRenderer>(new CRenderer);
	//pObj->Renderer()->SetTex(CResMgr::GetInst()->GetTexture(L"Background"));
	//pObj->AddComponent<CTransform>(new CTransform);
	//pObj->AddComponent<CScript>(new CMoveScript);
	//pObj->AddComponent<CCollider>(new CCollider);
	//pObj->Collider()->SetColliderType(COLLIDER_TYPE::COLLIDER_CIRCLE);
	//pObj->Collider()->SetRadius(100.f);
	//pObj->AddComponent<CAnimator>(new CAnimator);
	//pObj->Animator()->LoadAnimation(path + L"Texture\\Animation\\Explosion", L"Explosion");
	//pObj->Animator()->PlayAnimation(L"Explosion");

	//pObj->SetTag(L"Player");

	//m_pCurScene->AddGameObject(pObj, L"Default");

	////몬스터
	//pObj = new CGameObject;

	//pObj->AddComponent<CRenderer>(new CRenderer);
	//pObj->Renderer()->SetTex(CResMgr::GetInst()->GetTexture(L"CuteMonster"));
	//pObj->AddComponent<CTransform>(new CTransform);
	//pObj->Transform()->SetPos(Vec3(400.f, 100.f, 100.f));
	//pObj->Transform()->SetScale(Vec3(150.f, 150.f, 0.f));
	//pObj->AddComponent<CCollider>(new CCollider);
	//pObj->Collider()->SetSize(Vec2(200.f, 200.f));

	//pObj->SetTag(L"Monster");

	//m_pCurScene->AddGameObject(pObj, L"Monster");


	//Prefab  등록
	/*pObj = new CGameObject;

	pObj->AddComponent<CRenderer>(new CRenderer);
	pObj->Renderer()->SetTex(CResMgr::GetInst()->GetTexture(L"Missile"));
	pObj->AddComponent<CTransform>(new CTransform);
	pObj->AddComponent<CScript>(new CBulletScript);

	pObj->SetTag(L"Bullet_1");

	CResMgr::GetInst()->AddPrefab(pObj);
*/
	m_pCurScene->Awake();
	m_pCurScene->Start();

	//CCollisionMgr::GetInst()->CollisionCheckLayer(L"Default", L"Monster");
	//CCollisionMgr::GetInst()->CollisionCheckLayer(L"Default", L"Default");
	return 0;
}

int CSceneMgr::Update()
{
	CalMousePos();
	m_pMouse->Transform()->SetPos(m_vMousePos);

	if (!m_bFadeOut)
	{
		if (m_pMouse->Renderer()->FadeOut(CTimeMgr::GetInst()->DeltaTime(), 3.f))
		{
			m_bFadeOut = true;
		}
	}
	else
	{
		if (m_pMouse->Renderer()->FadeIn(CTimeMgr::GetInst()->DeltaTime(), 1.4f))
		{
			m_bFadeOut = false;
		}
	}
	
	/*if (m_fA <= 0.f)
	{
		m_iDir = 1;

		if (m_fA <= 0.f)
			m_fA = 0.f;
	}
	else if (m_fA > 1.f )
	{
		m_iDir = -1;

		if (m_fA >= 1.f)
			m_fA = 1.f;
	}

	m_fA += CTimeMgr::GetInst()->DeltaTime() * 0.5f * m_iDir;
	m_pMouse->Renderer()->SetAlpha(m_fA);*/


	if (NULL != m_pCurScene)
		m_pCurScene->Update();
	return 0;
}

int CSceneMgr::LateUpdate()
{
	if (NULL != m_pCurScene)
		m_pCurScene->LateUpdate();
	return 0;
}

void CSceneMgr::Render()
{
	if (NULL != m_pCurScene)
		m_pCurScene->Render();
}

CGameObject * CSceneMgr::FindGameObject(wchar_t * _strTag)
{
	if (NULL != m_pCurScene)
		return m_pCurScene->FindGameObject(_strTag);

	return nullptr;
}

void CSceneMgr::SceneChange(wchar_t * _strSceneName)
{
	//Scene이름을 넣어주면 map에서 찾은 뒤 m_pCurScene을 찾은 Scene으로 바꿔준다. 

	map<wstring, CScene*>::iterator mapIter = m_mapScene.find(_strSceneName);

	if (mapIter == m_mapScene.end())
		return;

	m_pCurScene = mapIter->second;

	if (!m_pCurScene->GetInit())
	{
		m_pCurScene->Init();
		m_pCurScene->Awake();
		m_pCurScene->Start();
		m_pCurScene->SetInit(true);
	}

	// 아래 작업을 처리해 주기위해서 모든 Scene은 UILayer를 기본으로 생성해야 한다.
	CGameObject* pObj = m_pCurScene->FindGameObject(L"Mouse");

	if (NULL == pObj)
	{
		m_pCurScene->AddGameObject(m_pMouse, L"UILayer");
	}
}
	