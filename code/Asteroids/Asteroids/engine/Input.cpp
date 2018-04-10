#include "Input.h"


void Input::Init()
{
	for (int i = 0; i < 255; i++)
	{
		processedKeys[i] = KeyState_NotPressed;
	}
}
void Input::Update()
{
	for (int i = 0; i < 255; i++)
	{
		bool rawState = GetAsyncKeyState(i);

		if (processedKeys[i] == KeyState_NotPressed)
		{
			if (rawState == true)
			{
				processedKeys[i] = KeyState_Pressed;
			}
		}
		else
		{
			if (processedKeys[i] == KeyState_Pressed)
			{
				if (rawState == true)
				{
					processedKeys[i] = KeyState_Held;
				}
				else
				{
					processedKeys[i] = KeyState_Released;
				}
			}
			else
			{
				if (processedKeys[i] == KeyState_Held)
				{
					if (rawState == true)
					{
						processedKeys[i] = KeyState_Held;
					}
					else
					{
						processedKeys[i] = KeyState_Released;
					}
				}
				else
				{
					if (processedKeys[i] == KeyState_Released)
					{
						processedKeys[i] = KeyState_NotPressed;
					}
				}
			}
		}
	}
}

KeyState Input::GetKeyState(u8 keyID)
{
	return processedKeys[keyID];
}