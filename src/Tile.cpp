#include "Tile.h"

Tile::Tile(int x, int y, int w, int h, int tileType)
{
	m_Box.x = x;
	m_Box.y = y;

    m_Box.w = w;
    m_Box.h = h;

	m_Type = tileType;
}

void Tile::render(SDL_Renderer* renderer,  SDL_Rect& camera, Texture* texture, SDL_Rect tileClip[])
{
    if (checkCollision(camera, m_Box))
    {
        texture->render(renderer, m_Box.x - camera.x, m_Box.y - camera.y, &tileClip[m_Type]);
    }
}

int Tile::getType()
{
	return m_Type;
}

SDL_Rect Tile::getBox()
{
	return m_Box;
}

bool Tile::checkCollision(SDL_Rect a, SDL_Rect b)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    if (bottomA <= topB)
    {
        return false;
    }

    if (topA >= bottomB)
    {
        return false;
    }

    if (rightA <= leftB)
    {
        return false;
    }

    if (leftA >= rightB)
    {
        return false;
    }

    return true;
}
