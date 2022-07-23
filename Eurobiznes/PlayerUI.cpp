#include "PlayerUI.h"

ObjectToRender::ObjectToRender(SDL_Surface* _surface, SDL_Texture* _texture, SDL_Rect _destR)//konstruktor do tekstur
{
	texture = _texture;
	destR = _destR;
	surface = _surface;
}



PlayerUI::PlayerUI(Player* _player, Field** _fields, TTF_Font* _font,int width, int height)
{
	player = _player;
	fields = _fields;
	font = _font;
	customWidth = width;
	customHeight = height;
}

void PlayerUI::Update()//dodaje do wektora obiektow do wyrenderowania
{
	std::string combinedString = "MONEY: " + std::to_string(player->GetMoney());
	SDL_Surface* tempSurface = TTF_RenderUTF8_Solid(font, combinedString.c_str(), {0,0,0});
	SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	//free(tempSurface);
	SDL_Rect destR;
	destR.x = float(customWidth) * 0.8;
	destR.y = float(customHeight) * 0.1;
	destR.w = 200;
	destR.h = 50;
	ObjectToRender* tempObject = new ObjectToRender(tempSurface, tempTexture, destR);
	player->addRenderQueue(tempObject);//dodawanie do main vectora - print
}

void PlayerUI::Render()
{
	/*SDL_Surface* tempSurface = TTF_RenderText_Solid(font, std::to_string(player->GetMoney()).c_str(), {0,0,0});//TTF_RenderUTF8_Solid
	SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	SDL_Rect tempRect;
	tempRect.x = 0;
	tempRect.y = 0;
	tempRect.w = 300;
	tempRect.h = 100;

	SDL_RenderCopy(Game::renderer, tempTexture, NULL, NULL);
	SDL_DestroyTexture(tempTexture);*/

	std::vector<ObjectToRender*>* vec = player->getRenderQueue();

	for (int i = 0; i < vec->size(); i++)
	{
		SDL_Rect tempRect = vec->at(i)->getRect();//musi byc lvalue
		SDL_RenderCopy(Game::renderer, vec->at(i)->getTexture(), NULL, &tempRect);//dziala dobrze ale printuje 4 osoby na raz wiec sie buguje
		SDL_FreeSurface(vec->at(i)->getSurface());
		SDL_DestroyTexture(vec->at(i)->getTexture());
	}
	for (int i = 0; i < vec->size(); i++)
		delete vec->at(i);

	vec->clear();
	//std::cout << "POMIAR PO = ";
	//std::cout << vec->size() << std::endl;
}

