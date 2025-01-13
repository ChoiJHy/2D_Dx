#include "stdafx.h"
#include "Device.h"

#include "define.h"

CDevice::CDevice()
	: m_hWnd(NULL)
	, m_pD3D(NULL)
	, m_pDevice(NULL)
	, m_pFont(NULL)
	, m_pLine(NULL)
{
}


CDevice::~CDevice()
{
	if (NULL != m_pD3D)
		m_pD3D->Release();

	if (NULL != m_pDevice)
		m_pDevice->Release();

	if (NULL != m_pFont)
		m_pFont->Release();

	if (NULL != m_pLine)
		m_pLine->Release();
}

bool CDevice::Init(HWND _hWnd, bool _bWindowMode)
{
	m_hWnd = _hWnd;

	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(FAILED(m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &m_tCaps)))
		return false;

	DWORD dwProcessing = 0;
	if (m_tCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		dwProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		dwProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	SetPresent(_bWindowMode);

	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL
		, m_hWnd, dwProcessing | D3DCREATE_MULTITHREADED
		, &m_tPresent, &m_pDevice)))
	{
		MessageBox(m_hWnd, L"오류", L"장치 초기화 실패", MB_OK);
		return false;
	}

	// Cull 모드 끔
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//깊이 버퍼 사용을 하지 않는다./ 출력 순서대로 우선순위 결정
	DEVICE->SetRenderState(D3DRS_ZENABLE, false);
	//  빛 사용
	DEVICE->SetRenderState(D3DRS_LIGHTING, true);

	memset(&m_Light, 0, sizeof(D3DLIGHT9));
	m_Light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	
	m_Light.Direction = Vec3(0.f, 0.f, 0.f);
	m_Light.Type = D3DLIGHT_DIRECTIONAL;

	DEVICE->SetLight(0, &m_Light);
	DEVICE->LightEnable(0, true);



	// Font 초기화
	D3DXCreateFont(m_pDevice,//D3D Device
		22,//Font height
		0,//Font width
		FW_NORMAL, //Font Weight
		1,  //MipLevels
		false,            //Italic
		DEFAULT_CHARSET,  //CharSet
		OUT_DEFAULT_PRECIS, //OutputPrecision
		ANTIALIASED_QUALITY, //Quality
		DEFAULT_PITCH | FF_DONTCARE,//PitchAndFamily
		L"Arial",          //pFacename,
		&m_pFont);         //ppFont

	 // Line 초기화
	D3DXCreateLine(m_pDevice, &m_pLine);

	return true;
}

void CDevice::SetPresent(bool _bWindowMode, D3DFORMAT _fmt, bool _bDepth, D3DFORMAT _DepthFmt)
{

	m_tPresent.BackBufferWidth = WINSIZE_X;
	m_tPresent.BackBufferHeight = WINSIZE_Y;
	m_tPresent.BackBufferCount = 1;
	m_tPresent.BackBufferFormat = _fmt;

	m_tPresent.EnableAutoDepthStencil = _bDepth;
	m_tPresent.AutoDepthStencilFormat = _DepthFmt;

	m_tPresent.Flags = 0;
	m_tPresent.Windowed = _bWindowMode;
	m_tPresent.hDeviceWindow = m_hWnd;
	m_tPresent.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

	m_tPresent.MultiSampleQuality = 0;
	m_tPresent.MultiSampleType = D3DMULTISAMPLE_NONE;

	m_tPresent.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	m_tPresent.SwapEffect = D3DSWAPEFFECT_DISCARD;

}
