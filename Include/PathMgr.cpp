#include "stdafx.h"
#include "PathMgr.h"

wchar_t CPathMgr::m_arrPath[MAX_PATH] = { 0 };

wchar_t * CPathMgr::GetResourcesPath()
{
	GetCurrentDirectory(MAX_PATH, m_arrPath);

	int iLen = wcslen(m_arrPath);

	
	for (int i = iLen - 1; i > 0; --i)
	{
		// 실행결로를 뒤에서 부터 돌면서 \을 만날때까지 돌린다 .
		if (m_arrPath[i] == L'\\')
		{
			// \만나면 그 뒷부분을 모두 지운다.
			wmemset(m_arrPath + i + 1, L'\0', iLen - (i + 1));
			break;
		}
	}

	
	wcscat_s(m_arrPath, MAX_PATH, L"Bin\\Resources\\");

	return m_arrPath;
}

