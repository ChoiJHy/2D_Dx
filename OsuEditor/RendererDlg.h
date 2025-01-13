#pragma once


// CRendererDlg 대화 상자입니다.
class CGameObject;

class CRendererDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRendererDlg)

private:
	CGameObject* m_pTarget;

public:
	void SetRendererInfo(CGameObject* _pObj);

public:
	CRendererDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRendererDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RENDERER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strMeshKey;
	CString m_strTexKey;
	virtual void PostNcDestroy();
	BOOL m_bEnable;
	afx_msg void OnBnClickedCheck();
	virtual void OnOK();
	virtual void OnCancel();
};
