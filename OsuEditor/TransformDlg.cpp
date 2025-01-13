// TansformDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "OsuEditor.h"
#include "TransformDlg.h"
#include "afxdialogex.h"

#include "../Include/GameObject.h"

// CTansformDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTransformDlg, CDialogEx)

CTransformDlg::CTransformDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TRANSFORM, pParent)
	, m_fPosX(0.f), m_fPosY(0.f), m_fPosZ(0.f)
	, m_fScaleX(0.f), m_fScaleY(0.f), m_fScaleZ(0.f)
	, m_fRotX(0.f), m_fRotY(0.f), m_fRotZ(0.f)
	, m_pTarget(NULL)
{

}

CTransformDlg::~CTransformDlg()
{
}


void CTransformDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_POSX, m_fPosX);
	DDX_Text(pDX, IDC_POSY, m_fPosY);
	DDX_Text(pDX, IDC_POSZ, m_fPosZ);
	DDX_Text(pDX, IDC_SCALEX, m_fScaleX);
	DDX_Text(pDX, IDC_SCALEY, m_fScaleY);
	DDX_Text(pDX, IDC_SCALEZ, m_fScaleZ);
	DDX_Text(pDX, IDC_ROTX, m_fRotX);
	DDX_Text(pDX, IDC_ROTY, m_fRotY);
	DDX_Text(pDX, IDC_ROTZ, m_fRotZ);
}


BEGIN_MESSAGE_MAP(CTransformDlg, CDialogEx)
	//IDC_POSX 부터 IDC_ROTZ 사이에 있는 아이디에 EN_CHANGE메세지가 들어오면 함수포인터로 받은 함수를 호출한다.
	ON_CONTROL_RANGE(EN_CHANGE, IDC_POSX, IDC_ROTZ, &CTransformDlg::OnChangeValue)
END_MESSAGE_MAP()


// CTansformDlg 메시지 처리기입니다.

void CTransformDlg::SetTransformInfo(CGameObject * _pObj)
{
	// 타겟을 저장해 둡니다.
	m_pTarget = _pObj;

	CTransform* pTrans = _pObj->Transform();

	// 위치 값을 얻어온다.
	Vec3 vTemp = pTrans->GetPos();

	m_fPosX = vTemp.x;
	m_fPosY = vTemp.y;
	m_fPosZ = vTemp.z;

	// 크기 값을 얻어온다.
	vTemp = pTrans->GetScale();

	m_fScaleX = vTemp.x;
	m_fScaleY = vTemp.y;
	m_fScaleZ = vTemp.z;

	// 회전값을 얻어온다.
	vTemp = pTrans->GetRot();

	m_fRotX = vTemp.x;
	m_fRotY = vTemp.y;
	m_fRotZ = vTemp.z;

	// Transform 정보를 컨트롤로 전달
	// 컨트롤 에서 정보를 받아오려면 true를 넣는다.
	UpdateData(false);

}



void CTransformDlg::OnOK()
{
}

void CTransformDlg::OnCancel()
{
}


void CTransformDlg::OnChangeValue(UINT _id)
{
	// 현재 선택되어있는 오브젝트가 없다면 함수 종료
	if (NULL == m_pTarget)
		return;

	// 컨트롤에서 정보를 받아온다.
	UpdateData(true);

	CTransform* pTrans = m_pTarget->Transform();

	pTrans->SetPos(Vec3(m_fPosX, m_fPosY, m_fPosZ));
	pTrans->SetScale(Vec3(m_fScaleX, m_fScaleY, m_fScaleZ));
	pTrans->SetRot(Vec3(m_fRotX, m_fRotY, m_fRotZ));
}


void CTransformDlg::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	delete this;
	CDialogEx::PostNcDestroy();
}
