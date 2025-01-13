#pragma once
#include "Res.h"
class CMesh :
	public CRes
{
private:
	LPDIRECT3DVERTEXBUFFER9			m_pVB;
	VTXTEX*							m_pVtxTex;
	int								m_iVtxCnt;

	LPDIRECT3DINDEXBUFFER9			m_pIB;
	INDEX16*						m_pIndex;
	int								m_iIdxCnt;


public:
	void Init(int _iVtxCnt, int _iIdxCnt);
	void Render();
	void SetVtxInfo(VTXTEX* _pVtxArr, int _iSize);
	void SetIdxInfo(INDEX16* _pIdxArr, int _iSize);

public:
	CMesh();
	virtual ~CMesh();
};

