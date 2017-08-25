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
	
	this->_gork = Player(graphics, 75,75);
	this->_level = Tiled_Level("Map_2.tmx", graphics);

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
		

		/*
			Move on x axis and check for collisions
		*/
		if (input.isKeyHeld(SDL_SCANCODE_LEFT) == true) {
			this->_gork.moveLeft();
		} 
		else if (input.isKeyHeld(SDL_SCANCODE_RIGHT) == true) {
			this->_gork.moveRight();
		}
		else {
			this->_gork.stopDeltaX();
		}
		//check x asix collisions
		BoundingBox xMovedBbox = this->_gork.nextMove();//this->_gork.bbox();
		if (xMovedBbox.destRect.x < 0 || xMovedBbox.destRect.x + xMovedBbox.destRect.w > globals::SCREEN_WIDTH) {
			this->_gork.stopDeltaX();
		}
		for (BoundingBox collidableBbox : this->_level._collidableObjects) {
			if (this->_gork.bbox().checkCollision(collidableBbox)) {
				this->_gork.stopDeltaX();
			}
		}
		
		/*
			Move on y axis and check for collisions
		*/
		if (input.isKeyHeld(SDL_SCANCODE_UP) == true) {
			this->_gork.moveUp();
		}
		else if (input.isKeyHeld(SDL_SCANCODE_DOWN) == true) {
			this->_gork.moveDown();
		}
		else {
			this->_gork.stopDeltaY();
		}
		//check for collisions on the y axis
		BoundingBox yMovedBbox = this->_gork.nextMove();//this->_gork.bbox();
		if (yMovedBbox.destRect.y < 0 || yMovedBbox.destRect.y + yMovedBbox.destRect.h > globals::SCREEN_HEIGHT) {
			this->_gork.stopDeltaY();
		}
		for (BoundingBox collidableBbox : this->_level._collidableObjects) {
			if (this->_gork.bbox().checkCollision(collidableBbox)) {
				this->_gork.stopDeltaY();
			}
		}

		const int CURRENT_TIME_MS = SDL_GetTicks();
		int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;

		//this is where the real stuff happens
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
	this->_gork.draw(graphics);
	
	//this will take what is on the renderer and render it to the screen
	graphics.flip();
}

void Game::update(float elapsedTime) {
	this->_gork.update(elapsedTime);
	this->_level.update(elapsedTime);
}