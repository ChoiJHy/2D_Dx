// HierachyView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "OsuEditor.h"
#include "HierachyView.h"
#include "MainFrm.h"

#include "../Include/GameObject.h"
#include "../Include/SceneMgr.h"
#include "../Include/Scene.h"

#include "MyMessage.h"


// CHierachyView

IMPLEMENT_DYNCREATE(CHierachyView, CFormView)


CHierachyView::CHierachyView()
	: CFormView(IDD_HIERACHYVIEW), m_bDrag(false), m_hDragItem(NULL)
{

}

CHierachyView::~CHierachyView()
{
}


void CHierachyView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_CtrlTree);
}

BEGIN_MESSAGE_MAP(CHierachyView, CFormView)
	ON_NOTIFY(TVN_BEGINDRAG, IDC_TREE1, &CHierachyView::OnTvnBegindragTree)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CHierachyView::OnTreeItemChanged)
	ON_MESSAGE(MM_HIGHLIGHT, &CHierachyView::HighlightTreeItem)
END_MESSAGE_MAP()


// CHierachyView 진단입니다.

#ifdef _DEBUG
void CHierachyView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CHierachyView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CHierachyView 메시지 처리기입니다.

// Hierachy View Tree Control 초기화
void CHierachyView::InitTreeCtrl()
{
	// 현재 CurScene에 있는 모든 오브젝트를 트리 컨트롤에 추가한다. 
	list<CGameObject*> ObjList;
	CScene* pScene = CSceneMgr::GetInst()->GetCurScene();
	pScene->GetParentGameObjectList(ObjList);

	AddGameObjectTag(ObjList, TVI_ROOT);
}



void CHierachyView::MoveTreeItem(HTREEITEM _hSrcItem, HTREEITEM _hDestItem, HTREEITEM _hNextItem)
{
	HTREEITEM hItem = NULL;
	do
	{
		// _hDestItem이  _hSrcItem의 자식중 하나였다면
		// 중지하는 코드를 넣는다. 
		hItem = CopyItem(_hSrcItem, _hDestItem);

		//현재 아이템에 자식 아이템이 있다면 
		HTREEITEM hChildItem = m_CtrlTree.GetChildItem(_hSrcItem);
		if (hChildItem)
		{
			// 다음 아이템이 있는지 알아 둔다.
			HTREEITEM _hChildNextItem = m_CtrlTree.GetNextItem(hChildItem, TVGN_NEXT);

			//자식 아이템이 있다면 재귀로 호출하여 같이 이동할수 있도록 한다.
			MoveTreeItem(hChildItem, hItem, _hChildNextItem);
		}

		TVITEM item;
		item.mask = TVIF_HANDLE;
		item.hItem = _hSrcItem;
		m_CtrlTree.GetItem(&item);
		if (item.state & TVIS_EXPANDED)
		{
			m_CtrlTree.Expand(hItem, TVE_EXPAND);
		}

		if (_hNextItem)
		{
			_hSrcItem = _hNextItem;
			_hNextItem = m_CtrlTree.GetNextItem(_hSrcItem, TVGN_NEXT);
		}
		else
			break;
	} while (true);

	//아이템을 선택한다.
	m_CtrlTree.SelectItem(hItem);

	// 기존 아이템을 제거한다.
	m_CtrlTree.DeleteItem(_hSrcItem);
}

HTREEITEM CHierachyView::CopyItem(HTREEITEM _hSrcItem, HTREEITEM _hDestItem)
{
	// 이동할 아이템의 정보를 알아냅니다.
	TVITEM		TV;
	wchar_t		str[256];
	ZeroMemory(str, sizeof(str));
	TV.hItem = _hSrcItem;
	TV.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	TV.pszText = str;
	TV.cchTextMax = sizeof(str);
	m_CtrlTree.GetItem(&TV);

	DWORD dwData = m_CtrlTree.GetItemData(_hSrcItem);

	//아이템을 추가합니다.
	TVINSERTSTRUCT		TI;
	TI.hParent = _hDestItem;
	TI.hInsertAfter = TVI_LAST;
	TI.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	TI.item.iImage = TV.iImage;
	TI.item.iSelectedImage = TV.iSelectedImage;
	TI.item.pszText = TV.pszText;
	HTREEITEM hItem = m_CtrlTree.InsertItem(&TI);
	m_CtrlTree.SetItemData(hItem, dwData);

	return hItem;
}

void CHierachyView::AddGameObjectTag(const list<CGameObject*>& _ObjList, HTREEITEM _hParent)
{
	list<CGameObject*>::const_iterator iterEnd = _ObjList.end();
	for (list<CGameObject*>::const_iterator iter = _ObjList.begin();
		iter != iterEnd; ++iter)
	{
		HTREEITEM hItem = m_CtrlTree.InsertItem((*iter)->GetTag().c_str(), _hParent, TVI_LAST);
		m_CtrlTree.SetItemData(hItem, (DWORD_PTR)(*iter));

		const list<CGameObject*>& ChildList = (*iter)->GetChildList();
		if (ChildList.size() != 0)
		{
			AddGameObjectTag(ChildList, hItem);
		}
	}
}

HTREEITEM CHierachyView::FindItem(DWORD dwData)
{
	HTREEITEM hRoot = m_CtrlTree.GetRootItem();
	HTREEITEM hFindItem = NULL;

	while (hRoot)
	{
		hFindItem = FindTreeData(hRoot, dwData);

		if (NULL != hFindItem)
			break;
		else
			hRoot = m_CtrlTree.GetNextSiblingItem(hRoot);
	}

	return hFindItem;
}

HTREEITEM CHierachyView::FindTreeData(HTREEITEM hItem, DWORD dwData)
{
	HTREEITEM hItemFind, hItemChild, hItemSibling;
	hItemFind = hItemChild = hItemSibling = NULL;

	if (m_CtrlTree.GetItemData(hItem) == dwData)
	{
		hItemFind = hItem;
	}
	else
	{
		// 자식노드를 찾는다.
		hItemChild = m_CtrlTree.GetChildItem(hItem);

		if (hItemChild)
			hItemFind = FindTreeData(hItemChild, dwData);

		// 형제노드를 찾는다.
		hItemSibling = m_CtrlTree.GetNextSiblingItem(hItem);

		if (hItemFind == NULL && hItemSibling)
		{
			hItemFind = FindTreeData(hItemSibling, dwData);
		}
	}

	return hItemFind;
}




void CHierachyView::OnTvnBegindragTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 마우스 메시지를 잡아두고
	SetCapture();

	m_hDragItem = pNMTreeView->itemNew.hItem;
	m_bDrag = true;


	*pResult = 0;
}


void CHierachyView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	static bool bInit = false;

	if (!bInit)
	{
		bInit = true;

		//트리컨트롤에 아이템 추가하기  1
		TVINSERTSTRUCT TI;
		TI.hParent = TVI_ROOT;			// TVI_ROOT, NULL
										// HTREEITEM값을 사용하면 해당하는 아이템의 자식으로 아이템이 추가된다.
		TI.hInsertAfter = TVI_LAST;
		TI.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
		TI.item.iImage = 0;
		TI.item.iSelectedImage = 1;
		TI.item.pszText = L"Root_1";

		// 추가된 아이템의 HTREEITEM이 리턴된다.
		HTREEITEM hTreeItem = m_CtrlTree.InsertItem(&TI);

		// 트리 컨트롤에 아이템 추가하기2
		m_CtrlTree.InsertItem(L"Child_1", hTreeItem, TVI_LAST);
		m_CtrlTree.InsertItem(L"Root_2", TVI_ROOT, TVI_LAST);
	}
}




void CHierachyView::OnMouseMove(UINT nFlags, CPoint point)
{
	// 드래그 중이라면
	if (m_bDrag)
	{
		// 트리컨트롤 기준으로 마우스 좌표 계산
		CPoint p = point;
		ClientToScreen(&p);
		::ScreenToClient(m_CtrlTree.m_hWnd, &p);
		
		// 마우스가 위치한 아이템을 검사한다. 항목이 트리 뷰 항목위에
		// 있는지 확인하고 그렇다면 항목이 밝게 표시되도록한다.
		HTREEITEM hItem = m_CtrlTree.HitTest(p);

		//밝게 표시된 부분과 현재 선택된 아이템이 틀리다면 
		if (hItem != m_CtrlTree.GetDropHilightItem())
		{
			// 새로운 항목을 밝게 표시한다.
			m_CtrlTree.SelectDropTarget(hItem);
		}
	}

	CFormView::OnMouseMove(nFlags, point);
}




void CHierachyView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	// 드래그 중이었다면 

	if (m_bDrag)
	{
		m_bDrag = false;
		// 떼는 순간 마우스 메시시 캡쳐 기능을 제거한다. 
		ReleaseCapture();

		// 마지막으로 밝게 표시됐던 항목을 찾는다.
		HTREEITEM hTargetItem = m_CtrlTree.GetDropHilightItem();

		// 밝게 표시된 드롭 항목의 선택을 취소한다.
		m_CtrlTree.SelectDropTarget(NULL);

		// 선택된 항목이 있다면 
		if (hTargetItem)
		{
			// 선택된 아이템과 이동될 곳의 아이템이 같다면 이동할 필요가 없다.
			if (m_hDragItem != hTargetItem)
			{
				// 현재 자식의 부모 아이템 핸들을 구한다. 
				HTREEITEM hParentItem = m_CtrlTree.GetNextItem(m_hDragItem, TVGN_PARENT);

				// 이동하려는 곳이 자신이 직접속한 항목이라면 이동할 필요가 없다.
				if (hParentItem != hTargetItem)
				{
					//트리의 내용을 이동한다.
					MoveTreeItem(m_hDragItem, hTargetItem);

					//이동된 곳의 트리를 확장.
					m_CtrlTree.Expand(hTargetItem, TVE_EXPAND);
				}
			}
		}

		m_hDragItem = NULL;

	}
	CFormView::OnLButtonUp(nFlags, point);
}



void CHierachyView::OnTreeItemChanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	HTREEITEM hTreeItem = pNMTreeView->itemNew.hItem;

	CString str = m_CtrlTree.GetItemText(hTreeItem);

	CGameObject* pObj = (CGameObject*)m_CtrlTree.GetItemData(hTreeItem);

	if (NULL == pObj)
		return;

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	HWND hWnd = pFrame->GetComView()->m_hWnd;
	::SendMessage(hWnd, MM_SELOBJ, (WPARAM)pObj, 0);

	*pResult = 0;
}


LRESULT CHierachyView::HighlightTreeItem(WPARAM _pObj, LPARAM _lparam)
{
	if (NULL == _pObj)
		return LRESULT(false);

	HTREEITEM hFind = FindItem(_pObj);

	m_CtrlTree.Select(hFind, TVGN_CARET | TVGN_FIRSTVISIBLE | TVGN_DROPHILITE);
	m_CtrlTree.SelectItem(hFind);
	m_CtrlTree.SetFocus();

	return LRESULT();
}
