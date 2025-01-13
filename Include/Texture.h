#pragma once
#include "Res.h"
class CTexture :
	public CRes
{
private:
	LPDIRECT3DTEXTURE9		m_pTex;
	wstring					m_strFullPath;

public:
	bool Load(const wchar_t* _pTexPath);


public:
	LPDIRECT3DTEXTURE9 GetTex()
	{
		return m_pTex;
	}

public:
	CTexture();
	virtual ~CTexture();
};

