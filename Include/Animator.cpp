#include "stdafx.h"
#include "Animator.h"

#include "Animation.h"
#include "ResMgr.h"

CAnimator::CAnimator()
{
}


CAnimator::~CAnimator()
{
	map<wstring, CAnimation*>::iterator iter = m_mapAni.begin();
	for (; iter != m_mapAni.end(); ++iter)
	{
		delete iter->second;
	}
}

int CAnimator::Update()
{
	if (NULL != m_pCurAni)
		m_pCurAni->Update();
	return 0;
}

int CAnimator::LateUpdate()
{
	if (NULL != m_pCurAni)
		m_pCurAni->LateUpdate();
	return 0;
}

CComponent * CAnimator::Clone()
{
	return new CAnimator(*this);
}

CTexture * CAnimator::GetTexture()
{
	if (NULL != m_pCurAni)
		return m_pCurAni->GetCurFrame();
	return nullptr;
}

void CAnimator::GetAnimationList(vector<wstring>& _vecAnimation)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAni.begin();
	map<wstring, CAnimation*>::iterator iterEnd = m_mapAni.end();
	for (; iter != iterEnd; ++iter)
	{
		_vecAnimation.push_back(iter->first);
	}
}

bool CAnimator::LoadAnimation(wstring _pFolderPath, wchar_t * _pAniKey)
{
	WIN32_FIND_DATA fd;
	HANDLE hFind = FindFirstFile(wstring(_pFolderPath + L"\\*.*").c_str(), &fd);

	if (INVALID_HANDLE_VALUE == hFind)
		return false;

	CAnimation* pAni = new CAnimation;

	while (FindNextFile(hFind, &fd))
	{
		wstring strFullPath = _pFolderPath;
		strFullPath += L"\\";
		strFullPath += fd.cFileName;

		CTexture* pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(strFullPath.c_str(), fd.cFileName);
		pAni->AddTexture(pTex);
	}
	m_mapAni.insert(make_pair(_pAniKey, pAni));
	pAni->SetKey(_pAniKey);

	return true;
}

bool CAnimator::PlayAnimation(wchar_t * _pAniKey)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAni.find(_pAniKey);
	if (iter == m_mapAni.end())
		return false;

	m_pCurAni = iter->second;
	m_pCurAni->Reset();

	return true;
}
