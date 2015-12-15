//=============================================================================
// shader.cpp
// Author : Noriyuki Honda
//=============================================================================

//=============================================================================
// include
//=============================================================================
#include "shader.h"

//=============================================================================
// CreateInsntace
// pDevice                   : �f�o�C�X
// pVertexShaderSrcFile      : ���_�V�F�[�_�[�t�@�C��
// pVertexShaderFunctionName : ���_�V�F�[�_�[�֐���
// pPixelShaderSrcFile       : �s�N�Z���V�F�[�_�[�t�@�C��
// pPixelShaderFunctionName  : �s�N�Z���V�F�[�_�[�֐���
//=============================================================================
void Shader::CreateInstance(LPDIRECT3DDEVICE9 pDevice,
	LPCSTR pVertexShaderSrcFile,
	LPCSTR pVertexShaderFunctionName,
	LPCSTR pPixelShaderSrcFile,
	LPCSTR pPixelShaderFunctionName)
{
	m_pD3DDevice = pDevice;

	LPD3DXBUFFER error, VS_code, PS_code;

	m_pVertexShader = NULL;
	m_pVertexShaderCompile = NULL;
	m_pPixelShader = NULL;
	m_pPixelShaderCompile = NULL;

	// VertexShader
	HRESULT hr = D3DXCompileShaderFromFile(pVertexShaderSrcFile,
		NULL,
		NULL,
		pVertexShaderFunctionName,
		"vs_2_0",
		0,
		&VS_code,
		&error,
		&m_pVertexShaderCompile);
	if (FAILED(hr))
	{
		MessageBox(NULL, (char *)error->GetBufferPointer(), "error", MB_OK);
	}
	pDevice->CreateVertexShader((DWORD *)VS_code->GetBufferPointer(), &m_pVertexShader);

	// PixelShader
	hr = D3DXCompileShaderFromFile(pPixelShaderSrcFile,
		NULL,
		NULL,
		pPixelShaderFunctionName,
		"ps_2_0",
		0,
		&PS_code,
		&error,
		&m_pPixelShaderCompile);
	if (FAILED(hr))
	{
		MessageBox(NULL, (char *)error->GetBufferPointer(), "error", MB_OK);
	}
	pDevice->CreatePixelShader((DWORD *)PS_code->GetBufferPointer(), &m_pPixelShader);
}

//=============================================================================
// Release
//=============================================================================
void Shader::Release(void)
{
	SAFE_DELETE_OBJ(m_pVertexShader);
	SAFE_DELETE_OBJ(m_pVertexShaderCompile);
	SAFE_DELETE_OBJ(m_pPixelShader);
	SAFE_DELETE_OBJ(m_pPixelShaderCompile);
}

//=============================================================================
// Attach
//=============================================================================
void Shader::Attach(void)
{
	m_pD3DDevice->SetVertexShader(m_pVertexShader);
	m_pD3DDevice->SetPixelShader(m_pPixelShader);
}

//=============================================================================
// Detach
//=============================================================================
void Shader::Detach(void)
{
	m_pD3DDevice->SetVertexShader(NULL);
	m_pD3DDevice->SetPixelShader(NULL);
}

//=============================================================================
// SetMtx
// hC   : �萔�̈�Ɋi�[���镨
// pMtx : �}�g���N�X�|�C���^
//=============================================================================
void Shader::SetMtx(D3DXHANDLE hC, D3DXMATRIX *pMtx)
{
	m_pVertexShaderCompile->SetMatrix(m_pD3DDevice, hC, pMtx);
}

//=============================================================================
// setTex
// pSamplerName : �e�N�X�`���t�@�C����
// pTex         : �e�N�X�`���|�C���^
//=============================================================================
void Shader::SetTex(D3DXHANDLE pSamplerName, LPDIRECT3DTEXTURE9 pTex)
{
	m_pD3DDevice->SetTexture(m_pPixelShaderCompile->GetSamplerIndex(pSamplerName), pTex);
}

//=============================================================================
// setFloatArray
// pMat : �}�e���A���|�C���^
//=============================================================================
void Shader::SetFloatArray(D3DXMATERIAL *pMat)
{
	D3DXVECTOR3 lightDir(-1.0f, -1.0f, 1.0f);

	m_pVertexShaderCompile->SetFloatArray(m_pD3DDevice, "LocalLightDir", lightDir, 3);
	m_pVertexShaderCompile->SetFloatArray(m_pD3DDevice, "LightDiffuse", D3DXVECTOR4(0.7f, 0.7f, 0.7f, 1.0f), 4);
	m_pVertexShaderCompile->SetFloatArray(m_pD3DDevice, "LightAmbient", D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f), 4);
	m_pVertexShaderCompile->SetFloatArray(m_pD3DDevice, "MatDiffuse", (float *)&pMat->MatD3D.Diffuse, 4);
	m_pVertexShaderCompile->SetFloatArray(m_pD3DDevice, "MatAmbient", (float *)&pMat->MatD3D.Ambient, 4);
}

//=============================================================================
// SetValue
// hC  : �萔�̈於
// vtx : ���W
//=============================================================================
void Shader::SetValue(D3DXHANDLE hC, D3DXVECTOR3 vtx)
{
	m_pVertexShaderCompile->SetValue(m_pD3DDevice, "playerPos", &vtx, sizeof(float) * 3);
}

//=============================================================================
// Create
// pDevice                   : �f�o�C�X
// pVertexShaderSrcFile      : ���_�V�F�[�_�[�t�@�C��
// pVertexShaderFunctionName : ���_�V�F�[�_�[�֐���
// pPixelShaderSrcFile       : �s�N�Z���V�F�[�_�[�t�@�C��
// pPixelShaderFunctionName  : �s�N�Z���V�F�[�_�[�֐���
//=============================================================================
Shader* Shader::Create(LPDIRECT3DDEVICE9 pDevice,
	LPCSTR pVertexShaderSrcFile,
	LPCSTR pVertexShaderFunctionName,
	LPCSTR pPixelShaderSrcFile,
	LPCSTR pPixelShaderFunctionName)
{
	Shader *pShader = new Shader();

	pShader->CreateInstance(pDevice,
		pVertexShaderSrcFile,
		pVertexShaderFunctionName,
		pPixelShaderSrcFile,
		pPixelShaderFunctionName);

	return pShader;
}

// EOF