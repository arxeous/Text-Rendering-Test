#include "Texture.h"

Texture::Texture()
{
	m_Texture = NULL;
	m_Width = 0;
	m_Height = 0;
	m_Pixels = NULL;
	m_Pitch = 0;
}

Texture::~Texture()
{
	free();
}

bool Texture::loadFromFile(SDL_Renderer*& renderer, std::string filePath)
{
	free();
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(filePath.c_str());
	if (loadedSurface == NULL) 
	{
		printf("Image failed to load at path: %s\n SDL IMG Error: %s", filePath.c_str(), IMG_GetError() );
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Texture failed to load from surface at path: %s\n SDL Error: %s", filePath.c_str(), SDL_GetError());
		}
		else
		{
			m_Width = loadedSurface->w;
			m_Height = loadedSurface->h;

		}
		SDL_FreeSurface(loadedSurface);
	}
	m_Texture = newTexture;
	return m_Texture != NULL;
}

bool Texture::loadFontFromFile(SDL_Renderer*& renderer, std::string filePath)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(filePath.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", filePath.c_str(), IMG_GetError());
	}
	else
	{
		//Convert surface to display format
		SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat(loadedSurface, SDL_PIXELFORMAT_RGBA8888, 0);
		if (formattedSurface == NULL)
		{
			printf("Unable to convert loaded surface to display format! %s\n", SDL_GetError());
		}
		else
		{
			//Create blank streamable texture
			newTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h);
			if (newTexture == NULL)
			{
				printf("Unable to create blank texture! SDL Error: %s\n", SDL_GetError());
			}
			else
			{
				//Enable blending on texture
				SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_BLEND);

				//Lock texture for manipulation
				SDL_LockTexture(newTexture, &formattedSurface->clip_rect, &m_Pixels, &m_Pitch);

				//Copy loaded/formatted surface pixels
				memcpy(m_Pixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h);

				//Get image dimensions
				m_Width = formattedSurface->w;
				m_Height = formattedSurface->h;

				//Get pixel data in editable format
				Uint32* pixels = (Uint32*)m_Pixels;
				int pixelCount = (m_Pitch / 4) * m_Height;

				//Map colors				
				Uint32 colorKey = SDL_MapRGB(formattedSurface->format, 0xFF, 0x00, 0xFF);
				Uint32 transparent = SDL_MapRGBA(formattedSurface->format, 0xFF, 0x00, 0xFF, 0x00);

				//Color key pixels
				for (int i = 0; i < pixelCount; ++i)
				{
					if (pixels[i] == colorKey)
					{
						pixels[i] = transparent;
					}
				}

				//Unlock texture to update
				SDL_UnlockTexture(newTexture);
				m_Pixels = NULL;
			}

			//Get rid of old formatted surface
			SDL_FreeSurface(formattedSurface);
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	m_Texture = newTexture;
	return m_Texture != NULL;
}

void Texture::free()
{
	if (m_Texture != NULL) 
	{
		SDL_DestroyTexture(m_Texture);
		m_Texture = NULL;
		m_Width = 0;
		m_Height = 0;
	}
}

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(m_Texture, red, green, blue);
}

void Texture::setBlendMode(SDL_BlendMode blendMode)
{
	SDL_SetTextureBlendMode(m_Texture, blendMode);
}

void Texture::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(m_Texture, alpha);
}

void Texture::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, float scale)
{
	SDL_Rect renderQuad = { x, y, m_Width , m_Height };

	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	renderQuad.w *= scale;
	renderQuad.h *= scale;

	SDL_RenderCopy(renderer, m_Texture, clip, &renderQuad);

}

int Texture::getWidth()
{
	return m_Width;
}

int Texture::getHeight()
{
	return m_Height;
}

bool Texture::lockTexture()
{
	bool success = true;

	//Texture is already locked
	if (m_Pixels != NULL)
	{
		printf("Texture is already locked!\n");
		success = false;
	}
	//Lock texture
	else
	{
		if (SDL_LockTexture(m_Texture, NULL, &m_Pixels, &m_Pitch) != 0)
		{
			printf("Unable to lock texture! %s\n", SDL_GetError());
			success = false;
		}
	}

	return success;
}

bool Texture::unlockTexture()
{
	bool success = true;

	//Texture is not locked
	if (m_Pixels == NULL)
	{
		printf("Texture is not locked!\n");
		success = false;
	}
	//Unlock texture
	else
	{
		SDL_UnlockTexture(m_Texture);
		m_Pixels = NULL;
		m_Pitch = 0;
	}

	return success;
}

void* Texture::getPixels()
{
	return m_Pixels;
}

int Texture::getPitch()
{
	return m_Pitch;
}

Uint32 Texture::getPixel32(unsigned int x, unsigned int y)
{
	//Convert the pixels to 32 bit
	Uint32* pixels = (Uint32*)m_Pixels;

	//Get the pixel requested
	return pixels[(y * (m_Pitch / 4)) + x];
}

