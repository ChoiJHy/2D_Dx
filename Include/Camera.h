#pragma once
#include "struct.h"

class CGameObject;
class CCamera
{
private:
	Vec3			m_vPos;
	Matrix			m_matView;
	Matrix			m_matProj;

public:
	void Init();
	int Update();

public:
	void SetMatrix();
	void SetPos(Vec3 _vPos)
	{
		m_vPos = _vPos;
	}

public:
	Matrix GetViewMat()
	{
		return m_matView;
	}

	Matrix GetProjMat()
	{
		return m_matProj;
	}

	Vec3 GetPos()
	{
		return m_vPos;
	}


public:
	static CCamera* GetInst()
	{
		static CCamera cam;
		return &cam;
	}

private:
	CCamera();
	~CCamera();
};

