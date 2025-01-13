// ColliderDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "OsuEditor.h"
#include "ColliderDlg.h"
#include "afxdialogex.h"


#include "../Include/GameObject.h"

// CColliderDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CColliderDlg, CDialogEx)


CColliderDlg::CColliderDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_COLLIDER, pParent)
	, m_fColOffsetX(0)
	, m_fColOffsetY(0)
	, m_fColOffsetZ(0)
	, m_fColSizeX(0)
	, m_fColSizeY(0)
	, m_fColRotX(0)
	, m_fColRotY(0)
	, m_fColRotZ(0)
	, m_fColRadius(0)
{

}

CColliderDlg::~CColliderDlg()
{
}

void CColliderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_OFFSETX, m_fColOffsetX);
	DDX_Text(pDX, IDC_OFFSETY, m_fColOffsetY);
	DDX_Text(pDX, IDC_OFFSETZ, m_fColOffsetZ);
	DDX_Text(pDX, IDC_COLSIZEX, m_fColSizeX);
	DDX_Text(pDX, IDC_COLSIZEY, m_fColSizeY);
	DDX_Text(pDX, IDC_COLROTX, m_fColRotX);
	DDX_Text(pDX, IDC_COLROTY, m_fColRotY);
	DDX_Text(pDX, IDC_COLROTZ, m_fColRotZ);
	DDX_Text(pDX, IDC_COLRADIUS, m_fColRadius);
}


void CColliderDlg::SetColliderInfo(CGameObject * _pObj)
{
	// 타겟을 저장해 둡니다.
	m_pTarget = _pObj;

	CCollider* pCol = _pObj->Collider();

	// Offset을 가져온다.
	Vec3 vTemp = pCol->GetOffset();

	m_fColOffsetX = vTemp.x;
	m_fColOffsetY = vTemp.y;
	m_fColOffsetZ = vTemp.z;

	// 크기 값을 얻어온다.
	Vec2 vSize = pCol->GetSize();

	m_fColSizeX = vSize.x;
	m_fColSizeY = vSize.y;

	// 회전값을 얻어온다.
	vTemp = pCol->GetRot();

	m_fColRotX = vTemp.x;
	m_fColRotY = vTemp.y;
	m_fColRotZ = vTemp.z;

	float rad = pCol->GetRadius();
	m_fColRadius = rad;
	

	// Transform 정보를 컨트롤로 전달
	// 컨트롤 에서 정보를 받아오려면 true를 넣는다.
	UpdateData(false);
}


BEGIN_MESSAGE_MAP(CColliderDlg, CDialogEx)
	ON_CONTROL_RANGE(EN_CHANGE, IDC_OFFSETX, IDC_COLROTZ, &CColliderDlg::OnEnChangeColValue)
END_MESSAGE_MAP()


// CColliderDlg 메시지 처리기입니다.


void CColliderDlg::OnEnChangeColValue(UINT _id)
{
	// ColliderDlg의 값들이 변경되면 여기로 들어와서 
	// 선택된 Object의 Collider의 값들이 실제로 변경되게됩니다.

	// 현재 선택되어있는 오브젝트가 없다면 함수 종료
	if (NULL == m_pTarget)
		return;

	// 컨트롤에서 정보를 받아온다.
	UpdateData(true);

	CCollider* pCol = m_pTarget->Collider();

	pCol->SetOffset(Vec3(m_fColOffsetX, m_fColOffsetY, m_fColOffsetZ));
	pCol->SetSize(Vec2(m_fColSizeX, m_fColSizeY));
	pCol->SetRot(Vec3(m_fColRotX, m_fColRotY, m_fColRotZ));
	pCol->SetRadius(m_fColRadius);
}


void CColliderDlg::OnOK()
{
}


void CColliderDlg::OnCancel()
{
}


void CColliderDlg::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	delete this;
	CDialogEx::PostNcDestroy();
}
