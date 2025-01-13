#include "stdafx.h"
#include "Camera.h"

#include "Device.h"

#include "Core.h"
#include "ResMgr.h"

#include "GameObject.h"

CCamera::CCamera()
{
	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matProj);
}


CCamera::~CCamera()
{

}

void CCamera::Init()
{
	//원근투영 
	//D3DXMatrixPerspectiveFovLH(&m_matProj, D3DX_PI / 4.f, WINSIZE_X / WINSIZE_Y, 1, 1000);

	//직교투영
	D3DXMatrixOrthoLH(&m_matProj, WINSIZE_X, WINSIZE_Y, 0, 1000);

}

int CCamera::Update()
{

	memcpy(&m_matView._41, &Vec3(-m_vPos), sizeof(Vec3));
	return 0;
}

void CCamera::SetMatrix()
{
	DEVICE->SetTransform(D3DTS_VIEW, &m_matView);
	DEVICE->SetTransform(D3DTS_PROJECTION, &m_matProj);
}

