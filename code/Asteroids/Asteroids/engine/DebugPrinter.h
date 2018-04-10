#pragma once
#include <SDL.h>

int RGBATOCOLOR(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
int RGBTOCOLOR(unsigned char r, unsigned char g, unsigned char b);
void COLORTORGBA(int col, unsigned char& r, unsigned char& g, unsigned char& b, unsigned char& a);

class DebugPrinter
{
public:
	void Init();
	void SetScale(float w, float h);

	enum Justification { Justify_Left, Justify_Right, Justify_Centre };
	void SetJustification(Justification just);
	void Print(int x, int y, int colour, const char* fmt, ...);

	

private:
	int calculateOffset(const char *buffer);

	SDL_Texture*    debugFont;

	float fontScaleX, fontScaleY;
	Justification currentJust;
};
