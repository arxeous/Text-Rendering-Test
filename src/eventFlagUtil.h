#pragma once
#include "SDL.h"

void getEventFlags(SDL_Event event, bool& quit, bool& saveTiles, bool& loadTiles, bool& setTile, bool& unsetTile,bool& startPan, bool& buttonHold);