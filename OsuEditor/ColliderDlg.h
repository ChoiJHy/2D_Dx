#pragma once


// CColliderDlg 대화 상자입니다.
class CGameObject;
class CColliderDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CColliderDlg)
private:
	CGameObject* m_pTarget;

public:
	void SetColliderInfo(CGameObject* _pObj);

public:
	CColliderDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CColliderDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COLLIDER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	float m_fColOffsetX;
	float m_fColOffsetY;
	float m_fColOffsetZ;
	float m_fColSizeX;
	float m_fColSizeY;
	float m_fColRotX;
	float m_fColRotY;
	float m_fColRotZ;
	afx_msg void OnEnChangeColValue(UINT _id);
	virtual void OnOK();
	virtual void OnCancel();
	virtual void PostNcDestroy();
	float m_fColRadius;
};
