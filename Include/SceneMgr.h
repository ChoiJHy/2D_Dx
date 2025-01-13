#pragma once
#include "value.h"

class CScene;
class CGameObject;

class CSceneMgr
{
private:
	map<wstring, CScene*> m_mapScene;
	CScene*			m_pCurScene;

	CGameObject*	m_pMouse;
	Vec3			m_vMousePos;

	//½ÇÇè¿ë 
	bool			m_bFadeOut;

public:
	int Init();
	int Update();
	int LateUpdate();
	void Render();

private:
	void CalMousePos();

public:
	CScene* GetCurScene()
	{
		return m_pCurScene;
	}

	CScene* GetScene(wchar_t* _strSceneName);
	
	Vec3 GetMousePos()
	{
		return m_vMousePos;
	}

public:
	CGameObject* FindGameObject(wchar_t* _strTag);
	void SceneChange(wchar_t* _strSceneName);

public:
	static CSceneMgr* GetInst()
	{
		static CSceneMgr mgr;
		return &mgr;
	}

private:
	CSceneMgr();
	~CSceneMgr();
};

