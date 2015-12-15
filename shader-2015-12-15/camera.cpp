//=============================================================================
// camera.cpp
// Author : Noriyuki Honda
//=============================================================================

//=============================================================================
// include
//=============================================================================
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include <math.h>

//=============================================================================
// macro
//=============================================================================
#define POS_CAMERA_X (0.0f)
#define POS_CAMERA_Y (400.0f)
#define POS_CAMERA_Z (400.0f)

#define MOVE_SPEED (6.0f)

//=============================================================================
// Init
// pMgr : マネージャークラスポインタ
//=============================================================================
HRESULT Camera::Init(Manager *pManager)
{
	// デバイス取得
	m_pManager = pManager;
	m_pD3DDevice = pManager->GetRenderer()->GetDevice();

	m_rot.y = 0.0f;

	m_posCameraP.x = POS_CAMERA_X;
	m_posCameraP.y = POS_CAMERA_Y;
	m_posCameraP.z = POS_CAMERA_Z;

	m_posCameraR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecCameraV = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	m_fDistance = sqrt(pow(m_posCameraP.x - m_posCameraR.x, 2) + pow(m_posCameraP.z - m_posCameraR.z, 2));

	m_fMoveSpeed = MOVE_SPEED;

	return S_OK;
}

//=============================================================================
// Uninit
//=============================================================================
void Camera::Uninit(void)
{
}

//=============================================================================
// Update
//=============================================================================
void Camera::Update(void)
{
}

//=============================================================================
// SetCamera
//=============================================================================
void Camera::SetCamera(void)
{
	D3DXMatrixIdentity(&m_mtxView);
	D3DXMatrixLookAtLH(&m_mtxView, &m_posCameraP, &m_posCameraR, &m_vecCameraV);
	m_pD3DDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	D3DXMatrixIdentity(&m_mtxProjection);
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,D3DXToRadian(90),SCREEN_WIDTH / SCREEN_HEIGHT,1.0f,1000.0f);
	m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}

// EOF