#include <SDL.h>
#include <algorithm>
#include "game.h"
#include "graphics.h"
#include "input.h"
#include "globals.h"
#include "bounding_box.h"

//TODO Add collision detection? Not sure if should be here.

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
	
	this->_gork = Player(graphics, 20,20);
	this->_level = Tiled_Level("Map_2.tmx", graphics);

	int LAST_UPDATE_TIME = SDL_GetTicks();

	//start the game loop
	//one loop of this is one frame
	//TODO: Got collision working but seems all wrong where the elapsed time is calcualted. Need to re-organize the game loop
	while (true) {

		const int CURRENT_TIME_MS = SDL_GetTicks();
		int ELAPSED_TIME_MS = std::min(CURRENT_TIME_MS - LAST_UPDATE_TIME, MAX_FRAME_TIME);

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



		if (input.isKeyHeld(SDL_SCANCODE_LEFT) == true) {
			this->_gork.moveLeft();
		}
		else if (input.isKeyHeld(SDL_SCANCODE_RIGHT) == true) {
			this->_gork.moveRight();
		}
		else {
			//this->_gork.stopDeltaX();
			this->_gork.stopMoving();
		}

		//check x asix collisions
		BoundingBox xMovedBbox = this->_gork.nextMove(ELAPSED_TIME_MS);
		if (xMovedBbox.destRect.x < 0 || xMovedBbox.destRect.x + xMovedBbox.destRect.w > globals::SCREEN_WIDTH) {
			this->_gork.stopDeltaX();
		}
		for (BoundingBox collidableBbox : this->_level._collidableObjects) {
			if (xMovedBbox.checkCollision(collidableBbox)) {
				this->_gork.stopDeltaX();
			}
		}

		//player can not control y direction, controlled by gravity
		/*if (input.isKeyHeld(SDL_SCANCODE_UP) == true) {
			this->_gork.moveUp();
		}
		else if (input.isKeyHeld(SDL_SCANCODE_DOWN) == true) {
			this->_gork.moveDown();
		}
		else {
			this->_gork.stopDeltaY();
		}*/
		//check for collisions on the y axis
		this->_gork.applyGravity();
		BoundingBox yMovedBbox = this->_gork.nextMove(ELAPSED_TIME_MS);
		if (yMovedBbox.destRect.y < 0 || yMovedBbox.destRect.y + yMovedBbox.destRect.h > globals::SCREEN_HEIGHT) {
			this->_gork.stopDeltaY();
		}
		for (BoundingBox collidableBbox : this->_level._collidableObjects) {
			if (yMovedBbox.checkCollision(collidableBbox)) {
				this->_gork.stopDeltaY();
			}
		}

		//this is where the real stuff happens
		this->update(ELAPSED_TIME_MS);
		this->draw(graphics);

		LAST_UPDATE_TIME = CURRENT_TIME_MS;
	}
}

void Game::draw(Graphics &graphics) {

	//clear the screen, prep to be ready to render more stuff
	graphics.clear();

	//we will do other draws here
	this->_level.draw(graphics);
	this->_gork.draw(graphics);
	
	//this will take what is on the renderer and render it to the screen
	graphics.flip();
}

void Game::update(float elapsedTime) {
	this->_gork.update(elapsedTime);
	this->_level.update(elapsedTime);
}