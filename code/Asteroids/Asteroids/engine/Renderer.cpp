#include "Renderer.h"

int RGBATOCOLOR(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	return b | (g << 8) | (r << 16) | (a << 24);
}

void COLORTORGBA(int col, unsigned char& r, unsigned char& g, unsigned char& b, unsigned char& a)
{
	r = (col & 0x00ff0000) >> 16;
	g = (col & 0x0000ff00) >> 8;
	b = (col & 0x000000ff);
	a = (col & 0xff000000) >> 24;
}


int RGBTOCOLOR(unsigned char r, unsigned char g, unsigned char b)
{
	return RGBATOCOLOR(r, g, b, 255);
}


int SDLCALL watch(void *userdata, SDL_Event* event)
{

	if (event->type == SDL_APP_WILLENTERBACKGROUND)
	{
		//quitting = true;
	}

	return 1;
}

bool Renderer::OnStartUp()
{
	window = NULL;
	renderer = NULL;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
	{
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow("title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	debugPrinter = new DebugPrinter();
	debugPrinter->Init();

	SDL_AddEventWatch(watch, NULL);

	SetViewport(Viewport(0, 0, 800, 600));
	
	return true;
}

void Renderer::DrawRect(float x, float y, float w, float h, u32 col)
{
	SDL_Rect rect;

	rect.x = (s32)x;
	rect.y = (s32)y;
	rect.w = (s32)w;
	rect.h = (s32)h;

	unsigned char r, g, b, a;

	COLORTORGBA(col, r, g, b, a);


	SDL_SetRenderDrawColor(renderer, r,g,b,a);
	SDL_RenderFillRect(renderer, &rect);

}

void Renderer::DrawLine(Vector2 & v0, u32 col0, Vector2 & v1, u32 col1)
{
	unsigned char r, g, b, a;

	COLORTORGBA(col0, r, g, b, a);

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderDrawLine(renderer, (s32)v0.x, (s32)v0.y, (s32)v1.x, (s32)v1.y);
}

void Renderer::DrawCircle(Vector2& v0, float rad, u32 col0, int segments)
{
	u8 r, g, b, a;

	SDL_Point* points = new SDL_Point[segments * 2];

	int pointCount = 0;
	for (int i = 0; i < segments; i++)
	{
		points[pointCount].x = (int)(v0.x + (sin(DEG_TO_RAD((i * 360) / (float)segments))* rad));
		points[pointCount].y = (int)(v0.y + (cos(DEG_TO_RAD((i * 360) / (float)segments))* rad));
		pointCount++;

		points[pointCount].x = (int)(v0.x + (sin(DEG_TO_RAD((((i + 1) % segments) * 360) / (float)segments))* rad));
		points[pointCount].y = (int)(v0.y + (cos(DEG_TO_RAD((((i + 1) % segments) * 360) / (float)segments))* rad));
		pointCount++;
	}

	COLORTORGBA(col0, r, g, b, a);

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderDrawLines(renderer, points, pointCount);
}


void Renderer::OnEndFrame()
{
	frameCount++;
}

void Renderer::OnShutdown()
{
	SDL_DelEventWatch(watch, NULL);
	SDL_DestroyWindow(window);
	SDL_Quit();

	window = NULL;
	renderer = NULL;
}

u32 Renderer::GetFrameCount()
{
	return frameCount;
}
