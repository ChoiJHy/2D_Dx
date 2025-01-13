#pragma once

enum KEY_STATE
{
	STATE_NONE,
	STATE_TAP,
	STATE_PUSH,
	STATE_AWAY,
	STATE_END,
};
class CKeyMgr
{
private:
	map<int, KEY_STATE>		m_mapKey;

public:
	void Init();
	int Update();

public:
	KEY_STATE GetKey(int _iKeyVal)
	{
		map<int, KEY_STATE>::iterator iter = m_mapKey.find(_iKeyVal);
		if (iter != m_mapKey.end())
			return iter->second;
		return STATE_END;
	}

	bool GetKey(int _iKeyVal, KEY_STATE _eState)
	{
		map<int, KEY_STATE>::iterator iter = m_mapKey.find(_iKeyVal);
		if (iter != m_mapKey.end())
		{
			if (iter->second == _eState)
				return true;
		}

		return false;
	}

public:
	static CKeyMgr* GetInst()
	{
		static CKeyMgr key;
		return &key;
	}
private:
	CKeyMgr();
	~CKeyMgr();
};

