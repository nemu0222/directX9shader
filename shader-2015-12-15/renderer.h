//=============================================================================
// renderer.h
// Author : Noriyuki Honda
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

//=============================================================================
// include
//=============================================================================
#include "main.h"

//=============================================================================
// class
//=============================================================================
class Renderer
{
public:
	Renderer(void)
	{
#ifdef _DEBUG
		m_pD3DXFont = NULL;
#endif // _DEBUG
	}
	virtual ~Renderer(void){}

	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit(void);
	bool BeginDraw(void);
	void EndDraw(void);

#ifdef _DEBUG
	void DrawFPS(void);
#endif // _DEBUG

	LPDIRECT3DDEVICE9 GetDevice(void){ return m_pD3DDevice; };

private:
	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pD3DDevice;

#ifdef _DEBUG
	LPD3DXFONT m_pD3DXFont;
#endif // _DEBUG
};

#endif // _RENDERER_H_

// EOF