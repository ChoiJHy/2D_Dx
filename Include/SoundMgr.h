#pragma once
#include "define.h"
#include <fmod.hpp>

#define MAX_STREAM	30

class CSoundMgr
{
private:
	FMOD::System*	m_pSystem;
	FMOD::Sound*	m_pSound[SD_END]; // 효과음 개수만큼 가지고 있어야 한다. 
	FMOD::Sound*	m_pStream[MAX_STREAM]; // 배경음 갯수만큼 가지고 있어야 한다. 
	map<wstring, FMOD::Sound*>	m_mapStream; // 배경음을 이름으로 관리하기 위한 map

	int m_iStreamCnt; // StreamIndex

	FMOD::Channel*	m_pChannelStream; // 배경음 전용 채널
	FMOD::Channel*	m_pChannelSound; // 효과음 전용 채널 

	STREAM_STATE	m_eStreamState;
	
	FMOD_RESULT	result;
public:
	void Init();
	void Update();

public:
	void SoundLoad(wstring _path, SOUND_TYPE _type);
	void StreamLoad(wstring _path, wstring _Name);

	void PlaySound(SOUND_TYPE _type);
	void PlayStream(wstring _Name);

	void StopStream();
	void SetPause(bool _bPause);



private:
	void ErrorCheck(FMOD_RESULT _r);

private:
	FMOD::Sound* GetStream(wstring _Name);

	STREAM_STATE GetState()
	{
		return m_eStreamState;
	}
public:
	static CSoundMgr* GetInst()
	{
		static CSoundMgr SoundMgr;
		return &SoundMgr;
	}
private:
	CSoundMgr();
	~CSoundMgr();
};

