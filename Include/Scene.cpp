#include "stdafx.h"
#include "Scene.h"

#include "Layer.h"
#include "GameObject.h"

#include "Device.h"
#include "Camera.h"


CScene::CScene()
	: m_iLayerCnt(0)
	, m_bInit(false)
{
	//Default Layer 생성
	CreateLayer(L"Default");
}


CScene::~CScene()
{

	map<wstring, LAYER>::iterator iter = m_mapLayer.begin();
	for (iter; iter != m_mapLayer.end(); ++iter)
	{
		delete iter->second.pLayer;
	}

}

bool CScene::AddGameObject(CGameObject * _pObj, const wstring & _strLayerName)
{
	map<wstring, LAYER>::iterator finditer = m_mapLayer.find(_strLayerName);
	if(finditer == m_mapLayer.end())
		return false;

	finditer->second.pLayer->AddGameObject(_pObj);
	return true;
}

CGameObject * CScene::FindGameObject(wchar_t * _strTag)
{
	map<wstring, LAYER>::iterator iter = m_mapLayer.begin();
	map<wstring, LAYER>::iterator iterEnd = m_mapLayer.end();

	for (; iter != iterEnd; ++iter)
	{
		const list<CGameObject*>& ObjList = iter->second.pLayer->GetObjList_const();
		list<CGameObject*>::const_iterator listiter = ObjList.begin();
		list<CGameObject*>::const_iterator listiterEnd = ObjList.end();

		for (; listiter != listiterEnd; ++listiter)
		{
			if ((*listiter)->GetTag() == _strTag)
			{
				return *listiter;
			}
		}
	}

	return nullptr;
}

bool CScene::CreateLayer(wchar_t * _pLayerName)
{
	map<wstring, LAYER>::iterator iter = m_mapLayer.find(_pLayerName);

	if (iter != m_mapLayer.end())
		return false;

	CLayer* pNewLayer = new CLayer;
	pNewLayer->SetLayerName(_pLayerName);

	m_mapLayer.insert(make_pair(_pLayerName, LAYER{ m_iLayerCnt++, pNewLayer }));
	m_vecLayerIdx.push_back(_pLayerName);
	return true;
}

int CScene::GetLayerIndex(wstring _strLayerName)
{
	map<wstring, LAYER>::iterator iter = m_mapLayer.find(_strLayerName);
	if (iter == m_mapLayer.end())
		return -1;

	return iter->second.iIdx;
}

CLayer * CScene::GetLayerFromIndex(int _iIdx)
{
	if (_iIdx < 0 || _iIdx >= (int)m_vecLayerIdx.size())
		return NULL;

	wstring strLayerName = m_vecLayerIdx.at(_iIdx);

	map<wstring, LAYER>::iterator iter = m_mapLayer.find(strLayerName);
	if (iter == m_mapLayer.end())
		return NULL;

	return iter->second.pLayer;
}
CLayer * CScene::GetLayerFromName(wstring _strLayerName)
{
	map<wstring, LAYER>::iterator iter = m_mapLayer.find(_strLayerName);
	if (iter != m_mapLayer.end())
		return iter->second.pLayer;

	return nullptr;
}

void CScene::GetGameObjectList(list<CGameObject*>& _pObjList)
{
	map<wstring, LAYER>::iterator iter = m_mapLayer.begin();
	for (iter; iter != m_mapLayer.end(); ++iter)
	{
		const list<CGameObject*>& ObjList = iter->second.pLayer->GetObjList();
		list<CGameObject*>::const_iterator listIter = ObjList.begin();

		for (listIter; listIter != ObjList.end(); ++listIter)
		{
			_pObjList.push_back(*listIter);
		}
	}
}

void CScene::GetParentGameObjectList(list<CGameObject*>& _pObjList)
{
	map<wstring, LAYER>::iterator iter = m_mapLayer.begin();
	for (; iter != m_mapLayer.end(); ++iter)
	{
		const set<CGameObject*>& ObjList = iter->second.pLayer->GetParentObjList();
		set<CGameObject*>::const_iterator listIter = ObjList.begin();

		for (; listIter != ObjList.end(); ++listIter)
		{
			_pObjList.push_back(*listIter);
		}
	}
}

CGameObject * CScene::GetClickedObject(POINT _pt)
{
	Vec2 vWorldPos((float)_pt.x, (float)_pt.y);

	//vWorldPos를 화면비에 따라서 변경한다.
	HWND hWnd = CDevice::GetInst()->GetMainHWND();
	RECT rt{ 0 };
	GetWindowRect(hWnd, &rt);

	// 변경된 비율을 원래 비율인 WINSIZE_X, WINSIZE_Y 기준으로 되돌려 놓는다.
	float fXRatio = ((float)rt.right - (float)rt.left) / (float)WINSIZE_X;
	float fYRatio = ((float)rt.bottom - (float)rt.top) / (float)WINSIZE_Y;

	vWorldPos.x /= fXRatio;
	vWorldPos.y /= fYRatio;

	// 윈도우 좌표를 게임상의 좌표로 변경한다.
	Vec3 vCamPos = CCamera::GetInst()->GetPos();

	vWorldPos.x = (vWorldPos.x -WINSIZE_X * 0.5f) + vCamPos.x;
	vWorldPos.y = WINSIZE_Y * 0.5f - (float)_pt.y + vCamPos.y;

	// 해당 좌표로 충돌하는 게임 오브젝트를 찾는다.
	map<wstring, LAYER>::iterator iter = m_mapLayer.begin();
	map<wstring, LAYER>::iterator iterEnd = m_mapLayer.end();

	for (; iter != iterEnd; ++iter)
	{
		const list<CGameObject*>& ObjList = iter->second.pLayer->GetObjList();
		list<CGameObject*>::const_iterator listIter = ObjList.begin();
		list<CGameObject*>::const_iterator listIterEnd = ObjList.end();

		for (; listIter != listIterEnd; ++listIter)
		{
			if ((*listIter)->IsMouseOn(vWorldPos))
			{
				return (*listIter);
			}
		}
	}
	return nullptr;
}

void CScene::Awake()
{
	map<wstring, LAYER>::iterator iter = m_mapLayer.begin();
	for (iter; iter != m_mapLayer.end(); ++iter)
	{
		iter->second.pLayer->Awake();
	}
}

void CScene::Start()
{
	map<wstring, LAYER>::iterator iter = m_mapLayer.begin();
	for (iter; iter != m_mapLayer.end(); ++iter)
	{
		iter->second.pLayer->Start();
	}
}

int CScene::Update()
{
	map<wstring, LAYER>::iterator iter = m_mapLayer.begin();
	for (iter; iter != m_mapLayer.end(); ++iter)
	{
		iter->second.pLayer->Update();
	}
	return 0;
}

int CScene::LateUpdate()
{
	map<wstring, LAYER>::iterator iter = m_mapLayer.begin();
	for (iter; iter != m_mapLayer.end(); ++iter)
	{
		iter->second.pLayer->LateUpdate();
	}
	return 0;
}

void CScene::Render()
{
	map<wstring, LAYER>::iterator iter = m_mapLayer.begin();
	for (iter; iter != m_mapLayer.end(); ++iter)
	{
		iter->second.pLayer->Render();
	}
}