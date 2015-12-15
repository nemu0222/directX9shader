//=============================================================================
// model.h
// Author : Noriyuki Honda
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

//=============================================================================
// include
//=============================================================================
#include "main.h"

class Input;

//=============================================================================
// class
//=============================================================================
class Model
{
public:
	Model(void)
	{
		m_pD3DDevice = NULL;
		m_pD3DTexture = NULL;
		m_pD3DXMesh = NULL;
		m_pD3DXBuffMat = NULL;
		m_pD3DXAdjacencyBuffer = NULL;
		m_pDecl = NULL;
		m_dwNumMat = 0;

		D3DXMatrixIdentity(&m_mtxWorld);

		m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	}
	virtual ~Model(void){}

	HRESULT Init(Manager* pManager);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetWorldMtx(void);

	D3DXMATERIAL* GetMaterial(void);
private:
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	LPDIRECT3DTEXTURE9	m_pD3DTexture;
	LPD3DXMESH m_pD3DXMesh;
	LPD3DXBUFFER m_pD3DXBuffMat;
	// 隣接バッファポインタ
	LPD3DXBUFFER m_pD3DXAdjacencyBuffer;
	// マテリアル情報の数
	DWORD m_dwNumMat;
	// マテリアルポインタ
	D3DXMATERIAL* m_pMat;

	D3DXMATRIX m_mtxWorld;

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_scl;

	// デクラレーションポインタ
	LPDIRECT3DVERTEXDECLARATION9 m_pDecl;

	Input* m_pInput;
};

#endif // _MODEL_H_
// EOF