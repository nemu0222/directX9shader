//=============================================================================
// rendertarget.cpp
// Author : Noriyuki Honda
//=============================================================================

//=============================================================================
// include
//=============================================================================
#include "rendertarget.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// Init
// pManager       : �}�l�[�W���[�N���X�|�C���^
// nTexSizeWidth  : �����_�[�^�[�Q�b�g�p�̃e�N�X�`����\�����镝
// nTexSizeHeight : �����_�[�^�[�Q�b�g�p�̃e�N�X�`����\�����鍂��
// format         : �e�N�X�`���t�H�[�}�b�g
//=============================================================================
HRESULT RenderTarget::Init(Manager* pManager,int nTexSizeWidth, int nTexSizeHeight,D3DFORMAT format)
{
	m_pD3DDevice = pManager->GetRenderer()->GetDevice();
	m_nTexSizeWidth = nTexSizeWidth;
	m_nTexSizeHeight = nTexSizeHeight;
	m_format = format;
	// �����_�[�^�[�Q�b�g�̐ݒ�
	// �e�N�X�`���쐬
	HRESULT ret;
	ret = m_pD3DDevice->CreateTexture(m_nTexSizeWidth,
		m_nTexSizeHeight,
		1,
		D3DUSAGE_RENDERTARGET,
		m_format,
		D3DPOOL_DEFAULT,
		&m_pD3DTexture,
		NULL);
	if (FAILED(ret))
	{
		// ���������s
		return E_FAIL;
	}

	// �����_�[�^�[�Q�b�g�p�T�[�t�F�X�擾
	m_pD3DTexture->GetSurfaceLevel(0, &m_pRenderTarget);
	if (FAILED(m_pD3DDevice->CreateDepthStencilSurface(m_nTexSizeWidth,
		m_nTexSizeHeight,
		D3DFMT_D24S8,
		D3DMULTISAMPLE_NONE,
		0,
		TRUE,
		&m_pDepthStencilSurface,
		NULL)))
	{
		// ���������s
		return E_FAIL;
	}

	// �o�b�N�T�[�t�F�X�ۑ�
	m_pD3DDevice->GetRenderTarget(0, &m_pRenderTargetBack);
	m_pD3DDevice->GetDepthStencilSurface(&m_pDepthStencilSurfaceBack);

	return S_OK;
}

//=============================================================================
// Uninit
//=============================================================================
void RenderTarget::Uninit(void)
{
	SAFE_DELETE_OBJ(m_pD3DTexture);
	SAFE_DELETE_OBJ(m_pRenderTarget);
	SAFE_DELETE_OBJ(m_pRenderTargetBack);
	SAFE_DELETE_OBJ(m_pDepthStencilSurface);
	SAFE_DELETE_OBJ(m_pDepthStencilSurfaceBack);
}

//=============================================================================
// Attach
//=============================================================================
void RenderTarget::Attach(void)
{
	// �r���[�|�[�g�ۑ�
	m_pD3DDevice->GetViewport(&m_ViewportBackup);

	// �����_�[�^�[�Q�b�g���e�N�X�`���ɂ���
	m_pD3DDevice->SetRenderTarget(0, m_pRenderTarget);
	m_pD3DDevice->SetDepthStencilSurface(m_pDepthStencilSurface);

	// �r���[�|�[�g�ݒ�
	D3DVIEWPORT9 vpSet;
	vpSet.X = 0;
	vpSet.Y = 0;
	vpSet.Width = m_nTexSizeWidth;
	vpSet.Height = m_nTexSizeHeight;
	vpSet.MinZ = 0.0f;
	vpSet.MaxZ = 1.0f;

	m_pD3DDevice->SetViewport(&vpSet);
}

//=============================================================================
// Detach
//=============================================================================
void RenderTarget::Detach(void)
{
	m_pD3DDevice->SetRenderTarget(0, m_pRenderTargetBack);
	m_pD3DDevice->SetDepthStencilSurface(m_pDepthStencilSurfaceBack);

	// �O�̃r���[�|�[�g�ɖ߂�
	m_pD3DDevice->SetViewport(&m_ViewportBackup);
}

// EOF