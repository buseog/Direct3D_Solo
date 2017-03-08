#ifndef Engine_struct_h__
#define Engine_struct_h__

BEGIN(Engine)

typedef struct tagVertex_Texture
{
	D3DXVECTOR3		vPos;
	D3DXVECTOR2		vTexUV;
}VTXTEX;

const unsigned long D3DFVF_VTXTEX = D3DFVF_XYZ | D3DFVF_TEX1;

typedef struct tagVertex_Cube_Color
{
	D3DXVECTOR3		vPos;
	DWORD			vColor;
}VTXCOL;

const unsigned long D3DFVF_VTXCOL = D3DFVF_XYZ | D3DFVF_DIFFUSE;

typedef struct tagVertex_Normal_Texture
{
	D3DXVECTOR3		vPos;
	D3DXVECTOR3		vNormal;
	D3DXVECTOR2		vTexUV;
}VTXNORMALTEX;

const unsigned long D3DFVF_VTXNORMALTEX = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

typedef struct tagVertex_Cube_Texture
{
	D3DXVECTOR3		vPos;
	D3DXVECTOR3		vTexUV;
}VTXCUBETEX;

const unsigned long D3DFVF_VTXCUBETEX = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0);

typedef struct tagIndex16
{
	unsigned short _0;
	unsigned short _1;
	unsigned short _2;
}INDEX16;

typedef struct tagIndex32
{
	unsigned long _0;
	unsigned long _1;
	unsigned long _2;
}INDEX32;

typedef struct tagD3DXFrameDerived : public D3DXFRAME
{
	D3DXMATRIX		CombineTransformationMatrix;

}D3DXFRAME_DERIVED;

typedef struct tagD3DXMeshContainerDerived : public D3DXMESHCONTAINER
{
	LPDIRECT3DTEXTURE9*		pTextures;
	LPD3DXMESH				pOriMesh;

	DWORD					dwBoneCnt;

	D3DXMATRIX**			ppCombineTransformationMatrices;
	D3DXMATRIX*				pOffsetMatrices;
	D3DXMATRIX*				pRenderingMatrices;

}D3DXMESHCONTAINER_DERIVED;

END
#endif // Engine_struct_h__
