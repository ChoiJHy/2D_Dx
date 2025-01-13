#pragma once
#include "Component.h"

#include "RsPtr.h"

class CMesh;
class CTexture;

class CRenderer :
	public CComponent
{
private:
	CRsPtr<CMesh>		m_pMesh;
	CRsPtr<CTexture>	m_pTexture;
	D3DMATERIAL9		m_tMtrl;

public:
	virtual void Awake();
	virtual int Update();
	virtual int LateUpdate();
	void Render();
	
public:
	virtual CComponent* Clone();

public:
	CTexture* GetTex()
	{
		return m_pTexture;
	}

	CMesh* GetMesh()
	{
		return m_pMesh;
	}

public:
	void SetTex(CTexture* _pTexture);
	void SetAlpha(float _a)
	{
		m_tMtrl.Diffuse.a = _a;
	}

public:
	bool FadeOut(float _fDeltaTime, float _fSpeed, float _fa = 0.f);
	bool FadeIn(float _fDeltaTime, float _fSpeed, float _fa = 1.f);

private:
	void ColliderRender();
	void DrawRect();
	void DrawCircle();

	Vec2 AngleToDist(float _fAngle, float _fDist);
public:
	CRenderer();
	virtual ~CRenderer();
};

