// GameView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "OsuEditor.h"
#include "GameView.h"

#include "MainFrm.h"

#include "../Include/SceneMgr.h"
#include "../Include/Scene.h"

#include "MyMessage.h"


// CGameView

IMPLEMENT_DYNCREATE(CGameView, CFormView)

CGameView::CGameView()
	: CFormView(IDD_GAMEVIEW)
{

}

CGameView::~CGameView()
{
}

void CGameView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGameView, CFormView)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CGameView 진단입니다.

#ifdef _DEBUG
void CGameView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CGameView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CGameView 메시지 처리기입니다.


void CGameView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.


	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	CGameObject* pObj = pCurScene->GetClickedObject(point);

	// 찾은 오브젝트의 주소값을 HierachyView로 넘겨준다. 
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	HWND hWnd = pFrame->GetHierachyView()->m_hWnd;
	::SendMessage(hWnd, MM_HIGHLIGHT, (WPARAM)pObj, 0);

	hWnd = pFrame->GetComView()->m_hWnd;
	::SendMessage(hWnd, MM_SELOBJ, (WPARAM)pObj, 0);

	

	CFormView::OnLButtonDown(nFlags, point);
}
