#include "Font.h"
#include "Timer.h"

Font::Font()
	:m_FontTexture(NULL), m_NewLine(0), m_Space(0)
{
}

bool Font::buildFont(Texture* fontTexture)
{
	bool success = true;

	//Lock pixels for access
	if (!fontTexture->lockTexture())
	{
		printf("Unable to lock bitmap font texture!\n");
		success = false;
	}
	else
	{
		//Set the background color
		Uint32 bgColor = fontTexture->getPixel32(0, 0);

		//Set the cell dimensions
		int cellW = fontTexture->getWidth() / 16;
		int cellH = fontTexture->getHeight() / 16;

		//New line variables
		int top = cellH;
		int baseA = cellH;

		//The current character we're setting
		int currentChar = 0;

		//Go through the cell rows
		for (int rows = 0; rows < 16; ++rows)
		{
			//Go through the cell columns
			for (int cols = 0; cols < 16; ++cols)
			{
				//Set the character offset
				m_Chars[currentChar].x = cellW * cols;
				m_Chars[currentChar].y = cellH * rows;
				 
				//Set the dimensions of the character
				m_Chars[currentChar].w = cellW;
				m_Chars[currentChar].h = cellH;

				//Find Left Side
				//Go through pixel columns
				for (int pCol = 0; pCol < cellW; ++pCol)
				{
					//Go through pixel rows
					for (int pRow = 0; pRow < cellH; ++pRow)
					{
						//Get the pixel offsets
						int pX = (cellW * cols) + pCol;
						int pY = (cellH * rows) + pRow;

						//If a non colorkey pixel is found
						if (fontTexture->getPixel32(pX, pY) != bgColor)
						{
							//Set the x offset
							m_Chars[currentChar].x = pX;

							//Break the loops
							pCol = cellW;
							pRow = cellH;
						}
					}
				}

				//Find Right Side
				//Go through pixel columns
				for (int pColW = cellW - 1; pColW >= 0; --pColW)
				{
					//Go through pixel rows
					for (int pRowW = 0; pRowW < cellH; ++pRowW)
					{
						//Get the pixel offsets
						int pX = (cellW * cols) + pColW;
						int pY = (cellH * rows) + pRowW;

						//If a non colorkey pixel is found
						if (fontTexture->getPixel32(pX, pY) != bgColor)
						{
							//Set the width
							m_Chars[currentChar].w = (pX - m_Chars[currentChar].x) + 1;

							//Break the loops
							pColW = -1;
							pRowW = cellH;
						}
					}
				}

				//Find Top
				//Go through pixel rows
				for (int pRow = 0; pRow < cellH; ++pRow)
				{
					//Go through pixel columns
					for (int pCol = 0; pCol < cellW; ++pCol)
					{
						//Get the pixel offsets
						int pX = (cellW * cols) + pCol;
						int pY = (cellH * rows) + pRow;

						//If a non colorkey pixel is found
						if (fontTexture->getPixel32(pX, pY) != bgColor)
						{
							//If new top is found
							if (pRow < top)
							{
								top = pRow;
							}

							//Break the loops
							pCol = cellW;
							pRow = cellH;
						}
					}
				}

				//Find Bottom of A
				if (currentChar == 'A')
				{
					//Go through pixel rows
					for (int pRow = cellH - 1; pRow >= 0; --pRow)
					{
						//Go through pixel columns
						for (int pCol = 0; pCol < cellW; ++pCol)
						{
							//Get the pixel offsets
							int pX = (cellW * cols) + pCol;
							int pY = (cellH * rows) + pRow;

							//If a non colorkey pixel is found
							if (fontTexture->getPixel32(pX, pY) != bgColor)
							{
								//Bottom of a is found
								baseA = pRow;

								//Break the loops
								pCol = cellW;
								pRow = -1;
							}
						}
					}
				}

				//Go to the next character
				++currentChar;
			}
		}

		//Calculate space
		m_Space = cellW / 2;

		//Calculate new line
		m_NewLine = baseA - top;

		//Lop off excess top pixels
		for (int i = 0; i < 256; ++i)
		{
			m_Chars[i].y += top;
			m_Chars[i].h -= top;
		}

		fontTexture->unlockTexture();
		m_FontTexture= fontTexture;
	}

	return success;
}

void Font::renderText(SDL_Renderer* renderer, int x, int y, std::string text, float scale)
{
	//If the font has been built
	float period = SDL_GetTicks64() / 100.0f;
	if (m_FontTexture != NULL)
	{
		//Temp offsets
		int curX = x, curY = y;
		int offsetY = y;
		int waveHeight = 10;

		//Go through the text
		for (int i = 0; i < text.length(); ++i)
		{
			//If the current character is a space
			if (text[i] == ' ')
			{
				//Move over
				curX += m_Space ;
			}
			//If the current character is a newline
			else if (text[i] == '\n')
			{
				//Move down
				curY += m_NewLine;

				//Move back
				curX = x;
			}
			else
			{
				//Get the ASCII value of the character
				int ascii = (unsigned char)text[i];


				// Sin wave text functionality is done here.
				curY = waveHeight * sin(period + (float)i) + offsetY;
				//Show the character
				m_FontTexture->render(renderer, curX, curY, &m_Chars[ascii], scale);

				//Move over the width of the character with one pixel of padding
				curX += (m_Chars[ascii].w * scale) + 1;
			}
		}
	}
}
