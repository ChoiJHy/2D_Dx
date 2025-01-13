
// MainFrm.h : CMainFrame 클래스의 인터페이스
//

#pragma once


class CMainFrame : public CFrameWnd
{
	
public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

// 구현입니다.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	CSplitterWnd m_MainSplit;
	//CMainView    m_wndView;

public:
	HWND GetMainViewHWND()
	{
		return m_MainSplit.GetPane(0, 0)->m_hWnd;
	}
	CWnd* GetHierachyView()
	{
		return m_MainSplit.GetPane(0, 1);
	}
	CWnd* GetComView()
	{
		return m_MainSplit.GetPane(0, 2);
	}

// 생성된 메시지 맵 함수
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnDestroy();
};


