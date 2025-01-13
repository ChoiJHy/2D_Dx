#pragma once
class CTimeMgr
{
private:
	LARGE_INTEGER	m_tSecond;
	LARGE_INTEGER	m_tTime;

	float			m_fDeltaTime;
	float			m_fOldDeltaTime;
	float			m_fAccTime;

public:
	void Init();
	void Update();

public:
	float DeltaTime()
	{
		return m_fDeltaTime;
	}

public:
	static CTimeMgr* GetInst()
	{
		static CTimeMgr TimeMgr;
		return &TimeMgr;
	}
private:
	CTimeMgr();
	~CTimeMgr();
};

