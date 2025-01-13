#pragma once
class CDevice
{
private:
	HWND					m_hWnd;	
	LPDIRECT3D9				m_pD3D;	// IDirect3D9 장치정보를 얻어오는 기능을 수행
	D3DCAPS9				m_tCaps; // 알아낸 장치의 정보를 저장할 구조체

	LPDIRECT3DDEVICE9		m_pDevice; //IDirect3DDevice9 장치를 대표하는 객체
	D3DPRESENT_PARAMETERS	m_tPresent; //장치 초기화 시 필요한 값들을 셋팅

	LPD3DXFONT				m_pFont;
	LPD3DXLINE				m_pLine;
	D3DLIGHT9				m_Light;

public:
	bool Init(HWND _hWnd, bool _bWindowMode = true);

	LPDIRECT3DDEVICE9 GetDevice()
	{
		return m_pDevice;
	}

	LPD3DXFONT GetFont()
	{
		return m_pFont;
	}

	LPD3DXLINE GetLine()
	{
		return m_pLine;
	}

	HWND GetMainHWND()
	{
		return m_hWnd;
	}

private:
	void SetPresent(bool _bWindowMode
		, D3DFORMAT _fmt = D3DFMT_A8R8G8B8
		, bool _bDepth = true
		, D3DFORMAT _DepthFmt = D3DFMT_D24S8);

public:
	static CDevice* GetInst()
	{
		static CDevice dev;
		return &dev;
	}

	

private:
	CDevice();
	~CDevice();
};

