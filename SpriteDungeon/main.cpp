#define SDL_MAIN_HANDLED
#include <conio.h>
#include "SDL.h"
#include "GameCore.h"

using namespace SpriteDungeon;

int main() {

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* pWindow = SDL_CreateWindow("The Marvelous Misadventure of Pirate Boy!", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	PlayerState player = {};
	WorldState world = {};
	float deltaSeconds;
	int frameStartTicks, frameEndTicks = 0, deltaTicks = 0;

	initializeGame(pRenderer, player, world);
	
	while (!player.finishedGame) {
		if (deltaTicks < 1) {
			frameStartTicks = SDL_GetTicks();
			SDL_Delay(1);
			frameEndTicks = SDL_GetTicks();
			deltaTicks = frameEndTicks - frameStartTicks;
		}

		frameStartTicks = SDL_GetTicks();
		getInput(player, world);
		deltaSeconds = (float)deltaTicks / 1000.0f;

		updateGame(deltaSeconds, player, world);
		renderGame(pRenderer, player, world);

		frameEndTicks = SDL_GetTicks();
		deltaTicks = frameEndTicks - frameStartTicks;
	}
	if (player.won || player.died) {SDL_Delay(3000);}
	
	cleanup(player, world);

	SDL_DestroyRenderer(pRenderer);
	SDL_DestroyWindow(pWindow);
	SDL_Quit();
	return 0;
}