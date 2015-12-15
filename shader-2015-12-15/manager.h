//=============================================================================
// manager.h
// Author : Noriyuki Honda
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//=============================================================================
// include
//=============================================================================
#include "main.h"
#include "renderer.h"

class Renderer;
class Input;
class Camera;
class RenderTarget;

//=============================================================================
// class
//=============================================================================
class Manager
{
public:
	Manager(void){}
	virtual ~Manager(void){}

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	Renderer* GetRenderer(void){ return m_pRenderer; }
	Input* GetInput(void){ return m_pInput; }
	Camera* GetCamera(void){ return m_pCamera; }

private:
	Renderer* m_pRenderer;
	Input* m_pInput;
	Camera* m_pCamera;
	RenderTarget* m_pRenderTarget;
};

#endif // _MANAGER_H_

// EOF