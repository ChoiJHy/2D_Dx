#pragma once
#include "Component.h"

class CAnimation;
class CTexture;
class CAnimator :
	public CComponent
{
private:
	map<wstring, CAnimation*>	m_mapAni;
	CAnimation*					m_pCurAni;

public:
	virtual int Update();
	virtual int LateUpdate();
	virtual CComponent* Clone();

public:
	CTexture* GetTexture();
	void GetAnimationList(vector<wstring>& _vecAnimation);

	CAnimation* GetCurAnimation()
	{
		return m_pCurAni;
	}

public:
	bool LoadAnimation(wstring _pFolderPath, wchar_t* _pAniKey);
	bool PlayAnimation(wchar_t* _pAniKey);

public:
	CAnimator();
	virtual ~CAnimator();
};

