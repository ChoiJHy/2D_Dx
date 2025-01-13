#pragma once
#include "value.h"

class CRes
{
private:
	int m_iRefCnt;
	wstring		m_strKey;

public:
	void SetKey(const wchar_t* _pTexKey)
	{
		m_strKey = _pTexKey;
	}

public:
	const wchar_t* GetKey()
	{
		return m_strKey.c_str();
	}

public:
	void AddRef()
	{
		m_iRefCnt += 1;
	}
	void DropRef()
	{
		m_iRefCnt -= 1;
	}

public:
	CRes();
	virtual ~CRes();
};

