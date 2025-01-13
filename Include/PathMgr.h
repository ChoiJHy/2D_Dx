#pragma once
class CPathMgr
{
private:
	static wchar_t m_arrPath[MAX_PATH];

public:
	static wchar_t* GetResourcesPath();


private:
	CPathMgr() {};
	~CPathMgr() {};
};

