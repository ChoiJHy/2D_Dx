#pragma once

#include "stdafx.h"

#define WINSIZE_X 1366
#define WINSIZE_Y 768

typedef	D3DXVECTOR2			Vec2;
typedef D3DXVECTOR3			Vec3;
typedef D3DXVECTOR4			Vec4;
typedef D3DXMATRIXA16		Matrix;

#define DEVICE CDevice::GetInst()->GetDevice()
#define DELTATIME CTimeMgr::GetInst()->DeltaTime()
#define KEY CKeyMgr::GetInst()->GetKey

#define SAFE_DELETE(p)	if(NULL != p) { delete p; p = NULL; }
#define SAFE_DELETE_ARR(p) if(NULL != p) {delete[] p; p = NULL; }

enum COMPONENT_TYPE
{
	COM_TRANSFORM,
	COM_RENDERER,
	COM_ANIMATOR,
	COM_COLLIDER,
	COM_END,
};

enum class COLLIDER_TYPE
{
	COLLIDER_CIRCLE,
	COLLIDER_RECTANGLE,
	COLLIDER_POINT,
};

enum SOUND_TYPE
{
	SD_DRUM_NORMAL,
	SD_DRUM_CLAP,
	SD_DRUM_FINISH,
	SD_DRUM_WHISTLE,

	//섹션 성공, 실패
	SD_SECTION_PASS,
	SD_SECTION_FAIL,

	SD_COMBOBREAK, // 콤보 깨질때 
	SD_FAIL, // 곡 실패
	SD_SUCCESS,

	SD_MENU_BACK, // 메뉴 뒤로가기
	SD_MENU_CLICK, // 메뉴 클릭
	SD_MENU_HIT, // 메뉴 아이콘 건드릴 때
	SD_READY,// 준비 버튼 눌렀을때 

	SD_SPINNER_SPIN, // 스핀 돌아가는 사운드
	SD_SPINNER_BONUS, // 스핀 성공 후 보너스 점수 올라가는 소리

	SD_END
};

enum STREAM_STATE
{
	SS_PLAY,
	SS_PAUSE,
	SS_STOP,
	SS_END
};