//=============================================================================
// model.cpp
// Author : Noriyuki Honda
//=============================================================================

//=============================================================================
// include
//=============================================================================
#include "model.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

//=============================================================================
// macro
//=============================================================================
#define model "data/model.x"

//=============================================================================
// Init
// pManager : マネージャークラスポインタ
//=============================================================================
HRESULT Model::Init(Manager* pManager)
{
	m_pD3DDevice = pManager->GetRenderer()->GetDevice();
	m_pInput = pManager->GetInput();

	if (FAILED(D3DXLoadMeshFromX(model,
		D3DXMESH_MANAGED,
		m_pD3DDevice,
		&m_pD3DXAdjacencyBuffer,
		&m_pD3DXBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pD3DXMesh)))
	{
		return E_FAIL;
	}

	m_pD3DXMesh->OptimizeInplace(D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_VERTEXCACHE,
		(DWORD *)m_pD3DXAdjacencyBuffer->GetBufferPointer(),
		NULL,	// 最適化された隣接情報
		NULL,	// インデックス(面)
		NULL);	// インデックス(頂点)

	SAFE_DELETE_OBJ(m_pD3DXAdjacencyBuffer);

	// 頂点要素配列作成
	D3DVERTEXELEMENT9 vElementsModel[] =
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
		{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		D3DDECL_END(),
	};

	m_pD3DDevice->CreateVertexDeclaration(&vElementsModel[0], &m_pDecl);

	LPD3DXMESH pOldMeshModel = m_pD3DXMesh;

	pOldMeshModel->CloneMesh(D3DXMESH_MANAGED,
		vElementsModel,
		m_pD3DDevice,
		&m_pD3DXMesh);

	// もういらないのでリリース
	SAFE_DELETE_OBJ(pOldMeshModel);

	D3DXComputeNormals(m_pD3DXMesh, NULL);

	m_pMat = (D3DXMATERIAL *)m_pD3DXBuffMat->GetBufferPointer();

	return S_OK;
}

//=============================================================================
// Uninit
//=============================================================================
void Model::Uninit(void)
{
	SAFE_DELETE_OBJ(m_pD3DTexture);
	SAFE_DELETE_OBJ(m_pD3DXBuffMat);
	SAFE_DELETE_OBJ(m_pD3DXMesh);
	SAFE_DELETE_OBJ(m_pDecl);
}

//=============================================================================
// Update
//=============================================================================
void Model::Update(void)
{
	if (m_pInput->GetKeyboardPress(DIK_LEFT))
	{
		m_rot.y += 0.1f;
	}

	if (m_pInput->GetKeyboardPress(DIK_RIGHT))
	{
		m_rot.y -= 0.1f;
	}

	m_pMat = (D3DXMATERIAL *)m_pD3DXBuffMat->GetBufferPointer();

	SetWorldMtx();
}

//=============================================================================
// Draw
//=============================================================================
void Model::Draw(void)
{
	D3DMATERIAL9 mat;

	m_pD3DDevice->GetMaterial(&mat);
	for (int nCnt = 0; nCnt < (int)m_dwNumMat; nCnt++)
	{
		m_pD3DDevice->SetVertexDeclaration(m_pDecl);

		m_pD3DXMesh->DrawSubset(nCnt);
	}

	m_pD3DDevice->SetMaterial(&mat);
}

//=============================================================================
// SetWorldMtx
//=============================================================================
void Model::SetWorldMtx(void)
{
	D3DXMATRIX mtxScl;
	D3DXMATRIX mtxRot;
	D3DXMATRIX mtxTranslate;

	D3DXMatrixIdentity(&m_mtxWorld);
	// scale
	D3DXMatrixScaling(&mtxScl, m_scl.x, m_scl.y, m_scl.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScl);
	// rotation
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	// position
	D3DXMatrixTranslation(&mtxTranslate, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTranslate);
}

//=============================================================================
// GetMaterial
//=============================================================================
D3DXMATERIAL* Model::GetMaterial(void)
{
	return m_pMat;
}

// EOF