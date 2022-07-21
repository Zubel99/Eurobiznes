#pragma once
#include "Game.h"

class Player;
class Field
{
private:
	int fieldNumber;
	int xPos, yPos;
	SDL_Texture* texture;
	SDL_Rect srcR, destR;
	int zeroHouseFee, oneHouseFee, twoHouseFee, threeHouseFee, fourHouseFee, hotelFee;
	std::string name;
	bool buyable;
	bool upgradeable;
	int fieldPrice;
	int housePrice;
	int houses;
	bool hotel;
	int mortgageAmount;
	bool isMortgage;
	Player* owner;
	std::vector<int> country;
	bool buyingLocked;
	bool rebuying;


public:

	Field(const char* texturesheet, int x, int y, int w, int h, int fieldNumber, std::string name, bool buyable, bool upgradeable, int fieldPrice, int zeroHouseFee, int oneHouseFee,
		int twoHouseFee, int threeHouseFee, int fourHouseFee, int hotelFee, int housePrice, int mortgage);
	~Field();
	void Update();
	void Render();
	int getxPos() { return xPos; }
	int getyPos() { return yPos; }

	void setCountry(std::vector<int> vec);
	std::vector<int> getCountry() { return country; }
	int getFieldNumber() { return fieldNumber; }
	int getFieldPrice() { return fieldPrice; }
	bool getUpgradeable() { return upgradeable; }
	bool getBuyable() { return buyable; }
	std::string getName() { return name; }
	int getZeroHF() { return zeroHouseFee; }
	int getOneHF() { return oneHouseFee; }
	int getTwoHF() { return twoHouseFee; }
	int getThreeHF() { return threeHouseFee; }
	int getFourHF() { return fourHouseFee; }
	int getHotelF() { return hotelFee; }
	int getHousePrice() { return housePrice; }
	int getHouses() { return houses; }
	void buyHouse() { houses += 1;}
	void sellHouse() { houses -= 1; }
	Player* getOwner() { return owner; }
	bool getHotel() { return hotel; }
	void buyHotel() { hotel = true; }
	void sellHotel() { hotel = false; }
	void setBuyingLocked(bool value) { buyingLocked = value; }
	bool getBuyingLocked() { return buyingLocked; }
	bool getRebuying() { return rebuying; }
	void setRebuying(bool value) { rebuying = value; }


	void changeOwner(Player* newOwner) { owner = newOwner; }//potem


};