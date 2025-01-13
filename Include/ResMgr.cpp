#include "stdafx.h"
#include "ResMgr.h"

#include "GameObject.h"
#include "Mesh.h"

CResMgr::CResMgr()
{
}


CResMgr::~CResMgr()
{
	map<wstring, CRsPtr<CGameObject>>::iterator iter = m_mapPrefab.begin();
	map<wstring, CRsPtr<CGameObject>>::iterator iterEnd = m_mapPrefab.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}

	map<wstring, CRsPtr<CMesh>>::iterator iter1 = m_mapMesh.begin();
	map<wstring, CRsPtr<CMesh>>::iterator iterEnd1 = m_mapMesh.end();

	for (; iter1 != iterEnd1; ++iter1)
	{
		SAFE_DELETE(iter1->second);
	}

	map<wstring, CRsPtr<CTexture>>::iterator iter2 = m_mapTexture.begin();
	map<wstring, CRsPtr<CTexture>>::iterator iterEnd2 = m_mapTexture.end();

	for (; iter2 != iterEnd2; ++iter2)
	{
		SAFE_DELETE(iter2->second);
	}
}



void CResMgr::Init()
{
	CMesh* pMesh = new CMesh;
	pMesh->Init(4, 2);

	VTXTEX arrVtx[4];

	// 정점 정보 셋팅
	arrVtx[0].vPos = Vec3(-0.5f, -0.5f, 0.f);
	//arrVtx[0].col = D3DCOLOR_ARGB(255, 255, 255, 255);
	arrVtx[0].vUV = Vec2(0.f, 1.f);

	arrVtx[1].vPos = Vec3(0.5f, -0.5f, 0.f);
	//arrVtx[1].col = D3DCOLOR_ARGB(255, 255, 255, 255);
	arrVtx[1].vUV = Vec2(1.f, 1.f);
	
	arrVtx[2].vPos = Vec3(-0.5f, 0.5f, 0.f);
	//arrVtx[2].col = D3DCOLOR_ARGB(255, 255, 255, 255);
	arrVtx[2].vUV = Vec2(0.f, 0.f);

	arrVtx[3].vPos = Vec3(0.5f, 0.5f, 0.f);
	//arrVtx[3].col = D3DCOLOR_ARGB(255, 255, 255, 255);
	arrVtx[3].vUV = Vec2(1.f, 0.f);

	pMesh->SetVtxInfo(arrVtx, 4);

	INDEX16 Idx[2];
	Idx[0]._1 = 0; Idx[0]._2 = 1; Idx[0]._3 = 2;
	Idx[1]._1 = 1; Idx[1]._2 = 3; Idx[1]._3 = 2;

	pMesh->SetIdxInfo(Idx, 2);

	m_mapMesh.insert(make_pair(L"DefaultMesh", pMesh));
	pMesh->SetKey(L"DefaultMesh");
}

bool CResMgr::AddPrefab(CGameObject * _pObj)
{
	if (m_mapPrefab.find(_pObj->GetTag()) != m_mapPrefab.end())
		return false;
	
	m_mapPrefab.insert(make_pair(_pObj->GetTag(), _pObj));
	return true;
}

CRsPtr<CGameObject> CResMgr::GetPrefab(wchar_t * _pTagName)
{
	map<wstring, CRsPtr<CGameObject>>::iterator mapiter = m_mapPrefab.find(_pTagName);

	if (mapiter != m_mapPrefab.end())
		return mapiter->second;

	return nullptr;
}

CTexture * CResMgr::GetTexture(wchar_t * _strTexKey)
{
	map<wstring, CRsPtr<CTexture>>::iterator iter = m_mapTexture.find(_strTexKey);

	if (iter != m_mapTexture.end())
		return iter->second;
	else
		return NULL;
}