// ComView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "OsuEditor.h"
#include "ComView.h"

#include "TransformDlg.h"
#include "RendererDlg.h"
#include "ColliderDlg.h"
#include "AnimatorDlg.h"

#include "MyMessage.h"

#include "../Include/GameObject.h"


// CComView

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#undef THIS_FILE
//static char THIS_FILE[] = __FILE__;
//#endif

IMPLEMENT_DYNCREATE(CComView, CScrollView)

CComView::CComView()
	: m_pTransDlg(NULL)
	, m_pRendererDlg(NULL)
	, m_pColliderDlg(NULL)
	, m_pAnimatorDlg(NULL)
{

}

CComView::~CComView()
{

}


BEGIN_MESSAGE_MAP(CComView, CScrollView)
	ON_WM_DESTROY()
	ON_MESSAGE(MM_SELOBJ, &CComView::OnSelectedObject)
END_MESSAGE_MAP()


// CComView 그리기입니다.

void CComView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);

	// Transform 다이얼로그를 자식으로 등록한다. 
	m_pTransDlg = new CTransformDlg;
	m_pTransDlg->Create(IDD_TRANSFORM, this);
	m_pTransDlg->ShowWindow(SW_HIDE);

	// Renderer다이얼로그를 자식으로 등록합니다.
	m_pRendererDlg = new CRendererDlg;
	m_pRendererDlg->Create(IDD_RENDERER, this);
	m_pRendererDlg->ShowWindow(SW_HIDE);

	m_pColliderDlg = new CColliderDlg;
	m_pColliderDlg->Create(IDD_COLLIDER, this);
	m_pColliderDlg->ShowWindow(SW_HIDE);

	m_pAnimatorDlg = new CAnimatorDlg;
	m_pAnimatorDlg->Create(IDD_ANIMATOR, this);
	m_pAnimatorDlg->ShowWindow(SW_HIDE);
}

void CComView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// CComView 진단입니다.

#ifdef _DEBUG
void CComView::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void CComView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG


// CComView 메시지 처리기입니다.


void CComView::OnDestroy()
{
	CScrollView::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	m_pTransDlg->CloseWindow();
	m_pRendererDlg->CloseWindow();
	m_pColliderDlg->CloseWindow();
	m_pAnimatorDlg->CloseWindow();

	m_pTransDlg = NULL;
	m_pRendererDlg = NULL;
	m_pColliderDlg = NULL;
	m_pAnimatorDlg = NULL;
}

LRESULT CComView::OnSelectedObject(WPARAM _wParam, LPARAM _lParam)
{
	CGameObject* pObj = (CGameObject*)_wParam;
	RECT		 rt = { 0 };
	int iHeight = 0;

	if (NULL == pObj)
		return LRESULT(false);

	// 1. Transform 컴포넌트가 있다면 활성화 한다. 
	if (NULL != pObj->Transform())
	{
		m_pTransDlg->ShowWindow(SW_SHOW);
		m_pTransDlg->SetTransformInfo(pObj);

		::GetClientRect(m_pTransDlg->m_hWnd, &rt);
		iHeight += rt.bottom - rt.top;
	}
	else
	{
		//없으면 보이지 않게 한다. 
		m_pTransDlg->ShowWindow(SW_HIDE);
	}

	// 2. Renderer 컴포넌트가 있다면 활성화 한다. 
	if (NULL != pObj->Renderer())
	{
		m_pRendererDlg->ShowWindow(SW_SHOW);
		m_pRendererDlg->SetRendererInfo(pObj);

		::GetClientRect(m_pRendererDlg->m_hWnd, &rt);
		AdjustWindowRect(&rt, WS_BORDER, false);
		m_pRendererDlg->SetWindowPos(NULL, 0, iHeight, rt.right - rt.left, rt.bottom - rt.top, 0);

		iHeight += rt.bottom - rt.top;
	}
	else
	{
		m_pRendererDlg->ShowWindow(SW_HIDE);
	}

	//3. Collider 컴포넌트가 있다면 활성화 한다.
	if (NULL != pObj->Collider())
	{
		m_pColliderDlg->ShowWindow(SW_SHOW);
		m_pColliderDlg->SetColliderInfo(pObj);

		::GetClientRect(m_pColliderDlg->m_hWnd, &rt);
		AdjustWindowRect(&rt, WS_BORDER, false);
		m_pColliderDlg->SetWindowPos(NULL, 0, iHeight, rt.right - rt.left, rt.bottom - rt.top, 0);

		iHeight += rt.bottom - rt.top;
	 }
	else
	{
		m_pColliderDlg->ShowWindow(SW_HIDE);
	}


	// 4. Animator 컴포넌트가 있다면 활성화 한다. 
	if (NULL != pObj->Animator())
	{
		m_pAnimatorDlg->ShowWindow(SW_SHOW);
		m_pAnimatorDlg->SetAnimatorInfo(pObj);

		::GetClientRect(m_pAnimatorDlg->m_hWnd, &rt);
		AdjustWindowRect(&rt, WS_BORDER, false);
		m_pAnimatorDlg->SetWindowPos(NULL, 0, iHeight, rt.right - rt.left, rt.bottom - rt.top, 0);

		iHeight += rt.bottom - rt.top;
	}
	else
	{
		m_pAnimatorDlg->ShowWindow(SW_HIDE);
	}
	return LRESULT();
}