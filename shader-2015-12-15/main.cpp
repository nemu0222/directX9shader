//=============================================================================
// main.cpp
// Author : Noriyuki Honda
//=============================================================================

//=============================================================================
// include
//=============================================================================
#include "main.h"
#include "manager.h"

//=============================================================================
// macro
//=============================================================================
#define CLASS_NAME "AppClass"
#define WINDOW_NAME "DirectX9ShaderProgramming"

//=============================================================================
// prototype
//=============================================================================
// WindowProcedure
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//=============================================================================
// global
//=============================================================================
#ifdef _DEBUG
int g_nCountFPS;
#endif // _DEBUG

//=============================================================================
// main
// hInstance     : インスタンスハンドル
// hPrevInstance : 特に使っていない
// lpCmdLine     : コマンドライン引数(特に使っていない)
// nCmdShow      : ウィンドウの最小化、最大化、通常表示等のフラグ
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// メモリリークチェック
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// 無くても良いけど、警告が出る(未使用宣言)
	UNREFERENCED_PARAMETER(hPrevInstance);
	// 無くても良いけど、警告が出る(未使用宣言)
	UNREFERENCED_PARAMETER(lpCmdLine);

	// 変数宣言
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;
	MSG msg;
	HWND hWnd;

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)GetStockObject(BLACK_BRUSH),
		NULL,
		CLASS_NAME,
		NULL
	};

	RegisterClassEx(&wcex);

	hWnd = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(int)SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2,
		(int)SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),
		NULL,
		NULL,
		hInstance,
		NULL);

	Manager* pManager = new Manager();
	pManager->Init(hInstance, hWnd, true);

	timeBeginPeriod(1);
	dwExecLastTime =
		dwFPSLastTime = timeGetTime();
	dwCurrentTime =
		dwFrameCount = 0;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{
#ifdef _DEBUG
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
#endif // _DEBUG
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				pManager->Update();
				pManager->Draw();

				dwFrameCount++;
			}
		}
	}

	UnregisterClass(CLASS_NAME, wcex.hInstance);
	SAFE_DELETE_CLASSOBJ(pManager);
	timeEndPeriod(1);

	return (int)msg.wParam;
}

//=============================================================================
// WindowProcedure
// hWnd   : ウィンドウハンドル
// uMsg   : メッセージ
// wParam : メッセージの1番目のパラメータ
// lParam : メッセージの2番目のパラメータ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

#ifdef _DEBUG
//=============================================================================
// GetFPSCounter
//=============================================================================
int GetFPSCounter(void)
{
	return g_nCountFPS;
}
#endif // _DEBUG

// EOF