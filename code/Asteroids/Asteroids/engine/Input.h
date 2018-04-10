#pragma once
#pragma once
#include <windows.h>
#include "typedef.h"
#include "Singleton.h"

enum KeyState { KeyState_NotPressed, KeyState_Pressed, KeyState_Held, KeyState_Released };

class Input : public Singleton<Input>
{
public:

	void Init();
	void Update();

	KeyState GetKeyState(u8 keyID);

protected:
	
	bool keyState[255];
	KeyState processedKeys[255];
};

