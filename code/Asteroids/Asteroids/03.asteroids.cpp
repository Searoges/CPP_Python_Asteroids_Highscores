//SDL2 flashing random color example
//Should work on iOS/Android/Mac/Windows/Linux

#include <SDL.h>
#undef  main

#include <stdlib.h> //rand()
#include "engine/timer.h"

#include <list>
#include "engine/Renderer.h"
#include "engine/Input.h"

#include "game/AstGame.h"

bool quitting = false;
float r = 0.0f;

#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2.lib")

int main(int argc, char *argv[]) 
{
	Renderer::Get()->OnStartUp();
	Input::Get()->Init();
	
	Timer frameTimer, fpsTimer;
	
	float elaspedTime = 0;
	float fpsTime = 0;

	if (AstGame::Get()->OnOneTimeInit() != false)
	{		
		frameTimer.Start();

		while (!quitting)
		{
			SDL_Event event;

			fpsTimer.Stop();
			fpsTime = fpsTimer.GetmS();
			fpsTimer.Start();
								
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					quitting = true;
				}
			}

			Input::Get()->Update();

			AstGame::Get()->stateMachine.Update();
			{				
				AstGame::Get()->stateMachine.Draw();

				Renderer::Get()->debugPrinter->Print(10, 80, RGBATOCOLOR(255, 0, 0, 255), "%f %f %f", elaspedTime, fpsTime, 1000.0f/fpsTime);

				Renderer::Get()->OnEndFrame();
				SDL_RenderPresent(Renderer::Get()->renderer);
				
				frameTimer.Stop();
				elaspedTime = frameTimer.GetmS();
				

				if (elaspedTime < 17)
				{
					Sleep((DWORD)(17 - elaspedTime));					
				}
				
				frameTimer.Start();
			}
		}
	}	

	Renderer::Get()->OnShutdown();
}