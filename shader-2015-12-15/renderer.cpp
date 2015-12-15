//=============================================================================
// renderer.cpp
// Author : Noriyuki Honda
//=============================================================================

//=============================================================================
// include
//=============================================================================
#include "renderer.h"

//=============================================================================
// Init
// hWnd    : ウィンドウハンドル
// bWindow : ウィンドウモードかフルスクリーン
//=============================================================================
HRESULT Renderer::Init(HWND hWnd, bool bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));								// ワークをゼロクリア
	d3dpp.BackBufferCount = 1;										// バックバッファの数
	d3dpp.BackBufferWidth = (int)SCREEN_WIDTH;						// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = (int)SCREEN_HEIGHT;					// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;							// バックバッファフォーマットはディスプレイモードに合わせて使う
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						// 映像信号に同期してフリップする
	d3dpp.Windowed = bWindow;										// ウィンドウモード
	d3dpp.EnableAutoDepthStencil = TRUE;							// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;					// デプスバッファとして16bitを使う(D24S8 : 最高品質　　D16 : 一般的)

	// ウィンドウモード
	if (bWindow)
	{
		d3dpp.FullScreen_RefreshRateInHz = 0;						// リフレッシュレート
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// インターバル
	}
	// フルスクリーン
	else
	{
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// リフレッシュレート
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// インターバル
	}

	// デバイスオブジェクトの生成
	// [デバイス作成制御]<描画>と<頂点処理>をハードウェアで行なう
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &m_pD3DDevice)))
	{
		// 上記の設定が失敗したら
		// [デバイス作成制御]<描画>をハードウェアで行い、<頂点処理>はCPUで行なう
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &m_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// [デバイス作成制御]<描画>と<頂点処理>をCPUで行なう
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &m_pD3DDevice)))
			{
				// 初期化失敗
				return E_FAIL;
			}
		}
	}

#ifdef _DEBUG
	D3DXCreateFont(m_pD3DDevice,
		18,
		0,
		0,
		0,
		FALSE,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		"Terminal",
		&m_pD3DXFont);
#endif // _DEBUG

	// レンダーステートパラメータの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// 裏面をカリング
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Zバッファを使用
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定

	// サンプラーステートパラメータの設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(U値)を設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(V値)を設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小フィルタモードを設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大フィルタモードを設定

	// テクスチャステージステートの設定
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理を設定
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数

	return S_OK;
}

//=============================================================================
// Uninit
//=============================================================================
void Renderer::Uninit(void)
{
#ifdef _DEBUG
	SAFE_DELETE_OBJ(m_pD3DXFont);
#endif // _DEBUG

	SAFE_DELETE_OBJ(m_pD3D);
	SAFE_DELETE_OBJ(m_pD3DDevice);
}

//=============================================================================
// BeginDraw
//=============================================================================
bool Renderer::BeginDraw(void)
{
	// バックバッファ＆Ｚバッファのクリア
	m_pD3DDevice->Clear(0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL),
		D3DCOLOR_RGBA(0, 0, 0, 0),
		1.0f,
		0);

	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		return true;
	}
	return false;
}

//=============================================================================
// EndDraw
//=============================================================================
void Renderer::EndDraw(void)
{
#ifdef _DEBUG
	DrawFPS();
#endif // _DEBUG

	m_pD3DDevice->EndScene();

	// バックバッファとフロントバッファの入れ替え
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

#ifdef _DEBUG
//=============================================================================
// DrawFPS
//=============================================================================
void Renderer::DrawFPS(void)
{
	RECT rect = { 0, 0, (LONG)SCREEN_WIDTH, (LONG)SCREEN_HEIGHT };
	char aStr[256];
	wsprintf(&aStr[0], "FPS : %d\n", GetFPSCounter());
	m_pD3DXFont->DrawText(NULL,
		&aStr[0],
		-1,
		&rect,
		DT_LEFT,
		D3DCOLOR_RGBA(0, 255, 255, 255));
}
#endif // _DEBUG

// EOF