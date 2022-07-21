#include "Game.h"

Game* game = nullptr;
int main()
{
	//srand(time(NULL));
	//fpsy
	const int fps = 60;
	const int frameDelay = 1000 / fps;
	unsigned long long frameStart;
	int frameTime;
	//
	game = new Game();
	game->init("SuperGiera", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1500, 1000, false);
	while (game->running())
	{
		frameStart = SDL_GetTicks();//licz fps
		game->handleEvents();
		game->update();
		game->render();
		frameTime = SDL_GetTicks() - frameStart;//skoncz liczyc i policz srednia ilosc na cykl
		if (frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);
	}

	game->clean();
	return 0;
}