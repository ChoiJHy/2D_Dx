#include "stdafx.h"
#include "Mesh.h"

#include "Device.h"


CMesh::CMesh()
	: m_pVB(NULL), m_pVtxTex(NULL), m_iVtxCnt(0)
	, m_pIB(NULL), m_pIndex(NULL), m_iIdxCnt(0)
{
}


CMesh::~CMesh()
{
	if (NULL != m_pVB)
		m_pVB->Release();

	if (NULL != m_pIB)
		m_pIB->Release();

	SAFE_DELETE_ARR(m_pVtxTex);
	SAFE_DELETE_ARR(m_pIndex);
}

void CMesh::Init(int _iVtxCnt, int _iIdxCnt)
{
	//정점버퍼 생성
	DEVICE->CreateVertexBuffer(sizeof(VTXTEX) * _iVtxCnt, 0
		, VTXPOSTEX, D3DPOOL_DEFAULT, &m_pVB, NULL);

	DEVICE->CreateIndexBuffer(sizeof(INDEX16) * _iIdxCnt, 0
		, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIB, 0);

	m_iVtxCnt = _iVtxCnt;
	m_iIdxCnt = _iIdxCnt;
}

void CMesh::Render()
{
	DEVICE->SetStreamSource(0, m_pVB, 0, sizeof(VTXTEX));
	DEVICE->SetFVF(VTXPOSTEX);
	DEVICE->SetIndices(m_pIB);
	DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_iVtxCnt, 0, m_iIdxCnt);
}

void CMesh::SetVtxInfo(VTXTEX* _pVtxArr, int _iSize)
{
	if (_iSize > m_iVtxCnt)
	{
		m_pVB->Release();
		DEVICE->CreateVertexBuffer(sizeof(VTXTEX) * _iSize, 0
			, VTXPOSTEX, D3DPOOL_DEFAULT, &m_pVB, NULL);
		m_iVtxCnt = _iSize;
	}

	void* pVoid = NULL;

	if (NULL != m_pVB)
	{
		m_pVB->Lock(0, 0, &pVoid, 0);

		memcpy(pVoid, _pVtxArr, sizeof(VTXTEX) * _iSize);

		m_pVB->Unlock();
	}

	if (NULL != m_pVtxTex)
		delete[] m_pVtxTex;

	m_pVtxTex = new VTXTEX[_iSize];
	memcpy(m_pVtxTex, _pVtxArr, sizeof(VTXTEX) * _iSize);
}

void CMesh::SetIdxInfo(INDEX16 * _pIdxArr, int _iSize)
{
	if (_iSize > m_iIdxCnt)
	{
		m_pIB->Release();
		DEVICE->CreateIndexBuffer(sizeof(INDEX16) * _iSize, 0
			, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIB, NULL);
		m_iIdxCnt = _iSize;
	}

	void* pVoid = NULL;

	if (NULL != m_pIB)
	{
		m_pIB->Lock(0, 0, &pVoid, 0);

		memcpy(pVoid, _pIdxArr, sizeof(INDEX16) * _iSize);

		m_pIB->Unlock();
	}

	if (NULL != m_pIndex)
		delete[] m_pIndex;

	m_pIndex = new INDEX16[_iSize];
	memcpy(m_pIndex, _pIdxArr, sizeof(INDEX16) * _iSize);
}
