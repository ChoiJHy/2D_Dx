#pragma once

class CGameObject;

#include "Texture.h"
#include "Mesh.h"
#include "RsPtr.h"

class CResMgr
{
private:
	map<wstring, CRsPtr<CGameObject>>		m_mapPrefab;
	map<wstring, CRsPtr<CMesh>>				m_mapMesh;
	map<wstring, CRsPtr<CTexture>>			m_mapTexture;

public:
	bool AddPrefab(CGameObject* _pObj);
	CRsPtr<CGameObject> GetPrefab(wchar_t* _pTagName);

	template<typename T>
	CRes* Load(wstring _strResPath, wstring _strKey);

public:
	CTexture* GetTexture(wchar_t* _strTexKey);

public:
	void Init();

public:
	static CResMgr* GetInst()
	{
		static CResMgr ResMgr;
		return &ResMgr;
	}
private:
	CResMgr();
	~CResMgr();
};

template<typename T>
CRes * CResMgr::Load(wstring _strResPath, wstring _strKey)
{
	const type_info& info = typeid(T);

	if (info.hash_code() == typeid(CMesh).hash_code())
	{
		map<wstring, CRsPtr<CMesh>>::iterator iter = m_mapMesh.find(_strKey);
		if (iter != m_mapMesh.end())
		{
			return iter->second;
		}
	}
	else if (info.hash_code() == typeid(CTexture).hash_code())
	{
		map<wstring, CRsPtr<CTexture>>::iterator iter = m_mapTexture.find(_strKey);
		if (iter != m_mapTexture.end())
			return iter->second;

		else
		{
			CTexture* pTex = new CTexture;
			if (!pTex->Load(_strResPath.c_str()))
			{
				delete pTex;
				return NULL;
			}
			m_mapTexture.insert(make_pair(_strKey, pTex));
			pTex->SetKey(_strKey.c_str());
			return pTex;
		}
	}

	return NULL;
}
