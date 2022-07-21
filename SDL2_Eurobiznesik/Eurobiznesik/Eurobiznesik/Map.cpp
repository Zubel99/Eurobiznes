#include "Map.h"

Map::Map(int width, int height)
{
	srcR.x = srcR.y = destR.x = destR.y = 0;
	srcR.w = 1920;
	srcR.h = 1080;//rozmiar oryginalu
	destR.w = width;//(width / 151);// rozmiar koncowy (przeskalowany source)
	destR.h = height;//(height / 101);

	customWidth = width;
	customHeight = height;
}

Map::~Map()
{}

void Map::DrawMap()//czy nie za duzo razy to samo ponawia?
{
	auto temp = TextureManager::LoadTexture("assets/mainMap.png");
	TextureManager::Draw(temp, srcR, destR);
	SDL_DestroyTexture(temp);
}