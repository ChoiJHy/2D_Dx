// RendererDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "OsuEditor.h"
#include "RendererDlg.h"
#include "afxdialogex.h"

#include "../Include/GameObject.h"
#include "../Include/Texture.h"
#include "../Include/Mesh.h"
// CRendererDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRendererDlg, CDialogEx)


CRendererDlg::CRendererDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_RENDERER, pParent)
	, m_strMeshKey(_T(""))
	, m_strTexKey(_T(""))
	, m_bEnable(TRUE)
	, m_pTarget(NULL)
{

}

CRendererDlg::~CRendererDlg()
{
}

void CRendererDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strMeshKey);
	DDX_Text(pDX, IDC_EDIT2, m_strTexKey);
	DDX_Check(pDX, IDC_CHECK1, m_bEnable);
}

void CRendererDlg::SetRendererInfo(CGameObject * _pObj)
{
	m_pTarget = _pObj;
	CRenderer* pRenderer = _pObj->Renderer();

	CTexture* pTex = pRenderer->GetTex();
	if (NULL != pTex)
	{
		m_strTexKey = pTex->GetKey();
	}

	CMesh* pMesh = pRenderer->GetMesh();
	if (NULL != pMesh)
	{
		m_strMeshKey = pMesh->GetKey();
	}


	//컨트롤로 정보를 전달하기 위해서는 값을 false로 넣어준다. 
	UpdateData(false);
}


BEGIN_MESSAGE_MAP(CRendererDlg, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK1, &CRendererDlg::OnBnClickedCheck)
END_MESSAGE_MAP()


// CRendererDlg 메시지 처리기입니다.


void CRendererDlg::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	delete this;
	CDialogEx::PostNcDestroy();
}


void CRendererDlg::OnBnClickedCheck()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(true);

	if (NULL != m_pTarget)
	{
		m_pTarget->Renderer()->SetEnable(m_bEnable);
	}
		
}


void CRendererDlg::OnOK()
{
}



void CRendererDlg::OnCancel()
{
}
