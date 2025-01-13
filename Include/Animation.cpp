#include "stdafx.h"
#include "Animation.h"

#include "TimeMgr.h"
#include "Texture.h"

CAnimation::CAnimation()
	: m_fTerm(0.05f)
	, m_fAccTime(0.f)
	, m_iIdx(0)
{
}


CAnimation::~CAnimation()
{
}

int CAnimation::Update()
{
	m_fAccTime += DELTATIME;

	if (m_fTerm < m_fAccTime)
	{
		float fStride = m_fAccTime / m_fTerm;
		int iStride = (int)fStride;
		m_iIdx += iStride;
		m_fAccTime = m_fTerm * (fStride - (float)iStride);

		if (m_iIdx >= (int)m_vecTex.size())
		{
			m_iIdx = 0;
		}
	}

	return 0;
}

int CAnimation::LateUpdate()
{
	return 0;
}
