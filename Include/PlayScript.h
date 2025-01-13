#pragma once
#include "Script.h"
class CPlayScript :
	public CScript
{
public:
	bool	m_bPause;

	wstring		m_strStreamName;

	float	m_fAR;
	float	m_fHPDrain;
	float	m_fCS;
	
public:
	void SetStreamName(wstring _strStreamName)
	{
		m_strStreamName = _strStreamName;
	}


public:
	virtual void Start();
	virtual int Update();
	virtual int LateUpdate();

public:
	virtual CComponent* Clone()
	{
		return new CPlayScript(*this);
	}
public:
	CPlayScript();
	~CPlayScript();
};

