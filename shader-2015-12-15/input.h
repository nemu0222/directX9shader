//=============================================================================
// input.h
// Author : Noriyuki Honda
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

//=============================================================================
// include
//=============================================================================
#include "main.h"

//=============================================================================
// macro
//=============================================================================
#define KEY_MAX (256)

//=============================================================================
// class
//=============================================================================
class Input
{
public:
	Input(void)
	{
		m_pDInput = NULL;
		m_pDIDeviceKey = NULL;
		for (int i = 0; i < 256; i++)
		{
			m_aKeyStatePress[i] = NULL;
			m_aKeyStatePressOld[i] = NULL;
			m_aKeyStateRelease[i] = NULL;
			m_aKeyStateTrigger[i] = NULL;
		}
	}
	virtual ~Input(void){}

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	bool GetKeyboardPress(int nKey);
	bool GetKeyboardTrigger(int nKey);
	bool GetKeyboardRepeat(int nKey);
	bool GetKeyboardRelease(int nKey);

private:
	LPDIRECTINPUT8 m_pDInput;
	LPDIRECTINPUTDEVICE8 m_pDIDeviceKey;

	BYTE m_aKeyStatePress[KEY_MAX];
	BYTE m_aKeyStatePressOld[KEY_MAX];
	BYTE m_aKeyStateTrigger[KEY_MAX];
	BYTE m_aKeyStateRelease[KEY_MAX];

	int m_nRepeatCount;
};

#endif // _INPUT_H_

// EOF