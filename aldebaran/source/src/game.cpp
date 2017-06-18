#include <SDL.h>
#include <algorithm>
#include "game.h"
#include "graphics.h"
#include "input.h"
#include "globals.h"

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
	this->_player = Sprite(graphics, "content/sprites/MyChar.png", 0, 0, 16, 16, 0, 0, 2);

	// original sprite, each sprite size is 16x16, but we will set scale to x3
	//this->_gork = Sprite(graphics, "content/sprites/gorksprite.png", 0, 0, 16, 16, 75, 75, 3);


	this->_gork = Player(graphics, 75, 75);
	//this->_level = Tiled_Level("Map_1.tmx", Vector2(0, 0), graphics);
	this->_level = Tiled_Level("Map_2.tmx", graphics);

	// gorksprite_resized.png is gorksprite.png resized 3x in paint.net. Each sprite size is 48x48
	//this->_gorkResized = Sprite(graphics, "content/sprites/gorksprite_resized.png", 0, 0, 48, 48, 75 + 48, 75, 1);
	
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
		else if (input.isKeyHeld(SDL_SCANCODE_LEFT) == true) {
			this->_gork.moveLeft();
		}
		else if (input.isKeyHeld(SDL_SCANCODE_RIGHT) == true) {
			this->_gork.moveRight();
		}
		else {
			this->_gork.stopMoving();
		}

		const int CURRENT_TIME_MS = SDL_GetTicks();
		int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;

		this->update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));

		LAST_UPDATE_TIME = CURRENT_TIME_MS;

		this->draw(graphics);
	}
}

void Game::draw(Graphics &graphics) {

	//clear the screen, prep to be ready to render more stuff
	graphics.clear();
	//we will do other draws here
	this->_level.draw(graphics);
	//this->_player.draw(graphics);
	this->_gork.draw(graphics);
	
	//this will take what is on the renderer and render it to the screen
	graphics.flip();
}

void Game::update(float elapsedTime) {
	this->_gork.update(elapsedTime);
	this->_level.update(elapsedTime);
}