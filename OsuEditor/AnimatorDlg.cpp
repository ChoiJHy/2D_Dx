// AnimatorDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "OsuEditor.h"
#include "AnimatorDlg.h"
#include "afxdialogex.h"
#include <ShlObj.h>

#include "../Include/GameObject.h"
#include "../Include/Animation.h"
#include "../Include/Texture.h"
#include "../Include/PathMgr.h"

// CAnimatorDlg 대화 상자입니다.


INT CALLBACK BrowseCallbackProc(HWND hWnd, UINT uMsg, LPARAM lp, LPARAM pData)
{
	TCHAR szDir[MAX_PATH];

	switch (uMsg)
	{
	case BFFM_INITIALIZED:
	{
		const wchar_t* pPath = CPathMgr::GetResourcesPath();
		SendMessage(hWnd, BFFM_SETSELECTION, TRUE, (LPARAM)pPath);
		break;
	}
	case BFFM_SELCHANGED:
		if (SHGetPathFromIDList((LPITEMIDLIST)lp, szDir))
		{
			SendMessage(hWnd, BFFM_SETSTATUSTEXT, 0, (LPARAM)szDir);
		}
		break;
	}
	return 0;
}

IMPLEMENT_DYNAMIC(CAnimatorDlg, CDialogEx)


CAnimatorDlg::CAnimatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ANIMATOR, pParent)
{

}

CAnimatorDlg::~CAnimatorDlg()
{
}

void CAnimatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ANIMATIONLIST, m_AnimationList);
}


void CAnimatorDlg::SetAnimatorInfo(CGameObject * _pObj)
{
	m_pTarget = _pObj;

	CAnimator* pAnimator = m_pTarget->Animator();

	// 가져온 Animator에서 모든 Animation 이름을 가져옵니다.
	vector<wstring> vecAnimation;
	pAnimator->GetAnimationList(vecAnimation);

	// 현재 재생중인 Animation을 알아냅니다.
	CAnimation* pCurAni = pAnimator->GetCurAnimation();
	wstring strCurAni;
	if (NULL != pCurAni)
		strCurAni = pCurAni->GetKey();

	// 콤보박스를 초기화합니다.
	m_AnimationList.ResetContent();
	// 콤보박스의 인덱스번호에 -1이 들어가면 아무것도 나오지 않는다.
	int idx = -1;

	for (int i = 0; i < vecAnimation.size(); ++i)
	{
		if (vecAnimation[i] == strCurAni)
			idx = i;
		m_AnimationList.AddString(vecAnimation[i].c_str());
	}

	m_AnimationList.SetCurSel(idx);
}


BEGIN_MESSAGE_MAP(CAnimatorDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_ANIMATIONLIST, &CAnimatorDlg::OnAnimationListChange)
	ON_BN_CLICKED(IDC_ADDANIMATION, &CAnimatorDlg::OnAddAnimation)
END_MESSAGE_MAP()


// CAnimatorDlg 메시지 처리기입니다.
void CAnimatorDlg::OnAnimationListChange()
{
	int idx = m_AnimationList.GetCurSel();
	CString str;
	m_AnimationList.GetLBText(idx, str);

	m_pTarget->Animator()->PlayAnimation(str.GetBuffer());
}

void CAnimatorDlg::OnAddAnimation()
{
	LPITEMIDLIST pidlBrowse;
	BROWSEINFO   BrInfo;

	BrInfo.hwndOwner = GetSafeHwnd();
	BrInfo.pidlRoot = 0; // NULL 이면 최초 위치는 바탕화면 입니다.

	memset(&BrInfo, 0, sizeof(BrInfo));
	BrInfo.pszDisplayName = m_szFolderPath;
	BrInfo.lpszTitle = _T("Animation 폴더 지정");
	BrInfo.ulFlags = BIF_USENEWUI;

	BrInfo.lpfn = BrowseCallbackProc;

	pidlBrowse = ::SHBrowseForFolder(&BrInfo);

	if (pidlBrowse != NULL)
	{
		SHGetPathFromIDList(pidlBrowse, m_szFolderPath);
	}

	// 잘못된 폴더를 선택한 경우 리턴합니다.
	m_szFolderPath;
	CString strPath = m_szFolderPath;
	int idx = strPath.Find(L"\\Animation");
	if (-1 == idx)
		return;

	// 마지막 폴더명만 추출하기 .
	CString str = m_szFolderPath;
	CString name = str.Right(str.GetLength() - str.ReverseFind('\\') - 1);

	m_pTarget->Animator()->LoadAnimation(m_szFolderPath, name.GetBuffer());
	m_AnimationList.AddString(name);
}

void CAnimatorDlg::PostNcDestroy()
{
	delete this;
	CDialogEx::PostNcDestroy();
}


void CAnimatorDlg::OnOK()
{
}


void CAnimatorDlg::OnCancel()
{
}




