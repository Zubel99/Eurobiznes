#include "Game.h"
#include <vector>
//std::vector<Field*> test;


Field* fields[40];
Player* playerList[4];//ilosc playerow
PlayerUI* playerUI[4];


const char* playerTextures[6] = { "assets/player1.png", "assets/player2.png", "assets/player3.png", "assets/player4.png", "assets/player5.png", "assets/player6.png" };//max 6 playerow
SDL_Renderer* Game::renderer = nullptr; //?
Map* map = nullptr;

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen)//przygotowuje srodowisko, tworzy okno, tworzy renderer
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		int flag = 0;
		if (fullscreen) 
			flag = SDL_WINDOW_FULLSCREEN_DESKTOP;

		std::cout << "Initial load - works!\n";
		window = SDL_CreateWindow(title, xPos, yPos, width, height, flag);
		if (window)
			std::cout << "Window - works!\n";
		else { std::cout << "Could not load window!\n"; exit(1); }

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer - works!\n";
		}
		else { std::cout << "Could not load renderer!\n"; exit(1); }
		isRunning = true;

		TTF_Init();//textfont
		tempFont = TTF_OpenFont(font.c_str(), 32);
		if (tempFont == nullptr)
		{
			std::cout << "Could not load font!\n";
			exit(1);
		}
	}
	else
		isRunning = false;

	int w, h;
	if (fullscreen)
	{
		SDL_GetRendererOutputSize(renderer, &w, &h);
	}
	else
	{
		w = width;
		h = height;
	}
	int spawnX = w * 0.63; //1210
	int spawnY = h * 0.898;//970

	for (int i = 0; i < sizeof(playerList) / sizeof(playerList[0]); i++)
	{
		playerList[i] = new Player(playerTextures[i], spawnX, spawnY, w, h,0);
		spawnX -= width/64;
	}
	map = new Map(w, h);
	std::cout << w << "x" << h << std::endl;//dla testu

	int tempX[40] = {
		1190,1030,930,830,730,630,530,430,330,230,110,/**/65,65,65,65,65,65,65,65,65,110,      /**/ 230,330,430,530,630,730,830,930,1030,1190,/**/1195,1195,1195,1195,1195,1195,1195,1195,1195 };
	int tempY[40] = { 
		965,980,980,980,980,980,980,980,980,980,965,/**/845,761,676,592,507,423,338,254,169,55,/**/35,35,35,35,35,35,35,35,35,55,             /**/169,254,338,423,507,592,676,761,845};
	std::map<int, std::string> fieldName{
		{0,"Start"},
		{1,"Grecja - Saloniki"},
		{2,"Szansa (karta niebieska)"},
		{3,"Grecja - Ateny"},
		{4,"Parking strzezony (do zaplaty 400$)"},
		{5,"Koleje polodniowe"},
		{6,"Wlochy - Neapol"},
		{7,"Szansa (karta czerwona)"},
		{8,"Wlochy - Mediolan"},
		{9,"Wlochy - Rzym"},
		{10,"Wiezienie / Dla odwiedzajacych"},
		{11,"Hiszpania - Barcelona"},
		{12,"Elektrownia atomowa"},
		{13,"Hiszpania - Sewilla"},
		{14,"Hiszpania - Madryt"},
		{15,"Koleje zachodnie"},
		{16,"Anglia - Liverpool"},
		{17,"Szansa (karta niebieska)"},
		{18,"Anglia - Glasgow"},
		{19,"Anglia - Londyn"},
		{20,"Darmowy parking"},
		{21,"Benelux - Rotterdam"},
		{22,"Szansa (karta czerwona)"},
		{23,"Benelux - Bruksela"},
		{24,"Benelux - Amsterdam"},
		{25,"Koleje polnocne"},
		{26,"Szwecja - Malmo"},
		{27,"Szwecja - Goteborg"},
		{28,"Siec wodociagow"},
		{29,"Szwecja - Sztokholm"},
		{30,"Idziesz do wiezienia!"},
		{31,"RFN - Frankfurt"},
		{32, "RFN - Kolonia"},
		{33,"Szansa (karta niebieska)"},
		{34,"RFN - Bonn"},
		{35,"Koleje wschodnie"},
		{36,"Szansa (karta czerwona)"},
		{37,"Austria - Innsbruck"},
		{38,"Podatek od wzbogacenia (do zaplaty 200$)"},
		{39,"Austria - Wieden"}
	};
	std::map<int, bool> fieldBuyable{
		{0,false},
		{1,true},
		{2,false},
		{3,true},
		{4,false},
		{5,true},
		{6,true},
		{7,false},
		{8,true},
		{9,true},
		{10,false},
		{11,true},
		{12,true},
		{13,true},
		{14,true},
		{15,true},
		{16,true},
		{17,false},
		{18,true},
		{19,true},
		{20,false},
		{21,true},
		{22,false},
		{23,true},
		{24,true},
		{25,true},
		{26,true},
		{27,true},
		{28,true},
		{29,true},
		{30,false},
		{31,true},
		{32,true},
		{33,false},
		{34,true},
		{35,true},
		{36,false},
		{37,true},
		{38,false},
		{39,true}
	};
	std::map<int, bool> fieldUpgradeable{
		{0,false},
		{1,true},
		{2,false},
		{3,true},
		{4,false},
		{5,false},
		{6,true},
		{7,false},
		{8,true},
		{9,true},
		{10,false},
		{11,true},
		{12,false},
		{13,true},
		{14,true},
		{15,false},
		{16,true},
		{17,false},
		{18,true},
		{19,true},
		{20,false},
		{21,true},
		{22,false},
		{23,true},
		{24,true},
		{25,false},
		{26,true},
		{27,true},
		{28,false},
		{29,true},
		{30,false},
		{31,true},
		{32,true},
		{33,false},
		{34,true},
		{35,false},
		{36,false},
		{37,true},
		{38,false},
		{39,true}
	};
	std::map<int, int> fieldPrice{
		{0,0},
		{1,120},
		{2,0},
		{3,120},
		{4,400},
		{5,400},
		{6,200},
		{7,0},
		{8,200},
		{9,240},
		{10,0},
		{11,280},
		{12,300},
		{13,280},
		{14,320},
		{15,400},
		{16,360},
		{17,0},
		{18,360},
		{19,400},
		{20,0},
		{21,440},
		{22,0},
		{23,440},
		{24,480},
		{25,400},
		{26,520},
		{27,520},
		{28,300},
		{29,560},
		{30,0},
		{31,600},
		{32,600},
		{33,0},
		{34,640},
		{35,400},
		{36,0},
		{37,700},
		{38,200},
		{39,800}
	};
	std::map<int, int> zeroHouseFee{
		{0,0},
		{1,10},
		{2,0},
		{3,10},
		{4,0},
		{5,0},
		{6,15},
		{7,0},
		{8,15},
		{9,20},
		{10,0},
		{11,20},
		{12,0},
		{13,20},
		{14,25},
		{15,0},
		{16,30},
		{17,0},
		{18,30},
		{19,35},
		{20,0},
		{21,35},
		{22,0},
		{23,35},
		{24,40},
		{25,0},
		{26,45},
		{27,45},
		{28,0},
		{29,50},
		{30,0},
		{31,55},
		{32,55},
		{33,0},
		{34,60},
		{35,0},
		{36,0},
		{37,70},
		{38,0},
		{39,100}
	};
	std::map<int, int> oneHouseFee{
		{0,0},
		{1,40},
		{2,0},
		{3,40},
		{4,0},
		{5,0},
		{6,60},
		{7,0},
		{8,60},
		{9,80},
		{10,0},
		{11,100},
		{12,0},
		{13,100},
		{14,120},
		{15,0},
		{16,140},
		{17,0},
		{18,140},
		{19,160},
		{20,0},
		{21,180},
		{22,0},
		{23,180},
		{24,200},
		{25,0},
		{26,220},
		{27,220},
		{28,0},
		{29,240},
		{30,0},
		{31,260},
		{32,260},
		{33,0},
		{34,300},
		{35,0},
		{36,0},
		{37,350},
		{38,0},
		{39,400}
	};
	std::map<int, int> twoHouseFee{
		{0,0},
		{1,120},
		{2,0},
		{3,120},
		{4,0},
		{5,0},
		{6,180},
		{7,0},
		{8,180},
		{9,200},
		{10,0},
		{11,300},
		{12,0},
		{13,300},
		{14,360},
		{15,0},
		{16,400},
		{17,0},
		{18,400},
		{19,440},
		{20,0},
		{21,500},
		{22,0},
		{23,500},
		{24,600},
		{25,0},
		{26,660},
		{27,660},
		{28,0},
		{29,720},
		{30,0},
		{31,780},
		{32,780},
		{33,0},
		{34,900},
		{35,0},
		{36,0},
		{37,1000},
		{38,0},
		{39,1200}
	};
	std::map<int, int> threeHouseFee{
		{0,0},
		{1,360},
		{2,0},
		{3,360},
		{4,0},
		{5,0},
		{6,540},
		{7,0},
		{8,540},
		{9,600},
		{10,0},
		{11,900},
		{12,0},
		{13,900},
		{14,1000},
		{15,0},
		{16,1100},
		{17,0},
		{18,1100},
		{19,1200},
		{20,0},
		{21,1400},
		{22,0},
		{23,1400},
		{24,1500},
		{25,0},
		{26,1600},
		{27,1600},
		{28,0},
		{29,1700},
		{30,0},
		{31,1900},
		{32,1900},
		{33,0},
		{34,2000},
		{35,0},
		{36,0},
		{37,2200},
		{38,0},
		{39,2800}
	};
	std::map<int, int> fourHouseFee{
		{0,0},
		{1,640},
		{2,0},
		{3,640},
		{4,0},
		{5,0},
		{6,800},
		{7,0},
		{8,800},
		{9,900},
		{10,0},
		{11,1250},
		{12,0},
		{13,1250},
		{14,1400},
		{15,0},
		{16,1500},
		{17,0},
		{18,1500},
		{19,1600},
		{20,0},
		{21,1750},
		{22,0},
		{23,1750},
		{24,1850},
		{25,0},
		{26,1950},
		{27,1950},
		{28,0},
		{29,2050},
		{30,0},
		{31,2200},
		{32,2200},
		{33,0},
		{34,2400},
		{35,0},
		{36,0},
		{37,2600},
		{38,0},
		{39,3400}
	};
	std::map<int, int> hotelFee{
		{0,0},
		{1,900},
		{2,0},
		{3,900},
		{4,0},
		{5,0},
		{6,1100},
		{7,0},
		{8,1100},
		{9,1200},
		{10,0},
		{11,1500},
		{12,0},
		{13,1500},
		{14,1800},
		{15,0},
		{16,1900},
		{17,0},
		{18,1900},
		{19,2000},
		{20,0},
		{21,2100},
		{22,0},
		{23,2100},
		{24,2200},
		{25,0},
		{26,2300},
		{27,2300},
		{28,0},
		{29,2400},
		{30,0},
		{31,2550},
		{32,2550},
		{33,0},
		{34,2800},
		{35,0},
		{36,0},
		{37,3000},
		{38,0},
		{39,4000}
	};
	std::map<int, int> housePrice{
	{0,0},
	{1,100},
	{2,0},
	{3,100},
	{4,0},
	{5,0},
	{6,100},
	{7,0},
	{8,100},
	{9,100},
	{10,0},
	{11,200},
	{12,0},
	{13,200},
	{14,200},
	{15,0},
	{16,200},
	{17,0},
	{18,200},
	{19,200},
	{20,0},
	{21,300},
	{22,0},
	{23,300},
	{24,300},
	{25,0},
	{26,300},
	{27,300},
	{28,0},
	{29,300},
	{30,0},
	{31,400},
	{32,400},
	{33,0},
	{34,400},
	{35,0},
	{36,0},
	{37,400},
	{38,0},
	{39,400}
	};
	std::map<int, int> mortgage{
		{0,0},
		{1,60},
		{2,0},
		{3,60},
		{4,0},
		{5,200},
		{6,100},
		{7,0},
		{8,100},
		{9,120},
		{10,0},
		{11,140},
		{12,150},
		{13,140},
		{14,160},
		{15,200},
		{16,180},
		{17,0},
		{18,180},
		{19,200},
		{20,0},
		{21,220},
		{22,0},
		{23,220},
		{24,240},
		{25,200},
		{26,260},
		{27,260},
		{28,150},
		{29,280},
		{30,0},
		{31,300},
		{32,300},
		{33,0},
		{34,320},
		{35,200},
		{36,0},
		{37,350},
		{38,0},
		{39,400}
	};
	std::vector<int> indexesGRECJA = { 1,3 };
	std::vector<int> indexesWLOCHY = { 6,8,9 };
	std::vector<int> indexesHISZPANIA = { 11,13,14 };
	std::vector<int> indexesANGLIA = { 16,18,19 };
	std::vector<int> indexesBENELUX = { 21,23,24 };
	std::vector<int> indexesSZWECJA = { 26,27,29 };
	std::vector<int> indexesRFN = {31,32,34 };
	std::vector<int> indexesAUSTRIA = { 37,39};

	for (int i = 0; i < 40; i++)
	{
		fields[i] = new Field("assets/player1.png", tempX[i]*(float(w) / 1920), tempY[i]*(float(h)/1080), w, h, i, fieldName[i],fieldBuyable[i],fieldUpgradeable[i],fieldPrice[i],
			zeroHouseFee[i],oneHouseFee[i],twoHouseFee[i],threeHouseFee[i],fourHouseFee[i],hotelFee[i], housePrice[i], mortgage[i]);
		{
			if (i < 5)
				fields[i]->setCountry(indexesGRECJA);
			else if (i < 10)
				fields[i]->setCountry(indexesWLOCHY);
			else if (i < 15)
				fields[i]->setCountry(indexesHISZPANIA);
			else if (i < 20)
				fields[i]->setCountry(indexesANGLIA);
			else if (i < 25)
				fields[i]->setCountry(indexesBENELUX);
			else if (i < 30)
				fields[i]->setCountry(indexesSZWECJA);
			else if (i < 35)
				fields[i]->setCountry(indexesRFN);
			else if (i < 40)
				fields[i]->setCountry(indexesAUSTRIA);
		}
	}
	fields[0]->addPlayersOccupying(4);

	for (int i = 0; i < sizeof(playerList) / sizeof(playerList[0]); i++)//playerui do renderowania ui pepege
	{
		playerUI[i] = new PlayerUI(playerList[i], fields, tempFont, w, h);
		fields[0]->addPlayersOnField(playerList[i]);
	}
}





void Game::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN: {//SDL_MOUSEBUTTONDOWN
			if (event.key.keysym.sym == SDLK_r)
			{
			playerList[0]->makeMove(fields);
			//playerList[0]->tempPrint(playerList[0]->GetCurrentField(),fields);
			}
			else if (event.key.keysym.sym == SDLK_t)
			{
				playerList[1]->makeMove(fields);
				//playerList[1]->tempPrint(playerList[1]->GetCurrentField(), fields);
			}
			else if (event.key.keysym.sym == SDLK_y)
			{
				playerList[2]->makeMove(fields);
				//playerList[2]->tempPrint(playerList[2]->GetCurrentField(), fields);
			}
			else if (event.key.keysym.sym == SDLK_b && fields[playerList[0]->GetCurrentField()]->getBuyable() == true && fields[playerList[0]->GetCurrentField()]->getOwner() == nullptr)
			{
				playerList[0]->buyField(fields[playerList[0]->GetCurrentField()]);//zrobic
			}
			else if (event.key.keysym.sym == SDLK_s)
			{
				playerList[0]->sellField(playerList[0]->GetCurrentField(), fields, nullptr);//nullptr zamienic na nowego gracza
			}
			else if (event.key.keysym.sym == SDLK_f)
			{
				for (auto field : playerList[0]->getFields()) { std::cout << field->getName() << ", ID = " << field->getFieldNumber() << std::endl; }
			}
			else if (event.key.keysym.sym == SDLK_o)
			{
				playerList[0]->buyHouse(fields, playerList[0]->GetCurrentField());
			}
			else if (event.key.keysym.sym == SDLK_p)
			{
				playerList[0]->sellHouse(fields, playerList[0]->GetCurrentField());
			}

			else if (event.key.keysym.sym == SDLK_x)
			{
				for (auto index : fields) {
					for (int i = 0; i < index->getCountry().size(); i++)
					{
						std::cout << index->getName() << ", FRIEND CITIES = " << index->getCountry().at(i) << std::endl;
					}
					std::cout << std::endl;
				}
			}
			else if (event.key.keysym.sym == SDLK_m)
			{
				std::cout << playerList[0]->GetMoney() << std::endl;
			}
			break;}

		case SDL_MOUSEBUTTONDOWN:
			std::cout << "ROZMIAR WEKTORA(ILOSC KUPIONYCH POSIADLOSCI) = " << playerList[0]->getFields().size() << std::endl;
			break;

		case SDL_QUIT:
			isRunning = false;
			break;

		default:
			break;
		}
	}
}

void Game::update()
{
	for (auto player : playerList)
		player->Update();
	for (auto player : playerUI)
		player->Update();
}


void Game::render()
{
	SDL_RenderClear(renderer);
	//tu dodaje rzeczy do render
	map->Render();

	for (auto player : playerList)
		player->Render();
	for (auto player : playerUI)
		player->Render();


	SDL_RenderPresent(renderer);//wyrenderowanie ich
}






void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	for (int i = 0; i < sizeof(playerList)/sizeof(playerList[0]); i++)
		delete playerList[i];
	for (int i = 0; i < sizeof(fields) / sizeof(fields[0]); i++)
		delete fields[i];
	delete map;
	SDL_QUIT;
	std::cout << "Koniec gry - wyczyszczono okno i renderer\n";
}