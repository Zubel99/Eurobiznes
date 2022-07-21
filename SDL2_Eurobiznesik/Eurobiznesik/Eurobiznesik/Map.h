#pragma once
#include "Game.h"
#include <vector>
#include <map>

class Map
{
private:
	int customWidth, customHeight;
	SDL_Rect srcR, destR;


public:
	Map(int width, int height);
	Map();
	~Map();
	void DrawMap();

};