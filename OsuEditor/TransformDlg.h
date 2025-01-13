#pragma once


// CTansformDlg 대화 상자입니다.
class CGameObject;
class CTransformDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTransformDlg)

public:
	CTransformDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTransformDlg();

private:
	// 현재 선택되어있는 GameObject
	CGameObject*	m_pTarget;

public:
	void SetTransformInfo(CGameObject* _pObj);

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TRANSFORM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	virtual void OnCancel();
public:
	float m_fPosX;
	float m_fPosY;
	float m_fPosZ;
	float m_fScaleX;
	float m_fScaleY;
	float m_fScaleZ;
	float m_fRotX;
	float m_fRotY;
	float m_fRotZ;
	afx_msg void OnChangeValue(UINT _id);
	virtual void PostNcDestroy();
};
