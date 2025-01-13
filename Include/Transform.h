#pragma once
#include "Component.h"

class CTransform :
	public CComponent
{
private:
	Vec3	m_vPos;
	Vec3	m_vScale;
	Vec3	m_vRot;		// 자전을 위한 벡터
	Vec3	m_vRevol;	// 공전을 위한 벡터

	Matrix	m_matWorld;

public:
	virtual void Awake();
	virtual int Update();
	virtual int LateUpdate();
	virtual CComponent* Clone()
	{
		return new CTransform(*this);
	}


///////////////////    G E T      //////////////////////////
public:
	const Matrix& GetWorldMat()
	{
		return m_matWorld;
	}

	const Vec3& GetPos()
	{
		return m_vPos;
	}

	const Vec3& GetScale()
	{
		return m_vScale;
	}

	const Vec3& GetRot()
	{
		return m_vRot;
	}

	const Vec3& GetRevol()
	{
		return m_vRevol;
	}

//////////////////////////// S E T  /////////////////////////////
public:
	void SetPos(const Vec3& _vPos)
	{
		m_vPos = _vPos;
	}

	void SetScale(const Vec3& _vScale);

	void SetRot(const Vec3& _vRot)
	{
		m_vRot = _vRot;
	}

	void SetRevol(const Vec3& _vRevol)
	{
		m_vRevol = _vRevol;
	}

	void SetPosWorld(Vec3 _vPos);

public:
	//모든 부모의 스케일 값을 합친것을 가져온다.
	void GetParentsScale(Vec3* _vOut);

private:
	// 자전 , 공전 행렬의 값을 계산해서 넣어줄 함수
	void GetSpinMatrix(Matrix* _pOutMat, Vec3 _vSpin);
public:
	CTransform();
	virtual ~CTransform();
};

