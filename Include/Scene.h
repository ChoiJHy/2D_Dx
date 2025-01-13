#pragma once
#include "stdafx.h"

class CLayer;
class CGameObject;

typedef struct _tagLayer
{
	int		 iIdx;
	CLayer*	 pLayer;
}LAYER;

class CScene
{
private:
	map<wstring, LAYER>		m_mapLayer;
	vector<wstring>			m_vecLayerIdx;
	int						m_iLayerCnt;
	wstring					m_strSceneName;
	
	bool					m_bInit;

public:
	bool AddGameObject(CGameObject* _pObj, const wstring& _strLayerName);
	CGameObject* FindGameObject(wchar_t* _strTag);

	bool CreateLayer(wchar_t* _pLayerName);

public:
	void SetSceneName(wchar_t* _pSceneName)
	{
		m_strSceneName = _pSceneName;
	}

	void SetInit(bool _bInit)
	{
		m_bInit = _bInit;
	}

public:
	const wstring& GetSceneName()
	{
		return m_strSceneName;
	}

	const bool GetInit()
	{
		return m_bInit;
	}

public:
	int GetLayerIndex(wstring _strLayerName);
	CLayer* GetLayerFromIndex(int _iIdx);
	CLayer* GetLayerFromName(wstring _strLayerName);
	void GetGameObjectList(list<CGameObject*>& _pObjList);
	void GetParentGameObjectList(list<CGameObject*>& _pObjList);

	CGameObject* GetClickedObject(POINT _pt);

public:
	virtual void Init() = 0;
	void Awake();
	void Start();
	int Update();
	int LateUpdate();
	void Render();

public:
	CScene();
	virtual ~CScene();
};

