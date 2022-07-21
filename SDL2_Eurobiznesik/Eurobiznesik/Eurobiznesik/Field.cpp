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



	xPos = x;
	yPos = y;
	texture = TextureManager::LoadTexture(texturesheet);


	srcR.h = 16;//tu wymiary
	srcR.w = 16;
	srcR.x = 0;
	srcR.y = 0;
	destR.w = srcR.w * (w / 400);//tu skaluje obraz
	destR.h = srcR.h * (h / 250);
}

void Field::Update()
{
	destR.x = xPos;
	destR.y = yPos;
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