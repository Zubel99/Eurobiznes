#include "Player.h"
#include "TextureManager.h"
Player::Player(const char* texturesheet, int x, int y, int w, int h, int currField)
{
	currentField = currField;
	dicesMatched = false;
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

void Player::Update()
{
	destR.x = xPos;
	destR.y = yPos;
}

void Player::Render()
{
	SDL_RenderCopy(Game::renderer, texture, &srcR, &destR);//&srcR
}

void Player::SetCurrentField(Field* curField, Field* targetField)//dodac przesuwanie w lewo jesli pole jest juz zajete - po to jest curField
{
	currentField = targetField->getFieldNumber();
	xPos = targetField->getxPos() - targetField->getPlayersOccupying() * 20;
	yPos = targetField->getyPos();
}

void Player::makeMove(Field** fields)
{
	if (daysJailed > 0) { this->daysJailed--; std::cout << "czekasz jeszcze " << this->daysJailed << " dni\n"; return; }

	fields[currentField]->subPlayersOnField(this);//dodaje do wektora
	fields[currentField]->addPlayersOccupying(-1);
	//fields[currentField]->fixPlayerPosition();

	int dice1 = rand() % 6 + 1;
	int dice2 = rand() % 6 + 1;
	int total = dice1 + dice2;
	if (dice1 == dice2) {
		dicesMatched = true;;
		dice1 = rand() % 6 + 1;
		dice2 = rand() % 6 + 1;
		total += dice1 + dice2;
	}
	else
		dicesMatched = false;

	if (dice1 == dice2 && dicesMatched == true) {     //przy wyjsciu z danegoi pola dac fix
		std::cout << "DUBLET = wiezienie\n" << std::endl;  this->daysJailed = 2; dicesMatched = false;
		fields[10]->addPlayersOnField(this); fields[10]->addPlayersOccupying(1); SetCurrentField(fields[currentField], fields[10]);	fields[currentField]->fixPlayerPosition(); return;
	}
	int fieldMod = currentField + total;
	if (fieldMod >= 40) { fieldMod %= 40; money += 400; }

	fields[fieldMod]->addPlayersOnField(this);
	fields[fieldMod]->addPlayersOccupying(1);
	SetCurrentField(fields[currentField], fields[fieldMod]);
	fields[currentField]->fixPlayerPosition();


	if (fieldMod == 30) { std::cout << "IDZIESZ DO WIEZIENIA!\n"; fields[10]->addPlayersOnField(this); 	fields[10]->addPlayersOccupying(1);
	SetCurrentField(fields[currentField], fields[10]);  this->daysJailed = 2;	fields[currentField]->fixPlayerPosition();}

}

void Player::buyField(Field* field)
{
	if (money >= field->getFieldPrice()) { money -= field->getFieldPrice(); field->changeOwner(this); ownedFields.push_back(field);
	std::cout << "KUPUJESZ: " << field->getName() << ", ID = " << field->getFieldNumber() << " ||| KASKA: " << money << std::endl;
	}
	else
	{
		//sprzedac albo zastaw cos
	}
}

void Player::sellField(int id, Field** fields, Player* newOwner)//argument - id posiadlosci
{

	int foundID = hasItem(id);
	if (foundID >= 0) {//tu sprzedaje
		ownedFields[foundID]->changeOwner(newOwner);
		ownedFields.erase(ownedFields.begin() + foundID);
		std::cout << "SPRZEDALES: " << fields[id]->getName() << ", ID = " << fields[id]->getFieldNumber() << " ZA " << fields[id]->getFieldPrice() << " ||| KASKA: " << money << std::endl;
	}
}

int Player::hasItem(int id)//pomocnicza do sprawdzania - sellField
{
	for (int i = 0; i < ownedFields.size(); i++)
	{
		if (ownedFields[i]->getFieldNumber() == id)
			return i;
	}
	return -1;
}


void Player::buyHouse(Field** fields, int id)
{
	if ((fields[id]->getUpgradeable() == true && fields[id]->getOwner() == this && fields[id]->getBuyingLocked() == false) ||
		(fields[id]->getUpgradeable() == true && fields[id]->getOwner() == this && fields[id]->getRebuying() == true))
	{
		if (money >= fields[id]->getHousePrice())
		{
			int minHouses = 5;
			for (int i = 0; i < fields[id]->getCountry().size(); i++)
			{
				if (minHouses > fields[fields[id]->getCountry().at(i)]->getHouses())//min domow w danym kraju
					minHouses = fields[fields[id]->getCountry().at(i)]->getHouses();
			}

			if (fields[id]->getHouses() - minHouses == 0 || fields[id]->getRebuying() == true)//rebyuing-obchodze zasade gethouses-minhouses dla pola ze sprzedanymi domami
			{		
				if (minHouses == 4)//hotele - max 1 na kraj
				{
					bool isHotelPresent = false;
					for (int i = 0; i < fields[id]->getCountry().size(); i++)//sprawdza czy jest hotel juz
						if (fields[fields[id]->getCountry().at(i)]->getHotel() == true)
							isHotelPresent = true;

					if (isHotelPresent == false)
					{
						fields[id]->buyHotel();
						money -= fields[id]->getHousePrice();//cena hotelu = cena domu
						std::cout << "KUPIONO HOTEL\n";
						for (int i = 0; i < fields[id]->getCountry().size(); i++)
						{
							fields[fields[id]->getCountry().at(i)]->setBuyingLocked(true);
							fields[fields[id]->getCountry().at(i)]->setRebuying(false);
						}
					}//jesli jest hotel juz to nic nie robi ez

				}
				else if (fields[id]->getHouses() == minHouses)//domy - max 4 na miasto
				{
					fields[id]->buyHouse();
					money -= fields[id]->getHousePrice();
					std::cout << "KUPIONO DOM\n";
				}
			}

			for (int i = 0; i < fields[id]->getCountry().size(); i++)//wypis ilosci domow i hoteli
			{
				if (fields[fields[id]->getCountry().at(i)]->getHotel() == false)
					std::cout << fields[fields[id]->getCountry().at(i)]->getName() << " = " << fields[fields[id]->getCountry().at(i)]->getHouses() << " houses\n";
				else
					std::cout << fields[fields[id]->getCountry().at(i)]->getName() << " = 1 hotel\n";
			}
		}
		else
		{
			//sprzedaj czy cos
		}
	}
}







void Player::sellHouse(Field** fields, int id)//w wywolaniu funkcji przekazywac dowolne id(nie tylko currentPos)//ustawic rebuying na sell //buying locked na true?
{
	if (fields[id]->getUpgradeable() == true && fields[id]->getOwner() == this)
	{
		if (fields[id]->getHotel() == false)//domy
		{
			if (fields[id]->getHouses() > 0)
			{
				//setrebyuing na true dac :D:D:D
				fields[id]->sellHouse();
				money += fields[id]->getHousePrice() / 2;
				fields[id]->setRebuying(true);
			}

		}
		else//hotel
		{
			fields[id]->sellHotel();
			money += fields[id]->getHousePrice() / 2;
			fields[id]->setRebuying(true);

		}




		for (int i = 0; i < fields[id]->getCountry().size(); i++)//wypis ilosci domow i hoteli
		{
			if (fields[fields[id]->getCountry().at(i)]->getHotel() == false)
				std::cout << fields[fields[id]->getCountry().at(i)]->getName() << " = " << fields[fields[id]->getCountry().at(i)]->getHouses() << " houses\n";
			else
				std::cout << fields[fields[id]->getCountry().at(i)]->getName() << " = 1 hotel\n";
		}
	}
}


void Player::addRenderQueue(ObjectToRender *OTR)
{
	renderQueue.push_back(OTR);
}

void Player::clearRenderQueue()
{
	for (int i = 0; i < renderQueue.size(); i++)
	{
		delete renderQueue.at(i);//chyba git ale nie do konca wiec uwaga
	}
}





















Player::~Player()
{
	SDL_DestroyTexture(texture);
}

void Player::tempPrint(int nr, Field** fields) 
{
	std::cout << "INDEX=" << nr << ", CURRENTFIELD=" << nr << ", NAME=" << fields[nr]->getName() << ", BUYABLE=" << fields[nr]->getBuyable() << ", UPGRADEABLE=" <<
		fields[nr]->getUpgradeable() << ", FIELD PRICE=" << fields[nr]->getFieldPrice() << ", HOUSE PRICE=" << fields[nr]->getHousePrice()
		<< ", FEES=" << fields[nr]->getZeroHF() << "/" << fields[nr]->getOneHF() << "/" << fields[nr]->getTwoHF() << "/" <<
		fields[nr]->getThreeHF() << "/" << fields[nr]->getFourHF() << "/" << fields[nr]->getHotelF() << std::endl;
}

