#include "BitMask.h"


BitMask::BitMask(int rows, int cols)
    :m_Rows(rows), m_Cols(cols)
{
	m_Bitmask = (Uint8 *)malloc(sizeof(Uint8) * rows * cols);
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			set2DArrayElm(row, col, cols, 0x00);
		}
	}
}

BitMask::~BitMask()
{
	delete m_Bitmask;
	m_Bitmask = nullptr;
}


void BitMask::set2DArrayElm(int row, int col, int width, Uint8 value)
{
	m_Bitmask[row * width + col] = value;
}

Uint8 BitMask::get2DArrayElm(int row, int col, int width)
{
	return m_Bitmask[row * width + col];
}

void BitMask::renderBitMask2(SDL_Renderer*& renderer, SDL_Color color, int tileSize, int bitRectSize, int offSetX, int offSetY)
{
	SDL_Rect visualBitmaskRect;
	visualBitmaskRect.w = bitRectSize;
	visualBitmaskRect.h = bitRectSize;
	Uint8 currentTileBitMask;
	int tileNum = 2;
	for (int row = 0; row < m_Rows; row++)
	{
		for (int col = 0; col < m_Cols; col++)
		{
			int rectXPoint =  (col * tileSize) + offSetX;
			int rectYPoint = (row * tileSize) + offSetY;

			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
			Uint8 rightMostOne = 0x01;
			Uint8 value = 0x00;
			currentTileBitMask = get2DArrayElm(row, col, m_Cols);
			
			for (int i = 0; i < 4; i++)
			{
				value = rightMostOne << i;

				if ((currentTileBitMask & value) == value)
				{

					if (i >= 0 && i < tileNum) 
					{
						visualBitmaskRect.x = rectXPoint + ((i % tileNum) * bitRectSize);
						visualBitmaskRect.y = rectYPoint;	
					}
					else if (i >= tileNum && i < tileNum * 2)
					{
						visualBitmaskRect.x = rectXPoint + ((i % tileNum) * bitRectSize);
						visualBitmaskRect.y = rectYPoint + bitRectSize;
					}
					SDL_RenderFillRect(renderer, &visualBitmaskRect);
				}
			}

		}
	}
}

void BitMask::saveTiles(std::string filePath, size_t resourceSize, int numOfResources) 
{
	const char* writeModeBinary = "wb";
	SDL_RWops* file = SDL_RWFromFile(filePath.c_str(), writeModeBinary);

	if (file != NULL)
	{
		SDL_RWwrite(file, m_Bitmask, resourceSize, numOfResources);
		SDL_RWclose(file);
		printf("File saved to %s", filePath.c_str());
	}
}

void BitMask::loadTiles(std::string filePath, size_t resourceSize, int numOfResources)
{
	const char* writeModeBinary = "rb";
	SDL_RWops* file = SDL_RWFromFile(filePath.c_str(), writeModeBinary);

	if (file != NULL)
	{
		SDL_RWread(file, m_Bitmask, resourceSize, numOfResources);
		SDL_RWclose(file);
		printf("File loaded from %s", filePath.c_str());
	}
}
