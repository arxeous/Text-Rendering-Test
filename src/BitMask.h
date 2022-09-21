#pragma once
#include <SDL.h>
#include <stdio.h>
#include <string>

class BitMask
{
public:
	BitMask(int rows, int cols);
	~BitMask();

	void set2DArrayElm(int row, int col, int width, Uint8 value);
	Uint8 get2DArrayElm(int row, int col, int width);

    void renderBitMask2(SDL_Renderer*& renderer, SDL_Color color, int tileSize, int bitRectSize, int offSetX, int offSetY);

    template <typename TwoD>
	void setBitMaskTile3(int mouseX, int mouseY, int tileSize, TwoD& bitmaskValues);
    template <typename TwoD>
    void unSetBitMaskTile3(int mouseX, int mouseY, int tileSize, TwoD& bitmaskValues);

    template <typename TwoD>
    void setBitMaskTile2(int mouseX, int mouseY, int tileSize, int offSetX, int offSetY,  TwoD& bitmaskValues);
    template <typename TwoD>
    void unSetBitMaskTile2(int mouseX, int mouseY, int offSetX, int offSetY, int tileSize, TwoD& bitmaskValues);

    void saveTiles(std::string filePath, size_t resourceSize, int numOfResources);

    void loadTiles(std::string filePath, size_t resourceSize, int numOfResources);

private:
	Uint8* m_Bitmask;
	int m_Rows;
	int m_Cols;
};


template <typename TwoD>
void BitMask::setBitMaskTile3(int mouseX, int mouseY, int tileSize, TwoD& bitmaskValues)
{
    int rowTileClicked = mouseY / tileSize;
    int colTileClicked = mouseX / tileSize;

    if ((rowTileClicked < m_Rows && colTileClicked < m_Cols)) {
        int tileOffsetX = colTileClicked * tileSize;
        int tileOffsetY = rowTileClicked * tileSize;

        int bitCellSize = tileSize * 0.3333;
        int relativeMouseX = mouseX - tileOffsetX;
        int relativeMouseY = mouseY - tileOffsetY;

        int bitClickedRow = relativeMouseY / bitCellSize;
        int bitClickedCol = relativeMouseX / bitCellSize;

        Uint8 clickedBit = bitmaskValues[bitClickedRow][bitClickedCol];

        printf("Element before: %i\n", get2DArrayElm(rowTileClicked, colTileClicked, m_Cols));
        Uint8 currentBitmaskOfClickedTile = get2DArrayElm(rowTileClicked, colTileClicked, m_Cols);

        currentBitmaskOfClickedTile |= clickedBit;

        set2DArrayElm(rowTileClicked, colTileClicked, m_Cols, currentBitmaskOfClickedTile);

        printf("Element after: %i\n\n", get2DArrayElm(rowTileClicked, colTileClicked, m_Cols));


    }
}

template <typename TwoD>
void BitMask::unSetBitMaskTile3(int mouseX, int mouseY, int tileSize, TwoD& bitmaskValues)
{
    int rowTileClicked = mouseY / tileSize;
    int colTileClicked = mouseX / tileSize;

    if ((rowTileClicked < m_Rows && colTileClicked < m_Cols)) {
        int tileOffsetX = colTileClicked * tileSize;
        int tileOffsetY = rowTileClicked * tileSize;

        int bitCellSize = tileSize * 0.3333;
        int relativeMouseX = mouseX - tileOffsetX;
        int relativeMouseY = mouseY - tileOffsetY;

        int bitClickedRow = relativeMouseY / bitCellSize;
        int bitClickedCol = relativeMouseX / bitCellSize;

        Uint8 clickedBit = bitmaskValues[bitClickedRow][bitClickedCol];

        printf("Element before: %i\n", get2DArrayElm(rowTileClicked, colTileClicked, m_Cols));
        Uint8 currentBitmaskOfClickedTile = get2DArrayElm(rowTileClicked, colTileClicked, m_Cols);

        currentBitmaskOfClickedTile ^= clickedBit;

        set2DArrayElm(rowTileClicked, colTileClicked, m_Cols, currentBitmaskOfClickedTile);

        printf("Element after: %i\n\n", get2DArrayElm(rowTileClicked, colTileClicked, m_Cols));


    }
}

template <typename TwoD>
void BitMask::setBitMaskTile2(int mouseX, int mouseY, int offSetX, int offSetY, int tileSize, TwoD& bitmaskValues)
{
    int rowTileClicked = (mouseY - offSetY)/ tileSize;
    int colTileClicked = (mouseX - offSetX)/ tileSize;
    //printf("X Col: %i\nY Row:%i\n\n", colTileClicked, rowTileClicked);      

    if ((rowTileClicked < m_Rows && colTileClicked < m_Cols))
    {
        int tileOffsetX = colTileClicked * tileSize;
        int tileOffsetY = rowTileClicked * tileSize;

        int bitCellSize = tileSize / 2;
        int relativeMouseX = mouseX - tileOffsetX;
        int relativeMouseY = mouseY - tileOffsetY;

        int bitClickedRow = relativeMouseY / bitCellSize;
        int bitClickedCol = relativeMouseX / bitCellSize;

        Uint8 clickedBit = bitmaskValues[bitClickedRow][bitClickedCol];


        Uint8 currentBitmaskOfClickedTile = get2DArrayElm(rowTileClicked, colTileClicked, m_Cols);

        currentBitmaskOfClickedTile |= clickedBit;

        set2DArrayElm(rowTileClicked, colTileClicked, m_Cols, currentBitmaskOfClickedTile);




    }
}

template <typename TwoD>
void BitMask::unSetBitMaskTile2(int mouseX, int mouseY, int offSetX, int offSetY, int tileSize, TwoD& bitmaskValues)
{
    int rowTileClicked = (mouseY - offSetY) / tileSize;
    int colTileClicked = (mouseX - offSetX) / tileSize;
   // printf("X Col: %i\nY Row:%i\n\n", colTileClicked, rowTileClicked);


    if ((rowTileClicked < m_Rows && colTileClicked < m_Cols))
    {
        int tileOffsetX = colTileClicked * tileSize;
        int tileOffsetY = rowTileClicked * tileSize;

        int bitCellSize = tileSize / 2;
        int relativeMouseX = mouseX - tileOffsetX;
        int relativeMouseY = mouseY - tileOffsetY;

        int bitClickedRow = relativeMouseY / bitCellSize;
        int bitClickedCol = relativeMouseX / bitCellSize;

        Uint8 clickedBit = bitmaskValues[bitClickedRow][bitClickedCol];

        Uint8 currentBitmaskOfClickedTile = get2DArrayElm(rowTileClicked, colTileClicked, m_Cols);


        if ((currentBitmaskOfClickedTile & clickedBit) == clickedBit)
        {
            currentBitmaskOfClickedTile ^= clickedBit;
        }

        set2DArrayElm(rowTileClicked, colTileClicked, m_Cols, currentBitmaskOfClickedTile);

    }
}