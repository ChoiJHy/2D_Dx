#include "stdafx.h"
#include "TimeMgr.h"


CTimeMgr::CTimeMgr()
	: m_fDeltaTime(0.f)
	, m_fOldDeltaTime(1.f)
	, m_fAccTime(0.f)
{
}


CTimeMgr::~CTimeMgr()
{
}

void CTimeMgr::Init()
{
	QueryPerformanceFrequency(&m_tSecond);
	QueryPerformanceCounter(&m_tTime);
}

void CTimeMgr::Update()
{
	LARGE_INTEGER tTime;
	QueryPerformanceCounter(&tTime);

	m_fDeltaTime = (float)(tTime.QuadPart - m_tTime.QuadPart) / (float)m_tSecond.QuadPart;

	if (m_fDeltaTime > m_fOldDeltaTime * 100.f)
		m_fDeltaTime = m_fOldDeltaTime;

	m_fOldDeltaTime = m_fDeltaTime;

	m_fAccTime += m_fDeltaTime;

	if (m_fAccTime >= 1.f)
	{
		QueryPerformanceFrequency(&m_tSecond);
		m_fAccTime = 0.f;
	}

	m_tTime = tTime;
}
