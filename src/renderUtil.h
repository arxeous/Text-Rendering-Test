#pragma once
#include "Tile.h"
#include "TileSet.h"


//Screen dimension constants
const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 700;

//Tile constants
const int TILE_WIDTH = 67;
const int TILE_HEIGHT = 67;
const int TILE_SIZE_SQUARE= 67;
const int TOTAL_TILES = 192;
const int TOTAL_TILE_SPRITES = 12;

const int BIT_RECT_SIZE_2 = TILE_SIZE_SQUARE / 2;
const int BIT_RECT_SIZE_3= TILE_SIZE_SQUARE / 3;



//Starts up SDL and creates window
bool init(SDL_Window*& window, SDL_Renderer*& renderer, int w, int h);

//Loads media
bool loadMedia(Tile* tiles[], SDL_Rect tileClips[], SDL_Renderer*& renderer, Texture*& tileTexture);

//Frees media and shuts down SDL
void close(Tile* tiles[], SDL_Window*& window, SDL_Renderer*& renderer, Texture*& tileTexture);

void close(SDL_Window*& window, SDL_Renderer*& renderer, TileSet*& tileTexture);


