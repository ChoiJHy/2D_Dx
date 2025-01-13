#include "stdafx.h"
#include "Renderer.h"

#include "Mesh.h"
#include "Texture.h"
#include "Device.h"
#include "GameObject.h"
#include "Transform.h"

#include "ResMgr.h"
#include "Camera.h"


CRenderer::CRenderer()
	: m_pTexture(NULL)
	, m_pMesh(NULL)
{
	m_tMtrl.Ambient = { 1.f, 1.f, 1.f, 1.f };
	m_tMtrl.Diffuse = { 1.f, 1.f, 1.f, 1.f };
	m_tMtrl.Emissive= { 1.f, 1.f, 1.f, 1.f };
	m_tMtrl.Specular = { 1.f, 1.f, 1.f, 1.f };
	m_tMtrl.Power = 3.2f;
}


CRenderer::~CRenderer()
{
}


void CRenderer::Awake()
{
	m_pMesh = (CMesh*)CResMgr::GetInst()->Load<CMesh>(L"", L"DefaultMesh");
}

int CRenderer::Update()
{
	return 0;
}

int CRenderer::LateUpdate()
{
	return 0;
}

void CRenderer::Render()
{
	DEVICE->SetTransform(D3DTS_WORLD, &TRANSFORM->GetWorldMat());

	// 만약 GameObject가 Animator컴포넌트가 있다면
	// 1. Animator 에게 현재 재생되고 있는 Animator을 알아낸다.
	// 2. 해당 Animator에게 현재 출력할 텍스쳐가 누군지 알아낸다.
	// 3. 해당 텍스쳐를 장치에게 넘긴다.
	CTexture* pTex = NULL;

	if (GameObject()->Animator() != NULL)
		pTex = GameObject()->Animator()->GetTexture();
	else
		pTex = m_pTexture;

	if (pTex != NULL)
		DEVICE->SetTexture(0, pTex->GetTex());
	else
		DEVICE->SetTexture(0, NULL);


	DEVICE->SetMaterial(&m_tMtrl);


	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	//DEVICE->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	DEVICE->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	DEVICE->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	DEVICE->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
	
	//DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_BLENDFACTOR);
	//DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVBLENDFACTOR);

	//DEVICE->SetRenderState(D3DRS_BLENDFACTOR, D3DCOLOR_ARGB(0, 255, 255, 255));

	m_pMesh->Render();

	if (GameObject()->Collider())
		ColliderRender();
}


CComponent * CRenderer::Clone()
{
	return new CRenderer(*this);
}


void CRenderer::SetTex(CTexture * _pTexture)
{
	if(NULL != _pTexture)
		m_pTexture = _pTexture;
}

bool CRenderer::FadeOut(float _fDeltaTime, float _fSpeed, float _fa)
{
	if (m_tMtrl.Diffuse.a > _fa)
	{
		m_tMtrl.Diffuse.a -= _fDeltaTime / _fSpeed;
		return false;
	}
	else if(m_tMtrl.Diffuse.a <= _fa)
	{
		m_tMtrl.Diffuse.a = _fa;
		return true;
	}

	return false;
}

bool CRenderer::FadeIn(float _fDeltaTime, float _fSpeed, float _fa)
{
	if (m_tMtrl.Diffuse.a < _fa)
	{
		m_tMtrl.Diffuse.a += _fDeltaTime / _fSpeed;
		return false;
	}
	else if (m_tMtrl.Diffuse.a >= _fa)
	{
		m_tMtrl.Diffuse.a = _fa;
		return true;
	}

	return false;
}

void CRenderer::ColliderRender()
{
	CCollider* pCollider = GameObject()->Collider();

	if (pCollider->GetColliderType() == COLLIDER_TYPE::COLLIDER_RECTANGLE)
	{
		DrawRect();
	}
	else if (pCollider->GetColliderType() == COLLIDER_TYPE::COLLIDER_CIRCLE)
	{
		DrawCircle();
	}
}

void CRenderer::DrawRect()
{
	Vec3 vColliderPos = Vec3(0.f, 0.f, 0.f);
	Vec3 arrPos[5] = { Vec3() };

	//ColliderMatrix에 모든 상태값이 들어있기 떄문에 길이를 1로 만들어준다. 
	arrPos[0] = Vec3(vColliderPos.x - 0.5f, vColliderPos.y + 0.5f, vColliderPos.z);
	arrPos[1] = Vec3(vColliderPos.x + 0.5f, vColliderPos.y + 0.5f, vColliderPos.z);
	arrPos[2] = Vec3(vColliderPos.x + 0.5f, vColliderPos.y - 0.5f, vColliderPos.z);
	arrPos[3] = Vec3(vColliderPos.x - 0.5f, vColliderPos.y - 0.5f, vColliderPos.z);
	arrPos[4] = Vec3(vColliderPos.x - 0.5f, vColliderPos.y + 0.5f, vColliderPos.z);

	Matrix mat = GameObject()->Collider()->GetColliderMatrix() * CCamera::GetInst()->GetViewMat() * CCamera::GetInst()->GetProjMat();
	for (int i = 0; i < 4; ++i)
	{
		CDevice::GetInst()->GetLine()->DrawTransform(arrPos + i, 2, &mat, D3DCOLOR_ARGB(255, 0, 0, 255));
	}
}

void CRenderer::DrawCircle()
{
	Vec2 vColliderPos = Vec2(0.f, 0.f);
	Vec3 arrPos[37] = { Vec3() };

	//ColliderMatrix에 모든 상태값이 들어있기 떄문에 길이를 1로 만들어준다. 
	for (int i = 0; i < 36; ++i)
	{
		vColliderPos = AngleToDist(10 * i, 0.5f);
		arrPos[i] = Vec3(vColliderPos.x, vColliderPos.y, 0.f);
	}

	arrPos[36] = arrPos[0];

	Matrix mat = GameObject()->Collider()->GetColliderMatrix() * CCamera::GetInst()->GetViewMat() * CCamera::GetInst()->GetProjMat();
	for (int i = 0; i < 36; ++i)
	{
		CDevice::GetInst()->GetLine()->DrawTransform(arrPos + i, 2, &mat, D3DCOLOR_ARGB(255, 0, 0, 255));
	}
}

Vec2 CRenderer::AngleToDist(float _fAngle, float _fDist)
{
	Vec2 vPos = Vec2(0.f, 0.f);
	float fRadian = D3DXToRadian(_fAngle);
	vPos.x = _fDist * cosf(fRadian);
	vPos.y = _fDist * sinf(fRadian);

	return vPos;
}
