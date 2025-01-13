#pragma once
#include "value.h"

class CLayer;
class CCollider;

union COLLIDER_ID
{
	struct
	{
		WORD Low;
		WORD High;
	};

	DWORD ID;
};

class CCollisionMgr
{
private:
	BYTE					m_arrColCheck[8];
	map<DWORD, bool>		m_mapColState;

public:
	int LateUpdate();

public:
	bool CollisionCheckLayer(wstring _strLayerLeft, wstring _strLayerRight);

private:
	void CollisionLayer(CLayer* _pLayerLeft, CLayer* _pLayerRight);
	bool IsCollision(CCollider* _pLeft, CCollider* _pRight);

	//사각충돌에서 사용할 축과 투영될 벡터를 계산해주는 함수
	void GetAsixProjVector(CCollider* _pCollider, Vec3* _pArrAxis, Vec3* _pArrProj);

	COLLIDER_ID MakeColID(CCollider* _pLeft, CCollider* _pRight);




	bool CollisionRectToRect(CCollider* _pLeft, CCollider* _pRight);
	bool CollisionCircleToCircle(CCollider* _pLeft, CCollider* _pRight);
	bool CollisionRectToCircle(CCollider* _pColliderRect, CCollider* _pColliderCircle);
	bool CollisionRectToPoint(CCollider* _pColliderRect, CCollider* _pColliderPoint);
	bool CollisionCircleToPoint(CCollider* _pColliderCircle, CCollider* _pColliderPoint);

public:
	static CCollisionMgr* GetInst()
	{
		static CCollisionMgr mgr;
		return &mgr;
	}
private:
	CCollisionMgr();
	~CCollisionMgr();
};

