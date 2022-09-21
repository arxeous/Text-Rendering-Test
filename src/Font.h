#pragma once
#include <SDL.h>
#include "Texture.h"

class Font 
{

public:
	//The default constructor
	Font();

	//Generates the font
	bool buildFont(Texture* fontTexture);

	//Shows the text
	void renderText(SDL_Renderer* renderer, int x, int y, std::string text, float scale = 1.0);

private:
	//The font texture
	Texture* m_FontTexture;

	//The individual characters in the surface
	SDL_Rect m_Chars[256];

	//Spacing Variables
	int m_NewLine, m_Space;

};