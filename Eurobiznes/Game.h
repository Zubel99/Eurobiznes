#pragma once//guard1
#ifndef Game_h//guard2
#define Game_h
#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED // bez tego sie wywala bo tak XD

#include <iostream> //wszystkie includy do maina potrzebne
#include <stdio.h>
#include "SDL2/SDL.h"
#include <string>
#include "SDL2_image/SDL_image.h"
#include "TextureManager.h"
#include "Map.h"
#include "GameObject.h"
#include "Player.h"
#include "Field.h"
#include <vector>
#include <map>
#include <algorithm>
#include <SDL2_ttf/SDL_ttf.h>
#include "PlayerUI.h"

class Game
{
private:
	bool isRunning = false;
	SDL_Window* window;
	std::string font = "./fonts/Rubik-Regular.ttf";


public:
	TTF_Font* tempFont;//error handling
	static SDL_Renderer* renderer; //static global renderer
	Game();
	~Game();
	void init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; }
};



#endif //SDL_MAIN_HANDLED
#endif //Game.h