//=============================================================================
// manager.cpp
// Author : Noriyuki Honda
//=============================================================================

//=============================================================================
// include
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "camera.h"
#include "rendertarget.h"

//=============================================================================
// Init
// hInstance : インスタンスハンドル
// hWnd      : ウィンドウハンドル
// bWindow   : ウィンドウモードかフルスクリーン
//=============================================================================
HRESULT Manager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	m_pRenderer = new Renderer();
	m_pRenderer->Init(hWnd, bWindow);

	m_pInput = new Input();
	m_pInput->Init(hInstance, hWnd);

	m_pCamera = new Camera();
	m_pCamera->Init(this);

	m_pRenderTarget = new RenderTarget();
	m_pRenderTarget->Init(this, 256, 256, D3DFMT_A8R8G8B8);

	return S_OK;
}

//=============================================================================
// Uninit
//=============================================================================
void Manager::Uninit(void)
{
	SAFE_DELETE_CLASSOBJ(m_pRenderTarget);
	SAFE_DELETE_CLASSOBJ(m_pCamera);
	SAFE_DELETE_CLASSOBJ(m_pInput);
	SAFE_DELETE_CLASSOBJ(m_pRenderer);
}

//=============================================================================
// Update
//=============================================================================
void Manager::Update(void)
{
	m_pInput->Update();
	m_pCamera->Update();
}

//=============================================================================
// Draw
//=============================================================================
void Manager::Draw(void)
{
	m_pRenderer->BeginDraw();

	m_pCamera->SetCamera();

	m_pRenderTarget->Attach();
	m_pRenderTarget->Detach();

	m_pRenderer->EndDraw();
}

// EOF