#include "stdafx.h"
#include "Texture.h"

#include "Device.h"

CTexture::CTexture()
	: m_pTex(NULL)
{
}


CTexture::~CTexture()
{
	if (NULL != m_pTex)
		m_pTex->Release();
}

bool CTexture::Load(const wchar_t * _pTexPath)
{
	if (FAILED(D3DXCreateTextureFromFile(DEVICE, _pTexPath, &m_pTex)))
	{
		return false;
	}

	m_strFullPath = _pTexPath;
	return true;
}