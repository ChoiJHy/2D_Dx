#pragma once
#include "Res.h"

template<typename T>
class CRsPtr
{
private:
	T*			m_pRes;


public:
	void operator =(T* _pRes)
	{
		m_pRes = _pRes;
		if(NULL != m_pRes)
			m_pRes->AddRef();
	}

	void operator =(const CRsPtr& _other)
	{
		m_pRes = _other.m_pRes;
		if (NULL != m_pRes)
			m_pRes->AddRef();
	}

	T* operator ->()
	{
		return m_pRes;
	}

	//CRsPtr이 T*형인 척 한다.
	operator T*()
	{
		return m_pRes;
	}
public:
	CRsPtr() : m_pRes(NULL)
	{
	}

	CRsPtr(T* _pRes) : m_pRes(_pRes)
	{
		if (NULL != m_pRes)
			m_pRes->AddRef();
	}

	CRsPtr(const CRsPtr& _other)
	{
		m_pRes = _other.m_pRes;
		if (NULL != m_pRes)
			m_pRes->AddRef();
	}
	~CRsPtr()
	{
		if (NULL != m_pRes)
			m_pRes->DropRef();
	}
};

