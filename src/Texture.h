#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>

class Texture {
public:
	Texture();
	virtual ~Texture();

	bool loadFromFile(SDL_Renderer*& renderer, std::string filePath);
	bool loadFontFromFile(SDL_Renderer*& renderer, std::string filePath);

	void free();
	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	void setBlendMode(SDL_BlendMode blendMode);
	void setAlpha(Uint8 alpha);
	void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL, float scale = 1.0);

	int getWidth();
	int getHeight();

	bool lockTexture();
	bool unlockTexture();
	void* getPixels();
	int getPitch();
	Uint32 getPixel32(unsigned int x, unsigned int y);


protected:
	SDL_Texture* m_Texture;

	int m_Width;
	int m_Height;

	void* m_Pixels;
	int m_Pitch;

};
