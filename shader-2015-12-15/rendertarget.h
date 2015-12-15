//=============================================================================
// rendertarget.h
// Author : Noriyuki Honda
//=============================================================================
#ifndef _RENDERTARGET_H_
#define _RENDERTARGET_H_

//=============================================================================
// include
//=============================================================================
#include "main.h"

class Manager;

//=============================================================================
// class
//=============================================================================
class RenderTarget
{
public:
	RenderTarget(void)
	{
		m_pD3DDevice = NULL;
		m_pD3DTexture = NULL;
		m_pRenderTarget = NULL;
		m_pRenderTargetBack = NULL;
		m_pDepthStencilSurface = NULL;
		m_pDepthStencilSurfaceBack = NULL;
	}
	virtual ~RenderTarget(void){}

	HRESULT Init(Manager* pManager,int nTexSizeWidth, int nTexSizeHeight,D3DFORMAT format);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Attach(void);
	void Detach(void);
private:
	LPDIRECT3DTEXTURE9 m_pD3DTexture;
	LPDIRECT3DSURFACE9 m_pRenderTarget;
	LPDIRECT3DSURFACE9 m_pRenderTargetBack;
	LPDIRECT3DSURFACE9 m_pDepthStencilSurface;
	LPDIRECT3DSURFACE9 m_pDepthStencilSurfaceBack;

	D3DVIEWPORT9 m_ViewportBackup;

	LPDIRECT3DDEVICE9 m_pD3DDevice;

	int m_nTexSizeWidth;
	int m_nTexSizeHeight;

	D3DFORMAT m_format;

	Manager* m_pManager;
};

#endif // _RENDERTARGET_H_

// EOF