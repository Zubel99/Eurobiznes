#include "Map.h"

Map::Map(int width, int height)
{
	destR.w = width;
	destR.h = height;

	customWidth = width;//do testow ale mzoe sie przydac trzymanie wymiarow tu zamiast w destR
	customHeight = height;

	texture = IMG_LoadTexture(Game::renderer, "assets/mainMap.png");
}

Map::~Map()
{
	SDL_DestroyTexture(texture);
}

void Map::Render()
{
	SDL_RenderCopy(Game::renderer, texture, NULL, &destR);
}