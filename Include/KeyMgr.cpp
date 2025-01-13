#include "stdafx.h"
#include "KeyMgr.h"


CKeyMgr::CKeyMgr()
{
}


CKeyMgr::~CKeyMgr()
{
}

void CKeyMgr::Init()
{
	m_mapKey.insert(make_pair('1', STATE_NONE)); m_mapKey.insert(make_pair('2', STATE_NONE)); m_mapKey.insert(make_pair('3', STATE_NONE));
	m_mapKey.insert(make_pair('4', STATE_NONE)); m_mapKey.insert(make_pair('5', STATE_NONE)); m_mapKey.insert(make_pair('6', STATE_NONE));
	m_mapKey.insert(make_pair('7', STATE_NONE)); m_mapKey.insert(make_pair('8', STATE_NONE)); m_mapKey.insert(make_pair('9', STATE_NONE));
	m_mapKey.insert(make_pair('Q', STATE_NONE)); m_mapKey.insert(make_pair('W', STATE_NONE)); m_mapKey.insert(make_pair('E', STATE_NONE));
	m_mapKey.insert(make_pair('R', STATE_NONE)); m_mapKey.insert(make_pair('T', STATE_NONE)); m_mapKey.insert(make_pair('Y', STATE_NONE));
	m_mapKey.insert(make_pair('U', STATE_NONE)); m_mapKey.insert(make_pair('I', STATE_NONE)); m_mapKey.insert(make_pair('O', STATE_NONE));
	m_mapKey.insert(make_pair('P', STATE_NONE)); m_mapKey.insert(make_pair('A', STATE_NONE)); m_mapKey.insert(make_pair('S', STATE_NONE));
	m_mapKey.insert(make_pair('D', STATE_NONE)); m_mapKey.insert(make_pair('F', STATE_NONE)); m_mapKey.insert(make_pair('G', STATE_NONE));
	m_mapKey.insert(make_pair('H', STATE_NONE)); m_mapKey.insert(make_pair('J', STATE_NONE)); m_mapKey.insert(make_pair('K', STATE_NONE));
	m_mapKey.insert(make_pair('L', STATE_NONE)); m_mapKey.insert(make_pair('Z', STATE_NONE)); m_mapKey.insert(make_pair('X', STATE_NONE));
	m_mapKey.insert(make_pair('C', STATE_NONE)); m_mapKey.insert(make_pair('V', STATE_NONE)); m_mapKey.insert(make_pair('B', STATE_NONE));
	m_mapKey.insert(make_pair('N', STATE_NONE)); m_mapKey.insert(make_pair('M', STATE_NONE));
	m_mapKey.insert(make_pair(VK_F1, STATE_NONE)); m_mapKey.insert(make_pair(VK_F2, STATE_NONE)); m_mapKey.insert(make_pair(VK_F3, STATE_NONE));
	m_mapKey.insert(make_pair(VK_F4, STATE_NONE)); m_mapKey.insert(make_pair(VK_F5, STATE_NONE)); m_mapKey.insert(make_pair(VK_F6, STATE_NONE));
	m_mapKey.insert(make_pair(VK_F7, STATE_NONE)); m_mapKey.insert(make_pair(VK_F8, STATE_NONE)); m_mapKey.insert(make_pair(VK_F9, STATE_NONE));

	m_mapKey.insert(make_pair(VK_LEFT, STATE_NONE)); m_mapKey.insert(make_pair(VK_RIGHT, STATE_NONE)); m_mapKey.insert(make_pair(VK_UP, STATE_NONE)); m_mapKey.insert(make_pair(VK_DOWN, STATE_NONE));
	m_mapKey.insert(make_pair(VK_SPACE, STATE_NONE)); m_mapKey.insert(make_pair(VK_RETURN, STATE_NONE)); m_mapKey.insert(make_pair(VK_ESCAPE, STATE_NONE)); m_mapKey.insert(make_pair(VK_SHIFT, STATE_NONE));

	m_mapKey.insert(make_pair(VK_LBUTTON, STATE_NONE)); m_mapKey.insert(make_pair(VK_RBUTTON, STATE_NONE));
}

int CKeyMgr::Update()
{
	map<int, KEY_STATE>::iterator iter = m_mapKey.begin();
	map<int, KEY_STATE>::iterator iterEnd = m_mapKey.end();

	for (; iter != iterEnd; ++iter)
	{
		if (GetAsyncKeyState(iter->first) & 0x8000)
		{
			if (iter->second == STATE_NONE)
				iter->second = STATE_TAP;
			else if (iter->second == STATE_TAP)
				iter->second = STATE_PUSH;
		}
		else
		{
			if (iter->second == STATE_TAP || iter->second == STATE_PUSH)
				iter->second = STATE_AWAY;
			else if (iter->second == STATE_AWAY)
			{
				iter->second = STATE_NONE;
			}
		}
	}
	return 0;
}
