//=============================================================================
// shader.h
// Author : Noriyuki Honda
//=============================================================================
#ifndef _SHADER_H_
#define _SHADER_H_

//=============================================================================
// include
//=============================================================================
#include "main.h"

//=============================================================================
// class
//=============================================================================
class Shader
{
public:
	Shader(void){}
	virtual ~Shader(void){}

	static Shader* Create(LPDIRECT3DDEVICE9 pDevice,
		LPCSTR pVertexShaderSrcFile,
		LPCSTR pVertexShaderFunctionName,
		LPCSTR pPixelShaderSrcFile,
		LPCSTR pPixelShaderFunctionName);

	void Release(void);

	// シェーダーの適用
	void Attach(void);
	// シェーダーの適用を外す
	void Detach(void);

	void SetMtx(D3DXHANDLE hC, D3DXMATRIX *pMtx);
	void SetTex(D3DXHANDLE pSamplerName, LPDIRECT3DTEXTURE9 pTex);
	void SetFloatArray(D3DXMATERIAL *pMat);
	void SetValue(D3DXHANDLE hC, D3DXVECTOR3 vtx);

private:
	void CreateInstance(LPDIRECT3DDEVICE9 pDevice,
		LPCSTR pVertexShaderSrcFile,
		LPCSTR pVertexShaderFunctionName,
		LPCSTR pPixelShaderSrcFile,
		LPCSTR pPixelShaderFunctionName);

	// VertexShader
	LPDIRECT3DVERTEXSHADER9 m_pVertexShader;
	LPD3DXCONSTANTTABLE m_pVertexShaderCompile;

	// PixelShader
	LPDIRECT3DPIXELSHADER9 m_pPixelShader;
	LPD3DXCONSTANTTABLE m_pPixelShaderCompile;

	LPDIRECT3DDEVICE9 m_pD3DDevice;
};

#endif // _SHADER_H_

// EOF