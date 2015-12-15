//=============================================================================
// camera.h
// Author : Noriyuki Honda
//=============================================================================
#ifndef _CCAMERA_H_
#define _CCAMERA_H_

//=============================================================================
// include
//=============================================================================
#include "main.h"

class Manager;

//=============================================================================
// class
//=============================================================================
class Camera
{
public:
	Camera(void){}
	virtual ~Camera(void){}

	HRESULT Init(Manager *pManager);
	void Uninit(void);
	void Update(void);

	void SetCamera(void);

	D3DXVECTOR3 GetRotation(void){ return m_rot; }
	D3DXMATRIX GetView(void){ return m_mtxView; }
	D3DXMATRIX GetProjection(void){ return m_mtxProjection; }
	void SetPosition(float PosX, float PosY, float PosZ){}
	D3DXVECTOR3 GetCameraP(void){ return m_posCameraP; }
	D3DXVECTOR3 GetCameraR(void){ return m_posCameraR; }
	D3DXVECTOR3 GetCameraV(void){ return m_vecCameraV; }

public:
	LPDIRECT3DDEVICE9 m_pD3DDevice;

	// カメラ視点
	D3DXVECTOR3 m_posCameraP;
	// カメラ注視点
	D3DXVECTOR3 m_posCameraR;
	// カメラ上方向ベクトル
	D3DXVECTOR3 m_vecCameraV;

	// 目的視点
	D3DXVECTOR3 m_posCameraPDest;
	// 目的注視点
	D3DXVECTOR3 m_posCameraRDest;

	D3DXVECTOR3 m_rot;

	D3DXMATRIX m_mtxView;
	D3DXMATRIX m_mtxProjection;

	float m_fDistance;
	float m_fMoveSpeed;

	Manager* m_pManager;
};

#endif // _CAMERA_H_

// EOF