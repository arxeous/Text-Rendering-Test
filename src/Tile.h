#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Texture.h"

class Tile {
public: 
	Tile(int x, int y, int w, int h, int tileType);

	void render(SDL_Renderer* renderer,  SDL_Rect& camera, Texture* texture, SDL_Rect tileClip[]);

	int getType();

	SDL_Rect getBox();
private:
	SDL_Rect m_Box;
	int m_Type;
	bool checkCollision(SDL_Rect a, SDL_Rect b);
};