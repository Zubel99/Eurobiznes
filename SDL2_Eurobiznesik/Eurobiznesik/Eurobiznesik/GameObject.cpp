#include "GameObject.h"
#include "TextureManager.h"
GameObject::GameObject(const char* texturesheet, int x, int y, int w, int h)
{
	xPos = x;
	yPos = y;
	texture = TextureManager::LoadTexture(texturesheet);
	
	srcR.h = 16;//tu wymiary
	srcR.w = 16;
	srcR.x = 0;
	srcR.y = 0;
	destR.w = srcR.w* (w/400);//tu skaluje obraz
	destR.h = srcR.h* (h/250);
}

void GameObject::Update()
{
	destR.x = xPos;
	destR.y = yPos;
}

void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer, texture, &srcR, &destR);
}