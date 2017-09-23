#include <SDL.h>
#include <algorithm>
#include "game.h"
#include "graphics.h"
#include "input.h"
#include "globals.h"
#include "bounding_box.h"
#include "background.h"
#include "layer.h"

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

	camera = { 0, 0, globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT };

	this->gameloop();
}

Game::~Game() {

}

void Game::gameloop() {
	Graphics graphics;
	Input input;
	SDL_Event event;
	
	//Set up the player
	this->_gork = new Player(graphics, 300,250);
	this->_gork->setScale(3.0f);
	this->_gork->setTimeToUpdate(200);

	//Set up the level
	this->_level = Tiled_Level("Map_2.tmx", graphics);

	//Set up the background
	this->_background = new Background(graphics, "content/backgrounds/dkc2_bramble_background.png", 0, 0, 256, 256, globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, 50);

	//Set up the layer
	this->_layer = new Layer(graphics, "content/backgrounds/dkc2_bramble_parallax.png", 0, 0, globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT);
	
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
			this->_gork->moveLeft();
		}
		else if (input.isKeyHeld(SDL_SCANCODE_RIGHT) == true) {
			this->_gork->moveRight();
		}
		else {
			this->_gork->stopMoving();
		}

		//check x asix collisions
		BoundingBox xMovedBbox = this->_gork->nextMoveX(ELAPSED_TIME_MS);
		for (BoundingBox collidableBbox : this->_level._collidableObjects) {
			if (xMovedBbox.checkCollision(collidableBbox)) {
				this->_gork->stopDeltaX();
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
		if (input.wasKeyPressed(SDL_SCANCODE_SPACE) == true) {
			SDL_Log("spacebar was pressed");
			//how do we affect gravity!
			this->_gork->jump();
		}
		this->_gork->applyGravity(ELAPSED_TIME_MS);
		BoundingBox yMovedBbox = this->_gork->nextMoveY(ELAPSED_TIME_MS);
		for (BoundingBox collidableBbox : this->_level._collidableObjects) {
			if (yMovedBbox.checkCollision(collidableBbox)) {
				this->_gork->stopDeltaY();
			}
		}

		//this is where the real stuff happens
		this->update(ELAPSED_TIME_MS);
		
		//find center of this->_gork
		int gorkCenterX = this->_gork->bbox().destRect.x + (this->_gork->bbox().destRect.w / 2);
		int gorkCenterY = this->_gork->bbox().destRect.y + (this->_gork->bbox().destRect.h / 2);

		camera.x = gorkCenterX - (camera.w / 2);
		camera.y = gorkCenterY - (camera.h / 2);
		if (camera.x < 0) {
			camera.x = 0;
		}
		if (camera.y < 0) {
			camera.y = 0;
		}
		this->_layer->update(&this->camera);

		this->draw(graphics);

		LAST_UPDATE_TIME = CURRENT_TIME_MS;
	}
}

void Game::update(int elapsedTime) {
	if (this->_background != nullptr) {
		this->_background->update(elapsedTime);
	}
	this->_gork->update(elapsedTime);
	this->_level.update(elapsedTime);
	//this->_layer->update(&this->camera);
}

void Game::draw(Graphics &graphics) {

	//clear the screen, prep to be ready to render more stuff
	graphics.clear();

	//we will do other draws here
	//this->_level.draw(graphics);
	//this->_gork.draw(graphics);
	
	
	this->_background->draw(graphics);
	this->_layer->draw(graphics);
	this->_level.draw(graphics, &this->camera);
	this->_gork->draw(graphics, &this->camera);

	//this will take what is on the renderer and render it to the screen
	graphics.flip();
}