#include "TileSet.h"

TileSet::TileSet()
	: Texture(), m_Rows(0), m_Cols(0), m_TileCellSize(0)
{
}

TileSet::~TileSet()
{
}

bool TileSet::loadFromFile(SDL_Renderer*& renderer, std::string filePath, int cellSize)
{
	bool success;
	m_TileCellSize = cellSize;
	success = Texture::loadFromFile(renderer, filePath);
	m_Cols = m_Width / m_TileCellSize;
	m_Rows = m_Height / m_TileCellSize;

	return success;
}

void TileSet::renderGrid(SDL_Renderer* renderer, int startingCanvasX, int startingCanvasY, SDL_Color color)
{
	int endingCanvasX = startingCanvasX + (m_TileCellSize * m_Cols);
	int endingCanvasY = startingCanvasY + (m_TileCellSize * m_Rows);
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	for (int x = 0; x <= m_Cols; ++x) 
	{
		SDL_RenderDrawLine(renderer, (x * m_TileCellSize + startingCanvasX), startingCanvasY, (x * m_TileCellSize + startingCanvasX), endingCanvasY);
	}
	for (int y = 0; y <= m_Rows; ++y)
	{
		SDL_RenderDrawLine(renderer, startingCanvasX, (y * m_TileCellSize + startingCanvasY), endingCanvasX, (y * m_TileCellSize + startingCanvasY));
	}
}

Uint32 TileSet::getTileCellSize()
{
	return m_TileCellSize;
}

Uint32 TileSet::getRows()
{
	return m_Rows;
}

Uint32 TileSet::getCols()
{
	return m_Cols;
}
