#pragma once
#include "Game.h"
#include <vector>
class Field;
class ObjectToRender;

class Player
{
private:
	int currentField;
	bool dicesMatched;
	int xPos;
	int yPos;
	SDL_Texture* texture;
	SDL_Rect srcR, destR;

	int money = 3000;
	int daysJailed = 0;
	std::vector<Field*> ownedFields;
	std::vector<ObjectToRender*> renderQueue;
public:
	void makeMove(Field** fields);
	int GetCurrentField() { return currentField; }
	void SetCurrentField(Field* curField, Field* targetField);
	void setxPos(int newPos) { xPos = newPos; }//temp

	void buyHouse(Field** fields, int id);
	void sellHouse(Field** fields, int id);


	int GetMoney() { return money; }
	int SubMoney(int amount) { money -= amount; return money; }
	int AddMoney(int amount) { money += amount; return money; }

	int GetJailed() { return daysJailed; }
	int AddJailed(int amount) { daysJailed += amount; return daysJailed; }

	void buyField(Field* field);

	void sellField(int id, Field** fields, Player* newOwner);
	int hasItem(int id);
	std::vector<Field*> getFields() { return ownedFields; }


	void clearRenderQueue();
	std::vector<ObjectToRender*>* getRenderQueue(){return &renderQueue;}
	void addRenderQueue(ObjectToRender *OTR);

	Player(const char* texturesheet, int x, int y, int w, int h, int currField);
	~Player();
	void Update();
	void Render();




	void tempPrint(int nr, Field** fields);
};