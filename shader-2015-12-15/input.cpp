//=============================================================================
// input.cpp
// Author : Noriyuki Honda
//=============================================================================

//=============================================================================
// include
//=============================================================================
#include "input.h"

//=============================================================================
// Init
// hInstance : �C���X�^���X�n���h��
// hWnd      : �E�B���h�E�n���h��
//=============================================================================
HRESULT Input::Init(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr;

	if (m_pDInput == NULL)
	{
		hr = DirectInput8Create(hInstance,
			DIRECTINPUT_VERSION,
			IID_IDirectInput8,
			(void **)&m_pDInput,
			NULL);
		if (FAILED(hr))
		{
			return hr;
		}
	}

	hr = m_pDInput->CreateDevice(GUID_SysKeyboard,
		&m_pDIDeviceKey,
		NULL);
	if (FAILED(hr))
	{
		return hr;
	}

	hr = m_pDIDeviceKey->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
	{
		return hr;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	hr = m_pDIDeviceKey->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));

	// ���͐���J�n
	m_pDIDeviceKey->Acquire();

	return S_OK;
}

//=============================================================================
// Uninit
//=============================================================================
void Input::Uninit(void)
{
	SAFE_DELETE_OBJ(m_pDInput);
	SAFE_DELETE_KEYOBJ(m_pDIDeviceKey);
}

//=============================================================================
// Update
//=============================================================================
void Input::Update(void)
{
	BYTE aKeyState[KEY_MAX];
	if (SUCCEEDED(m_pDIDeviceKey->GetDeviceState(sizeof(aKeyState),
		&aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey < 256; nCntKey++)
		{
			m_aKeyStatePress[nCntKey] = aKeyState[nCntKey];
			m_aKeyStateTrigger[nCntKey] = ((m_aKeyStatePress[nCntKey] ^ m_aKeyStatePressOld[nCntKey]) & m_aKeyStatePress[nCntKey]);
			m_aKeyStateRelease[nCntKey] = ((m_aKeyStatePress[nCntKey] ^ m_aKeyStatePressOld[nCntKey]) & ~m_aKeyStatePress[nCntKey]);
			m_aKeyStatePressOld[nCntKey] = m_aKeyStatePress[nCntKey];
		}
	}

	else
	{
		m_pDIDeviceKey->Acquire();
	}
}

//=============================================================================
// GetKeyboardPress
// nKey : �L�[
//=============================================================================
bool Input::GetKeyboardPress(int nKey)
{
	if (m_aKeyStatePress[nKey] & 0x80)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//=============================================================================
// GetKeyboardTrigger
// nKey : �L�[
//=============================================================================
bool Input::GetKeyboardTrigger(int nKey)
{
	if (m_aKeyStateTrigger[nKey] & 0x80)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//=============================================================================
// GetKeyboardRelease
// nKey : �L�[
//=============================================================================
bool Input::GetKeyboardRelease(int nKey)
{
	if (m_aKeyStateRelease[nKey] & 0x80)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//=============================================================================
// GetKeyboardRepeat
// nKey : �L�[
//=============================================================================
bool Input::GetKeyboardRepeat(int nKey)
{
	if (m_aKeyStateTrigger[nKey] & 0x80)
	{
		return true;
	}
	if (m_aKeyStatePress[nKey] & 0x80)
	{
		m_nRepeatCount++;

		// ��莞�Ԃ�������KeyPress�ɕύX
		if (m_nRepeatCount >= 30)
		{
			if (m_aKeyStatePress[nKey] & 0x80)
			{
				return true;
			}
			m_nRepeatCount = 0;
			return false;
		}
		m_nRepeatCount = 0;
		return false;
	}
	else
	{
		m_nRepeatCount = 0;
		return false;
	}
}

// EOF