#pragma once
#include "afxwin.h"

// CAnimatorDlg 대화 상자입니다.
class CGameObject;

class CAnimatorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAnimatorDlg)
private:
	CGameObject*		m_pTarget;
	wchar_t				m_szFolderPath[MAX_PATH];

public:
	void SetAnimatorInfo(CGameObject* _pObj);

public:
	CAnimatorDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAnimatorDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ANIMATOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
	virtual void OnOK();
	virtual void OnCancel();
public:
	CComboBox m_AnimationList;
	afx_msg void OnAnimationListChange();
	afx_msg void OnAddAnimation();
};
