#pragma once

#include "define.h"

typedef struct _tagVtxCol
{
	Vec3		vPos;
	D3DCOLOR	col;

	_tagVtxCol()
	{
		vPos = Vec3(0.f, 0.f, 0.f);
		col = D3DCOLOR_ARGB(255, 255, 255, 255);
	}
}VTXCOL;

// FVF 유연한 버텍스 포멧 (정점 형태를 어떻게 구성했는지를 비트연산으로 알림)
#define VTXPOSCOL		D3DFVF_XYZ | D3DFVF_DIFFUSE

typedef struct _tagVtxTex
{
	Vec3		vPos;
	//D3DCOLOR	col;
	Vec2		vUV;

	_tagVtxTex()
	{
		vPos = Vec3(0.f, 0.f, 0.f);
		//col = D3DCOLOR_ARGB(0, 0, 0, 0);
		vUV = Vec2(0.f, 0.f);
	}
}VTXTEX;

#define VTXPOSTEX		D3DFVF_XYZ /*| D3DFVF_DIFFUSE*/ | D3DFVF_TEX1

typedef struct _tagIdx16
{
	WORD _1, _2, _3;
	_tagIdx16()
		: _1(0)
		, _2(0)
		, _3(0)
	{

	}
}INDEX16;