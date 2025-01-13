#pragma once

#include "RsPtr.h"

class CTexture;

class CAnimation
{
private:
	vector<CRsPtr<CTexture>>		m_vecTex;
	float							m_fTerm;
	float							m_fAccTime;
	int								m_iIdx;

	wstring							m_strKey;

public:
	int Update();
	int LateUpdate();

public:
	void AddTexture(CTexture* _pTex)
	{
		if (NULL != _pTex)
			m_vecTex.push_back(_pTex);
	}

public:
	CTexture* GetCurFrame()
	{
		return m_vecTex[m_iIdx];
	}

	wstring GetKey()
	{
		return m_strKey;
	}

public:
	void SetKey(wstring _strKey)
	{
		m_strKey = _strKey;
	}

public:
	void Reset()
	{
		m_iIdx = 0;
		m_fAccTime = 0.f;
	}

public:
	CAnimation();
	~CAnimation();
};

