#pragma once

#include "value.h"

class CGameObject;
class CCore
{
private:
	CGameObject*	m_pObj;
	HWND			m_hWnd;

public:
	int Init(HWND _hWnd, bool _bWindowMode);
	int Run();

private:
	int Update();
	int LateUpdate();
	void Render();

public:
	HWND GetHWND()
	{
		return m_hWnd;
	}

public:
	static CCore* GetInst()
	{
		static CCore core;
		return &core;
	}

private:
	CCore();
	~CCore();
};

