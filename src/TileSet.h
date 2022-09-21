#pragma once
#include "Texture.h"

class TileSet: public Texture {
public:
	TileSet();
	virtual ~TileSet();

	bool loadFromFile(SDL_Renderer*& renderer, std::string filePath, int cellSize);
	void renderGrid(SDL_Renderer* renderer,  int startingCanvasX,  int startingCanvasY, SDL_Color color);

	Uint32 getTileCellSize();
	Uint32 getRows();
	Uint32 getCols();
private:
	Uint32 m_TileCellSize;
	Uint32 m_Rows;
	Uint32 m_Cols;
};
