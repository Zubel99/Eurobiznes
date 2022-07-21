#pragma once
#include "Game.h"
class GameObject
{
private:
	int xPos;
	int yPos;
	SDL_Texture* texture;
	SDL_Rect srcR, destR;

public:
	GameObject(const char* texturesheet, int x, int y, int w, int h);
	~GameObject();
	void Update();
	void Render();
};