#pragma once
#include <SDL.h>
#include "typedef.h"
#include "Singleton.h"
#include "DebugPrinter.h"
#include "Vector2.h"


int RGBATOCOLOR(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
int RGBTOCOLOR(unsigned char r, unsigned char g, unsigned char b);
void COLORTORGBA(int col, unsigned char& r, unsigned char& g, unsigned char& b, unsigned char& a);

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))

#define PI (3.1416f)

float inline DEG_TO_RAD(float degree)
{
	return (PI * degree) / 180.0f;
}


class Renderer : public Singleton<Renderer>
{
public:

	struct Viewport
	{
		Viewport() {};
		Viewport(u32 x, u32 y, u32 w, u32 h)
		{
			this->x = x;
			this->y = y;
			Width = w;
			Height = h;
		}
		u32 x, y;
		u32 Width, Height;
	};

	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	Viewport viewport;

	bool OnStartUp();

	void DrawRect(float x, float y, float w, float h,u32 col);
	void DrawLine(Vector2& v0, u32 col0, Vector2& v1, u32 col1);
	void DrawCircle(Vector2& v0, float rad, u32 col0, int segments = 36);

	void OnEndFrame();
	void OnShutdown();
	
	DebugPrinter* debugPrinter;

	

	void SetViewport(const Viewport& v) { viewport = v; }
	void GetViewport(Viewport& v) { v = viewport; }

	u32 GetFrameCount();
private:
	u32 frameCount;
	
};
