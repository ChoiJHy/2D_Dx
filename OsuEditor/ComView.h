#pragma once

class CTransformDlg;
class CRendererDlg;
class CColliderDlg;
class CAnimatorDlg;
// CComView 뷰입니다.

class CComView : public CScrollView
{
	DECLARE_DYNCREATE(CComView)

protected:
	CComView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CComView();

private:
	CTransformDlg*	m_pTransDlg;
	CRendererDlg*	m_pRendererDlg;
	CColliderDlg*	m_pColliderDlg;
	CAnimatorDlg*	m_pAnimatorDlg;

private:
	LRESULT OnSelectedObject(WPARAM _wParam, LPARAM _lParam);

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void OnDraw(CDC* pDC);      // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual void OnInitialUpdate();     // 생성된 후 처음입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
};


