#pragma once
#include "afxcmn.h"

#include "../Include/GameObject.h"

// CHierachyView 폼 뷰입니다.

class CHierachyView : public CFormView
{
	DECLARE_DYNCREATE(CHierachyView)
private:
	HTREEITEM	m_hDragItem;
	bool		m_bDrag;

private:
	void MoveTreeItem(HTREEITEM _hSrcItem, HTREEITEM _hDestItem, HTREEITEM _hNextItem = NULL);
	HTREEITEM CopyItem(HTREEITEM _hSrcItem, HTREEITEM _hDestItem);
	void AddGameObjectTag(const list<CGameObject*>& _ObjList, HTREEITEM _hParent);

	// itemData가 일치하는 item핸들 구하기
	HTREEITEM FindItem(DWORD dwData);
	HTREEITEM FindTreeData(HTREEITEM hItem, DWORD dwData);

public:
	void InitTreeCtrl();
	LRESULT HighlightTreeItem(WPARAM, LPARAM);

protected:
	CHierachyView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CHierachyView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HIERACHYVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_CtrlTree;
	afx_msg void OnTvnBegindragTree(NMHDR *pNMHDR, LRESULT *pResult);
	virtual void OnInitialUpdate();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTreeItemChanged(NMHDR *pNMHDR, LRESULT *pResult);
};


