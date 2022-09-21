#include "eventFlagUtil.h"

void getEventFlags(SDL_Event event, bool& quit, bool& saveTiles, bool& loadTiles, bool& setTile, bool& unsetTile, bool& startPan, bool& buttonHold)
{
	//User requests quit
	if (event.type == SDL_QUIT)
	{
		quit = true;
	}
	else if (event.type == SDL_KEYUP)
	{
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			quit = SDL_TRUE;
		}
		else if (event.key.keysym.sym == SDLK_s)
		{
			saveTiles = SDL_TRUE;
		}
		else if (event.key.keysym.sym == SDLK_l)
		{
			loadTiles = SDL_TRUE;
		}
	}
	else if (event.type == SDL_MOUSEBUTTONUP)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			setTile = SDL_FALSE;
		}
		else if (event.button.button == SDL_BUTTON_RIGHT)
		{
			unsetTile = SDL_FALSE;
		}
		else if (event.button.button ==  SDL_BUTTON_MIDDLE)
		{
			buttonHold = SDL_FALSE;
			startPan = SDL_FALSE;
		}

	}
	else if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			setTile = SDL_TRUE;
		}
		else if (event.button.button == SDL_BUTTON_RIGHT)
		{
			unsetTile = SDL_TRUE;
		}
	}
}