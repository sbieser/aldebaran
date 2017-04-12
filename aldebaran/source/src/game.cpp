#include <SDL.h>
#include <algorithm>
#include "game.h"
#include "graphics.h"
#include "input.h"

/*
	Game class
	Holds all game loop information
*/

namespace {
	const int FPS = 50;
	const int MAX_FRAME_TIME = 1000 / FPS;
}

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	this->gameloop();
}

Game::~Game() {

}

void Game::gameloop() {
	Graphics graphics;
	Input input;
	SDL_Event event;

	int LAST_UPDATE_TIME = SDL_GetTicks();

	//start the game loop
	//one loop of this is one frame
	while (true) {

		//resets pressed and released keys
		input.beginNewFrame();

		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				if (event.key.repeat == 0) {
					input.keyDownEvent(event);
				} 
			}
			else if (event.type == SDL_KEYUP) {
				input.keyUpEvent(event);
			}
			else if (event.type == SDL_QUIT) {
				return;
			} 
		}
		if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true) {
			return;
		}

		const int CURRENT_TIME_MS = SDL_GetTicks();
		int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;

		this->update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));

		LAST_UPDATE_TIME = CURRENT_TIME_MS;
	}
}

void Game::draw(Graphics &graphics) {

}

void Game::update(float elapsedTime) {

}

