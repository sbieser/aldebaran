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

	Character * character = new Character(graphics, 500, 100);
	character->setScale(3.0f);

	this->_characters.push_back(character);


	//Set up the level
	this->_level = Tiled_Level("Map_2.tmx", graphics);

	//Set up the background
	this->_background = new Background(graphics, "content/backgrounds/dkc2_bramble_background.png", globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, 50);

	//Set up the layer
	//this->_layer = new Layer(graphics, "content/backgrounds/dkc2_bramble_parallax.png", 0, 0, globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, 0.2f);
	Layer * layer1 = new Layer(graphics, "content/backgrounds/parallax_test_3.png", globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, 0.1f);
	layers.push_back(layer1);

	Layer * layer2 = new Layer(graphics, "content/backgrounds/parallax_test_2.png", globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, 0.5f);
	layers.push_back(layer2);

	Layer * layer3 = new Layer(graphics, "content/backgrounds/parallax_test_1.png", globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, 0.9f);
	layers.push_back(layer3);

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

		std::vector<BoundingBox> collidableObjects = this->_level._collidableObjects;
		for (Character * character : this->_characters) {
			collidableObjects.push_back(character->bbox());
		}

		//All player controlled objects should handle user input
		this->_gork->handleInput(input, collidableObjects, ELAPSED_TIME_MS);

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
		
		for (Layer * layer : this->layers) {
			layer->update(&this->camera);
		}

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

	std::vector<BoundingBox> collidableObjects = this->_level._collidableObjects;
	collidableObjects.push_back(this->_gork->bbox());
	for (Character * character : this->_characters) {
		character->update(elapsedTime, collidableObjects);
	}
}

void Game::draw(Graphics &graphics) {

	//clear the screen, prep to be ready to render more stuff
	graphics.clear();

	this->_background->draw(graphics);
	for (Layer * layer : this->layers) {
		layer->draw(graphics, &this->camera);
	}
	this->_level.draw(graphics, &this->camera);
	this->_gork->draw(graphics, &this->camera);



	for (Character * character : this->_characters) {
		//layer->draw(graphics, &this->camera);
		//do something to draw all the characters
		//maybe do drawing in here??
		character->draw(graphics, &this->camera);
	}

	//this will take what is on the renderer and render it to the screen
	graphics.flip();
}