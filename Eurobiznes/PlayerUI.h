#pragma once
#include "Game.h"

class Player;
class Field;


class ObjectToRender
{
private:
	SDL_Texture* texture;
	SDL_Surface* surface;
	SDL_Rect destR;
public:
	ObjectToRender(SDL_Surface* _surface, SDL_Texture* _texture, SDL_Rect _destR);
	SDL_Texture* getTexture() { return texture; }
	SDL_Rect getRect() { return destR; }
	SDL_Surface* getSurface() { return surface; }
};



class PlayerUI//przy tworzeniu playerList stworzyc tez to
{
private:
	Player* player;
	Field** fields;
	TTF_Font* font;
	int customWidth, customHeight;

public:
	PlayerUI(Player* _player, Field** _fields, TTF_Font* _font, int width, int height);
	void Update();
	void Render();
};