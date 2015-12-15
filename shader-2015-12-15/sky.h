//=============================================================================
// sky.h
// Author : Noriyuki Honda
//=============================================================================
#ifndef _SKY_H_
#define _SKY_H_

//=============================================================================
// include
//=============================================================================
#include "main.h"

class Manager;

//=============================================================================
// class
//=============================================================================
class Sky
{
public:
	Sky(void)
	{
		m_pD3DDevice = NULL;
		m_pD3DTexture = NULL;
		m_pD3DVtxBuff = NULL;
		m_pD3DIndexBuff = NULL;

		D3DXMatrixIdentity(&m_mtxWorld);

		m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

		m_nNumVertex = 0;
		m_nNumIndex = 0;
		m_nNumPolygon = 0;
		m_nNumBlockX = 0;
		m_nNumBlockY = 0;

		m_fNumSizeX = 0.0f;
		m_fNumSizeY = 0.0f;

		m_fLengthxz = 0.0f;
	}
	virtual ~Sky(void){}

	HRESULT Init(Manager* pManager,int blockX,int blockY,float sizeX,float sizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(D3DXVECTOR3 pos){ m_pos = pos; }
private:
	LPDIRECT3DDEVICE9 m_pD3DDevice;

	LPDIRECT3DVERTEXBUFFER9 m_pD3DVtxBuff;
	LPDIRECT3DINDEXBUFFER9 m_pD3DIndexBuff;
	LPDIRECT3DTEXTURE9 m_pD3DTexture;

	D3DXMATRIX m_mtxWorld;

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_scl;

	D3DXVECTOR3 m_offset;

	int m_nNumVertex;
	int m_nNumIndex;
	int m_nNumPolygon;
	int m_nNumBlockX;
	int m_nNumBlockY;
	float m_fNumSizeX;
	float m_fNumSizeY;

	float m_fLengthxz;
};

#endif // _SKY_H_

// EOF