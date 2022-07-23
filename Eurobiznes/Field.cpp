#include "Field.h"
#include "TextureManager.h"
Field::Field(const char* texturesheet, int x, int y, int w, int h, int number, std::string nam, bool buyabl, bool upgradeabl, int fieldPric,
	int zeroHF, int oneHF, int twoHF, int threeHF, int fourHF, int hF, int housePric, int mortgage)
{
	fieldNumber = number;
	name = nam;
	buyable = buyabl;
	upgradeable = upgradeabl;
	fieldPrice = fieldPric;
	zeroHouseFee = zeroHF;
	oneHouseFee = oneHF;
	twoHouseFee = twoHF;
	threeHouseFee = threeHF;
	fourHouseFee = fourHF;
	hotelFee = hF;
	housePrice = housePric;
	houses = 0;
	hotel = false;
	owner = nullptr;
	mortgageAmount = mortgage;
	isMortgage = false;
	buyingLocked = false;
	rebuying = false;
	playersOccupying = 0;



	xPos = x;
	yPos = y;
	texture = IMG_LoadTexture(Game::renderer, texturesheet);


	srcR.h = 16;//tu wymiary
	srcR.w = 16;
	srcR.x = 0;
	srcR.y = 0;
	destR.w = srcR.w * (w / 400);//tu skaluje obraz
	destR.h = srcR.h * (h / 250);
}

void Field::Render()
{
	SDL_RenderCopy(Game::renderer, texture, &srcR, &destR);
}

void Field::setCountry(std::vector<int> vec)
{
	for (auto index : vec)
		country.push_back(index);
}

void Field::fixPlayerPosition()
{
	for (int i = 0; i < playersOnField.size(); i++)
	{
		std::cout << "ILOSC GRACZY NA POLU = " << i+1 << std::endl;
		playersOnField.at(i)->setxPos(xPos - 20 * i);//wiecej na minus
	}
}

void Field::subPlayersOnField(Player* newPlayer)
{
	playersOnField.erase(std::remove(playersOnField.begin(), playersOnField.end(), newPlayer), playersOnField.end());
}


Field::~Field()
{
	SDL_DestroyTexture(texture);
}