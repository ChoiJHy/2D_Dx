#include "stdafx.h"
#include "CollisionMgr.h"

#include "Scene.h"
#include "SceneMgr.h"
#include "Layer.h"
#include "GameObject.h"
#include <D2D1.h>

CCollisionMgr::CCollisionMgr()
{
	memset(m_arrColCheck, 0, 8);
}


CCollisionMgr::~CCollisionMgr()
{
}

int CCollisionMgr::LateUpdate()
{
	BYTE byte = 0;
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	for (int i = 0; i < 8; ++i)
	{
		for (int j = i; j < 8; ++j)
		{
			byte = m_arrColCheck[i];
			byte >>= j;

			if (byte & 1)
			{
				CollisionLayer(pCurScene->GetLayerFromIndex(i), pCurScene->GetLayerFromIndex(j));
			}
		}
	}
	return 0;
}

// 인자로 받은 두 레이어가 충돌한다고 알림
bool CCollisionMgr::CollisionCheckLayer(wstring _strLayerLeft, wstring _strLayerRight)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	int iLeft = pCurScene->GetLayerIndex(_strLayerLeft);
	int iRight = pCurScene->GetLayerIndex(_strLayerRight);

	if (iLeft == -1 || iRight == -1)
		return false;

	if (iLeft > iRight)
	{
		int temp = iLeft;
		iLeft = iRight;
		iRight = temp;
	}

	BYTE byte = 0;

	byte >>= iRight;
	byte |= 1;
	byte <<= iRight;

	m_arrColCheck[iLeft] |= byte; 
	return true;
}

void CCollisionMgr::CollisionLayer(CLayer * _pLayerLeft, CLayer * _pLayerRight)
{
	list<CGameObject*>& pList1 = _pLayerLeft->GetObjList();
	list<CGameObject*>& pList2 = _pLayerRight->GetObjList();

	list<CGameObject*>::iterator iter1 = pList1.begin();
	list<CGameObject*>::iterator iter1End = pList1.end();
	for (; iter1 != iter1End; ++iter1)
	{
		if (NULL == (*iter1)->Collider())
			continue;

		list<CGameObject*>::iterator iter2 = pList2.begin();
		list<CGameObject*>::iterator iter2End = pList2.end();

		for (; iter2 != iter2End; ++iter2)
		{
			if (NULL == (*iter2)->Collider())
				continue;
			if ((*iter1) == (*iter2))
				continue;

			COLLIDER_ID id = MakeColID((*iter1)->Collider(), (*iter2)->Collider());
			map<DWORD, bool>::iterator iter = m_mapColState.find(id.ID);

			if (IsCollision((*iter1)->Collider(), (*iter2)->Collider()))
			{
				if (iter == m_mapColState.end())
				{
					// 최초 충돌 

					m_mapColState.insert(make_pair(id.ID, true));
					(*iter1)->Collider()->OnCollisionEnter((*iter2)->Collider());
					(*iter2)->Collider()->OnCollisionEnter((*iter1)->Collider());
				}
				else
				{
					if (iter->second)
					{
						// 계속 충돌중
						(*iter1)->Collider()->OnCollision((*iter2)->Collider());
						(*iter2)->Collider()->OnCollision((*iter1)->Collider());
					}
					else
					{
						// 이전에 충돌한 적이 있고 다시 충돌한 상황 
						iter->second = true;
						(*iter1)->Collider()->OnCollisionEnter((*iter2)->Collider());
						(*iter2)->Collider()->OnCollisionEnter((*iter1)->Collider());
					}
				}
			}
			else
			{
				if (iter != m_mapColState.end() && iter->second)
				{
					//충돌이 끝나는 시점 
					iter->second = false;
					(*iter1)->Collider()->OnCollisionExit((*iter2)->Collider());
					(*iter2)->Collider()->OnCollisionExit((*iter1)->Collider());
				}
			}
		}
	}
}

bool CCollisionMgr::IsCollision(CCollider * _pLeft, CCollider * _pRight)
{
	COLLIDER_TYPE leftType = _pLeft->GetColliderType();
	COLLIDER_TYPE rightType = _pRight->GetColliderType();

	if (leftType == COLLIDER_TYPE::COLLIDER_RECTANGLE)
	{
		switch (rightType)
		{
		case COLLIDER_TYPE::COLLIDER_CIRCLE:
			return CollisionRectToCircle(_pLeft, _pRight);
		case COLLIDER_TYPE::COLLIDER_RECTANGLE:
			return CollisionRectToRect(_pLeft, _pRight);
		case COLLIDER_TYPE::COLLIDER_POINT:
			return CollisionRectToPoint(_pLeft, _pRight);
		default:
			break;
		}
	}
	else if (leftType == COLLIDER_TYPE::COLLIDER_CIRCLE)
	{
		switch (rightType)
		{
		case COLLIDER_TYPE::COLLIDER_CIRCLE:
			return CollisionCircleToCircle(_pLeft, _pRight);
		case COLLIDER_TYPE::COLLIDER_RECTANGLE:
			return CollisionRectToCircle(_pRight, _pLeft);
		case COLLIDER_TYPE::COLLIDER_POINT:
			return CollisionRectToPoint(_pLeft, _pRight);
		default:
			break;
		}
	}
	else if (leftType == COLLIDER_TYPE::COLLIDER_POINT)
	{
		switch (rightType)
		{
		case COLLIDER_TYPE::COLLIDER_CIRCLE:
			return CollisionCircleToPoint(_pRight, _pLeft);
		case COLLIDER_TYPE::COLLIDER_RECTANGLE:
			return CollisionRectToPoint(_pRight, _pLeft);
		case COLLIDER_TYPE::COLLIDER_POINT:
			break;
		default:
			break;
		}
	}

	return false;
}

void CCollisionMgr::GetAsixProjVector(CCollider * _pCollider, Vec3 * _pArrAxis, Vec3 * _pArrProj)
{
	//좌상단의 위치를 구합니다.
	Vec3 vPos1 = Vec3(-0.5f, 0.5f, 0.f);
	D3DXVec3TransformCoord(&vPos1, &vPos1, &_pCollider->GetColliderMatrix());

	//우상단의 위치를 구합니다.
	Vec3 vPos2 = Vec3(0.5f, 0.5f, 0.f);
	D3DXVec3TransformCoord(&vPos2, &vPos2, &_pCollider->GetColliderMatrix());

	//좌하단의 위치를 구합니다.
	Vec3 vPos3 = Vec3(-0.5f, -0.5f, 0.f);
	D3DXVec3TransformCoord(&vPos3, &vPos3, &_pCollider->GetColliderMatrix());

	// 분리축 벡터와 투영시킬 벡터를 구합니다.
	_pArrProj[0] = (vPos2 - vPos1) * 0.5f;
	D3DXVec3Normalize(&_pArrAxis[0], &_pArrProj[0]);

	_pArrProj[1] = (vPos3 - vPos1) * 0.5f;
	D3DXVec3Normalize(&_pArrAxis[1], &_pArrProj[1]);
}


bool CCollisionMgr::CollisionRectToRect(CCollider * _pLeft, CCollider * _pRight)
{
	// 1. 분리축이 4개 필요합니다.
	// 2. 사각 충돌체의 투영벡터가 4개 필요합니다.

	Vec3 arrVecAxis[4] = { Vec3() };
	Vec3 arrVecProj[4] = { Vec3() };

	GetAsixProjVector(_pLeft, arrVecAxis, arrVecProj);
	GetAsixProjVector(_pRight, arrVecAxis + 2, arrVecProj + 2);

	// 두 충돌체의 중심을 잇는 벡터를 구합니다. 
	Vec3 vCenterLeft = Vec3(0.f, 0.f, 0.f);
	Vec3 vCenterRight = Vec3(0.f, 0.f, 0.f);

	D3DXVec3TransformCoord(&vCenterLeft, &vCenterLeft, &_pLeft->GetColliderMatrix());
	D3DXVec3TransformCoord(&vCenterRight, &vCenterRight, &_pRight->GetColliderMatrix());

	Vec3 vDist = vCenterRight - vCenterLeft;
	vDist.z = 0.f;

	for (int i = 0; i < 4; ++i)
	{
		float fDist = abs(D3DXVec3Dot(&arrVecAxis[i], &vDist));
		float fSum = 0.f;

		for (int j = 0; j < 4; ++j)
		{
			fSum += abs(D3DXVec3Dot(&arrVecAxis[i], &arrVecProj[j]));
		}

		if (fDist > fSum)
			return false;
	}

	return true;
}

bool CCollisionMgr::CollisionCircleToCircle(CCollider * _pLeft, CCollider * _pRight)
{
	float fLeftRadius = _pLeft->GetRadius();
	float fRightRadius = _pRight->GetRadius();

	Vec3 vCenterLeft = Vec3(0.f, 0.f, 0.f);
	Vec3 vCenterRight = Vec3(0.f, 0.f, 0.f);

	D3DXVec3TransformCoord(&vCenterLeft, &vCenterLeft, &_pLeft->GetColliderMatrix());
	D3DXVec3TransformCoord(&vCenterRight, &vCenterRight, &_pRight->GetColliderMatrix());

	float fDist = sqrt(pow(vCenterRight.x - vCenterLeft.x, 2.f) + pow(vCenterRight.y - vCenterLeft.y, 2.f));

	if (fLeftRadius + fRightRadius < fDist)
		return false;
	else
		return true;
}


bool CCollisionMgr::CollisionRectToCircle(CCollider * _pColliderRect, CCollider * _pColliderCircle)
{
	////분리축이 하나가 필요하다. (사각형의 중심과 원의 중심 사이의 방향 벡터를 축으로 한다.)
	//Vec3 vAxis;

	//Vec3 vCircleCenter = Vec3(0.f, 0.f, 0.f);
	//Vec3 vRectCenter = Vec3(0.f, 0.f, 0.f);

	//D3DXVec3TransformCoord(&vCircleCenter, &vCircleCenter, &_pColliderCircle->GetColliderMatrix());
	//D3DXVec3TransformCoord(&vRectCenter, &vRectCenter, &_pColliderRect->GetColliderMatrix());

	//vAxis = vCircleCenter - vRectCenter;

	////분리축 완성
	//D3DXVec3Normalize(&vAxis, &vAxis);

	////축에 투영시킬 사각 충돌체의 벡터를 구한다.
	////사각형의 중심과 꼭짓점중 하나를 잇는 벡터를 투영벡터로한다. 
	////원의 중심과 거리가 가까운쪽을 투영 벡터로한다. 
	//Vec3 arrVecProjRect[4] = { Vec3() };
	//arrVecProjRect[0] = Vec3(-0.5f, 0.5f, 0.f);		// 좌상단
	//arrVecProjRect[1] = Vec3(0.5f, 0.5f, 0.f);		// 우상단
	//arrVecProjRect[2] = Vec3(-0.5f, -0.5f, 0.f);	// 좌하단
	//arrVecProjRect[3] = Vec3(0.5f, -0.5f, 0.f);		// 우하단

	//for(int i = 0; i< 4; ++i)
	//	D3DXVec3TransformCoord(&arrVecProjRect[i], &arrVecProjRect[i], &_pColliderRect->GetColliderMatrix());

	//

	//return true;
	return false;
}

bool CCollisionMgr::CollisionRectToPoint(CCollider * _pColliderRect, CCollider * _pColliderPoint)
{
	Vec3 vLeftTop = Vec3(-0.5f, 0.5f, 0.f);
	Vec3 vRightBottom = Vec3(0.5f, -0.5f, 0.f);

	D3DXVec3TransformCoord(&vLeftTop, &vLeftTop, &_pColliderRect->GetColliderMatrix());
	D3DXVec3TransformCoord(&vRightBottom, &vRightBottom, &_pColliderRect->GetColliderMatrix());
	float left, top, right, bottom;
	left = vLeftTop.x;
	top = vLeftTop.y;
	right = vRightBottom.x;
	bottom = vRightBottom.y;

	Vec3 vPointPos = Vec3(0.f, 0.f, 0.f);
	D3DXVec3TransformCoord(&vPointPos, &vPointPos, &_pColliderPoint->GetColliderMatrix());

	float ptX, ptY;
	ptX = vPointPos.x;
	ptY = vPointPos.y;

	if (ptX < left)
		return false;
	else if (ptX > right)
		return false;
	if (ptY > top)
		return false;
	else if (ptY < bottom)
		return false;

	return true;
}

bool CCollisionMgr::CollisionCircleToPoint(CCollider * _pColliderCircle, CCollider * _pColliderPoint)
{
	Vec3 vPointPos = Vec3(0.f, 0.f, 0.f);
	D3DXVec3TransformCoord(&vPointPos, &vPointPos, &_pColliderPoint->GetColliderMatrix());

	Vec3 vCircleCenter = Vec3(0.f, 0.f, 0.f);
	D3DXVec3TransformCoord(&vCircleCenter, &vCircleCenter, &_pColliderCircle->GetColliderMatrix());

	float fDist = sqrt(pow(vPointPos.x - vCircleCenter.x, 2.f) + pow(vPointPos.y - vCircleCenter.y, 2.f));
	
	if (fDist > _pColliderCircle->GetRadius())
		return false;

	return true;
}

COLLIDER_ID CCollisionMgr::MakeColID(CCollider * _pLeft, CCollider * _pRight)
{
	WORD idLeft = _pLeft->GetID();
	WORD idRight = _pRight->GetID();

	COLLIDER_ID id;

	if (idLeft < idRight)
	{
		id.Low = idLeft;
		id.High = idRight;
	}
	else
	{
		id.Low = idRight;
		id.High = idLeft;
	}
	return id;
}