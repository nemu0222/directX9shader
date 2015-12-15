//=============================================================================
// sky.cpp
// Author : Noriyuki Honda
//=============================================================================

//=============================================================================
// include
//=============================================================================
#include "sky.h"
#include "manager.h"
#include "renderer.h"
#include <math.h>

//=============================================================================
// macro
//=============================================================================
#define sky "data/TEXTURE/sky001.jpg"

//=============================================================================
// Init
// pManager : マネージャークラスポインタ
// blockX   : フィールドの横の総ブロック数
// blockY   : フィールドの縦の総ブロック数
// sizeX    : フィールドのブロック単位の大きさ
//=============================================================================
HRESULT Sky::Init(Manager* pManager, int blockX, int blockY, float sizeX, float sizeY)
{
	m_pD3DDevice = pManager->GetRenderer()->GetDevice();

	m_fLengthxz = 50.0f;

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	float CylinderX, CylinderZ, fLengthxz;

	m_nNumBlockX = blockX;
	m_nNumBlockY = blockY;
	m_fNumSizeX = sizeX;
	m_fNumSizeY = sizeY;

	m_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_nNumIndex = (((blockX + 1) * 2) * blockY) + 2 * blockY;
	m_nNumVertex = (blockX + 1) * (blockY + 1);
	m_nNumPolygon = m_nNumIndex - 2;


	if (FAILED(m_pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nNumVertex,		// 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法
		FVF_VERTEX_3D,				// 頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&m_pD3DVtxBuff,				// インデックスバッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	if (FAILED(m_pD3DDevice->CreateIndexBuffer(sizeof(WORD) * m_nNumIndex,				// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法
		D3DFMT_INDEX16,				// 使用するインデックスフォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&m_pD3DIndexBuff,			// インデックスバッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	D3DXCreateTextureFromFile(m_pD3DDevice,
		sky,
		&m_pD3DTexture);

	VERTEX_3D *pVtx;

	m_pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int y = 0; y < blockY + 1; y++)
	{
		for (int x = 0; x < blockX + 1; x++)
		{
			fLengthxz = cosf((D3DX_PI / 2.0f / blockY) * y) * sizeY;
			CylinderX = sinf((2.0f * D3DX_PI / blockX) * x) * fLengthxz;
			CylinderZ = cosf((2.0f * D3DX_PI / blockX) * x) * -fLengthxz;
			pVtx[x + y * (blockX + 1)].vtx = D3DXVECTOR3(CylinderX,
				sinf((D3DX_PI / 2.0f / blockY) * y) * sizeY,
				CylinderZ);
			pVtx[x + y * (blockX + 1)].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[x + y * (blockX + 1)].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[x + y * (blockX + 1)].tex = D3DXVECTOR2((float)x / blockX, (float)y / blockY);
		}
	}

	m_pD3DVtxBuff->Unlock();


	WORD *pIndex;
	int nIndexCounter = 0;

	m_pD3DIndexBuff->Lock(0, 0, (void**)&pIndex, 0);

	for (int y = 0; y < blockY; y++)
	{
		pIndex[nIndexCounter] = y * (blockX + 1);
		nIndexCounter++;
		for (int x = 0; x < blockX + 1; x++)
		{
			pIndex[nIndexCounter] = y * (blockX + 1) + x;
			nIndexCounter++;
			pIndex[nIndexCounter] = x + (y + 1) * (blockX + 1);
			nIndexCounter++;
		}

		pIndex[nIndexCounter] = blockX + ((y + 1) * (blockX + 1));
		nIndexCounter++;
	}

	m_pD3DIndexBuff->Unlock();

	return S_OK;
}

//=============================================================================
// Uninit
//=============================================================================
void Sky::Uninit(void)
{
	SAFE_DELETE_OBJ(m_pD3DIndexBuff);
	SAFE_DELETE_OBJ(m_pD3DTexture);
	SAFE_DELETE_OBJ(m_pD3DVtxBuff);
}

//=============================================================================
// Update
//=============================================================================
void Sky::Update(void)
{
}

//=============================================================================
// Draw
//=============================================================================
void Sky::Draw(void)
{
	D3DXMATRIX mtxScl;
	D3DXMATRIX mtxRot;
	D3DXMATRIX mtxTranslate;

	D3DXMatrixIdentity(&m_mtxWorld);

	D3DXMatrixTranslation(&mtxTranslate, m_offset.x, m_offset.y, m_offset.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTranslate);
	D3DXMatrixScaling(&mtxScl, m_scl.x, m_scl.y, m_scl.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScl);
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	D3DXMatrixTranslation(&mtxTranslate, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTranslate);

	m_pD3DDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	m_pD3DDevice->SetStreamSource(0, m_pD3DVtxBuff, 0, sizeof(VERTEX_3D));
	m_pD3DDevice->SetIndices(m_pD3DIndexBuff);
	m_pD3DDevice->SetFVF(FVF_VERTEX_3D);
	m_pD3DDevice->SetTexture(0, m_pD3DTexture);
	m_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nNumVertex, 0, m_nNumPolygon);
}

// EOF