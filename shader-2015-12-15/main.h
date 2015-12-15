//=============================================================================
// main.h
// Author : Noriyuki Honda
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//=============================================================================
// include
//=============================================================================
#include <windows.h>
#include "d3dx9.h"

#define DIRECTINPUT_VERSION (0x0800)
#include "dinput.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <tchar.h>
#include <stdio.h>

#include <time.h>

//=============================================================================
// library link
//=============================================================================
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dinput8.lib")

//=============================================================================
// macro
//=============================================================================
// 2Dポリゴン頂点フォーマット
#define	FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

// 3Dポリゴン頂点フォーマット
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (600)

#define SAFE_DELETE_CLASSOBJ(x){if (x != NULL){x->Uninit(); delete x; x = NULL;}}
#define SAFE_DELETE_OBJ(x){if (x != NULL){x->Release(); x = NULL;}}
#define SAFE_DELETE_KEYOBJ(x){if (x != NULL){x->Unacquire(); x->Release(); x = NULL;}}

//=============================================================================
// struct
//=============================================================================
// 2Dポリゴン頂点フォーマット構造体
typedef struct
{
	D3DXVECTOR3 vtx;
	float rhw;			// テクスチャのパースペクティブコレクト用
	D3DCOLOR diffuse;
	D3DXVECTOR2 tex;
} VERTEX_2D;

// 3Dポリゴン頂点フォーマット構造体
typedef struct
{
	D3DXVECTOR3 vtx;
	D3DXVECTOR3 nor;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
} VERTEX_3D;

//=============================================================================
// prototype
//=============================================================================
#ifdef _DEBUG
int GetFPSCounter(void);
#endif // _DEBUG

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new(_NORMAL_BLOCK,__FILE__,__LINE__)
#define new DBG_NEW
#endif // DBG_NEW
#endif // _DEBUG

#endif // _MAIN_H_

// EOF