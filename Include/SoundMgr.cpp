#include "stdafx.h"
#include "SoundMgr.h"

#include <fmod_errors.h>

CSoundMgr::CSoundMgr()
	:m_iStreamCnt(0)
	, m_pSystem(NULL)
	, m_pChannelSound(NULL)
	, m_pChannelStream(NULL)
	, m_eStreamState(SS_STOP)
{
	// 초기에 모든 사운드 포인터를 NULL로 초기화 해준다. 
	for (int i = 0; i < SD_END; ++i)
	{
		m_pSound[i] = NULL;
	}

	for (int i = 0; i < MAX_STREAM; ++i)
	{
		m_pStream[i] = NULL;
	}
}


CSoundMgr::~CSoundMgr()
{
	// 마지막에 모든  SOUND와 SYSTEM을 지워준다. 
	for (int i = 0; i < SD_END; ++i)
	{
		if (m_pSound[i] != NULL)
		{
			result = m_pSound[i]->release();
			ErrorCheck(result);
		}
	}

	for (int i = 0; i < MAX_STREAM; ++i)
	{
		if (m_pStream[i] != NULL)
		{
			result = m_pStream[i]->release();
			ErrorCheck(result);
		}
	}

	result = m_pSystem->close();
	ErrorCheck(result);
	result = m_pSystem->release();
	ErrorCheck(result);

	
}

void CSoundMgr::ErrorCheck(FMOD_RESULT _r)
{
	if (_r != FMOD_OK)
	{
		TCHAR szStr[256] = { 0 };
		MultiByteToWideChar(CP_ACP, NULL, FMOD_ErrorString(_r), -1, szStr, 256);
		MessageBox(NULL, szStr, L"Sound Error", MB_OK);
	}
}

FMOD::Sound * CSoundMgr::GetStream(wstring _Name)
{
	map<wstring, FMOD::Sound*>::iterator iter = m_mapStream.find(_Name);

	if (iter == m_mapStream.end())
		return NULL;

	return iter->second;
}

void CSoundMgr::Init()
{
	result = FMOD::System_Create(&m_pSystem);
	ErrorCheck(result);
	result = m_pSystem->init(64, FMOD_INIT_NORMAL, NULL);
	ErrorCheck(result);
}

void CSoundMgr::Update()
{
	m_pSystem->update();
}

void CSoundMgr::SoundLoad(wstring _path, SOUND_TYPE _type)
{
	char path[MAX_PATH];
	WideCharToMultiByte(CP_ACP, 0, _path.c_str(), -1, path, MAX_PATH, 0, 0);
	result = m_pSystem->createSound(path, FMOD_DEFAULT, NULL, &m_pSound[_type]);
	ErrorCheck(result);
}

void CSoundMgr::StreamLoad(wstring _path, wstring _Name)
{
	map<wstring, FMOD::Sound*>::iterator iter = m_mapStream.find(_Name);

	if (iter != m_mapStream.end())
		return;

	char path[MAX_PATH];
	WideCharToMultiByte(CP_ACP, 0, _path.c_str(), -1, path, MAX_PATH, 0, 0);
	result = m_pSystem->createStream(path, FMOD_LOOP_OFF| FMOD_2D, NULL, &m_pStream[m_iStreamCnt]);
	ErrorCheck(result);

	// 정상적으로 Stream이 만들어 졌다면 
	if (!result)
	{
		//그 스트림을 map에 이름과 함께 넣어준다.
		m_mapStream.insert(make_pair(_Name, m_pStream[m_iStreamCnt++]));
	}
}

void CSoundMgr::PlaySound(SOUND_TYPE _type)
{
	// 타입에 맞는 사운드를 사운드채널을 이용해서 재생 
	if (NULL != m_pSound[_type])
	{
		result = m_pSystem->playSound(m_pSound[_type], NULL, false, &m_pChannelSound);
		ErrorCheck(result);
	}
}

void CSoundMgr::PlayStream(wstring _Name)
{
	// 들어온 이름이 있다면 그 스트림을 찾아서 스트림채널로 재생
	if (!m_pChannelStream)
	{
		m_eStreamState = SS_PLAY;
		result = m_pSystem->playSound(GetStream(_Name), 0, false, &m_pChannelStream);
		ErrorCheck(result);
	}
}

void CSoundMgr::StopStream()
{
	if (m_eStreamState == SS_PLAY || m_eStreamState == SS_PAUSE)
	{
		m_eStreamState = SS_STOP;
		result = m_pChannelStream->stop();
		ErrorCheck(result);

		m_pChannelStream = NULL;
	}
}

void CSoundMgr::SetPause(bool _bPause)
{
	// 일시정지 하라고 명령이 들어왔는데 
	if (_bPause)
	{
		//현재 상태가 플레이 중이라면
		if (m_eStreamState == SS_PLAY)
		{
			//스트림채널을 일시정지 시킨다.
			m_eStreamState = SS_PAUSE;
			result = m_pChannelStream->setPaused(true);
			ErrorCheck(result);
		}
		else
		{
			// 현재 상태가 플레이 이외의 상태라면 아무 일도 하지 않는다. 
			return;
		}
	}
	// 일시정지를 해제하라고 명령이 들어왔는데
	else
	{
		//현재 상태가 일시정지라면
		if (m_eStreamState == SS_PAUSE)
		{
			// 스트림채널의 일시정지를 해제한다.
			m_eStreamState = SS_PLAY;
			result = m_pChannelStream->setPaused(false);
			ErrorCheck(result);
		}
		// 현재 상태가 일시정지 이외의 상태라면 
		else
		{
			//아무일도 하지 않고 함수를 종료한다. 
			return;
		}
	}
}
