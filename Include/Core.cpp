#include "stdafx.h"
#include "Core.h"

#include "Device.h"
#include "Camera.h"
#include "SceneMgr.h"
#include "ResMgr.h"
#include "TimeMgr.h"
#include "KeyMgr.h"
#include "CollisionMgr.h"
#include "SoundMgr.h"

CCore::CCore()
{
}


CCore::~CCore()
{
}

int CCore::Init(HWND _hWnd, bool _bWindowMode)
{
	m_hWnd = _hWnd;

	if (!CDevice::GetInst()->Init(_hWnd, _bWindowMode))
		return false;
	
	CSoundMgr::GetInst()->Init();
	CTimeMgr::GetInst()->Init();
	CResMgr::GetInst()->Init();
	CSceneMgr::GetInst()->Init();
	CCamera::GetInst()->Init();
	CKeyMgr::GetInst()->Init();
	
	return true;
}

int CCore::Run()
{
	Update();

	LateUpdate();

	Render();

	return 0;
}


int CCore::Update()
{
	CSoundMgr::GetInst()->Update();
	CTimeMgr::GetInst()->Update();
	CCamera::GetInst()->Update();
	CSceneMgr::GetInst()->Update();
	CKeyMgr::GetInst()->Update();
	return 0;
}

int CCore::LateUpdate()
{
	CCamera::GetInst()->SetMatrix();
	CSceneMgr::GetInst()->LateUpdate();

	CCollisionMgr::GetInst()->LateUpdate();
	return 0;
}

void CCore::Render()
{
	//화면 갱신
	DEVICE->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 0, 0, 0), 1.f, 0);

	//그리기 시작
	DEVICE->BeginScene();

	CSceneMgr::GetInst()->Render();

	//그리기 종료
	DEVICE->EndScene();

	//전면 후면버퍼 교체
	DEVICE->Present(NULL, NULL, NULL, NULL);
}