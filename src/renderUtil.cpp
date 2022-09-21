#include "renderUtil.h"
#include <fstream>


bool init(SDL_Window*& window, SDL_Renderer*& renderer, int w, int h) {
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}
		window = SDL_CreateWindow("BitMask Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);

		if (window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL)
			{
				printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

//bool loadMedia(Tile* tiles[], SDL_Rect tileClips[], SDL_Renderer*& renderer, Texture*& tileTexture)
//{
//	//Loading success flag
//	bool success = true;
//
//	//Load tile texture
//	if (!tileTexture->loadFromFile(renderer, "res/pngs/tiles.png"))
//	{
//		printf("Failed to load tile set texture!\n");
//		success = false;
//	}
//
//	//Load tile map
//	if (!setTiles(tiles, tileClips))
//	{
//		printf("Failed to load tile set!\n");
//		success = false;
//	}
//
//	return success;
//}


void close(Tile* tiles[], SDL_Window*& window, SDL_Renderer*& renderer, Texture*& tileTexture)
{
	//Deallocate tiles
	for (int i = 0; i < TOTAL_TILES; ++i)
	{
		if (tiles[i] != NULL)
		{
			delete tiles[i];
			tiles[i] = NULL;
		}
	}

	tileTexture->free();

	//Destroy window	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void close(SDL_Window*& window, SDL_Renderer*& renderer, TileSet*& tileTexture)
{

	tileTexture->free();

	//Destroy window	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}