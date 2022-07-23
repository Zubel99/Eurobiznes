#pragma once
#include "Game.h"
#include <vector>
#include <map>

class Map
{
private:
	int customWidth, customHeight;
	SDL_Rect destR;
	SDL_Texture* texture;


public:
	Map(int width, int height);
	Map();
	~Map();
	void Render();

};