//#include <SDL.h>
#include <algorithm>
#include "game.h"
#include "graphics.h"
#include "input.h"
#include "globals.h"
#include "bounding_box.h"
#include "background.h"
#include "layer.h"
#include "collision_detection.h"


using namespace collision_detection;
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

	this->start();
}

Game::~Game() {

}

void Game::start() {
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
		SDL_Log("Elapsed Time: %d", ELAPSED_TIME_MS);
		//Read inputs
		if (SDL_PollEvent(&event)) {
			this->readInput(input, event);
		}

		//If escape key was pressed, just exit game for now
		if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true) {
			return;
		}
		
		//All player controlled objects should handle user input
		this->_gork->handleInput(input);

		//this is where the real stuff happens
		this->update(ELAPSED_TIME_MS);
		
		//Update the camera using players center position for now
		int gorkCenterX = this->_gork->bbox().destRect.x + (this->_gork->bbox().destRect.w / 2);
		int gorkCenterY = this->_gork->bbox().destRect.y + (this->_gork->bbox().destRect.h / 2);
		this->updateCamera(gorkCenterX, gorkCenterY);
		
		this->draw(graphics);

		LAST_UPDATE_TIME = CURRENT_TIME_MS;
	}
}

void Game::readInput(Input & input, SDL_Event event)
{
	//resets pressed and released keys
	input.beginNewFrame();
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

//advance the game state
void Game::update(int elapsedTime) {
	if (this->_background != nullptr) {
		this->_background->update(elapsedTime);
	}
	
	this->_level.update(elapsedTime);

	for (Layer * layer : this->layers) {
		layer->update(&this->camera);
	}
	
	this->_gork->update(elapsedTime);
	Vector2 _playerOldPosition = this->_gork->getOldPosition();
	applyGravity(this->_gork, elapsedTime);
	for (SDL_Rect tileRect : this->_level._collidableTiles) {
		SDL_Rect dr_a = this->_gork->destRect();

		//Bounding box for  the collidable tile
		bbox b = boundingBox(tileRect.x, tileRect.y, tileRect.w, tileRect.h);

		//Bounding box for checking the x axis
		bbox a = boundingBox(dr_a.x, _playerOldPosition.y, dr_a.w, dr_a.h);
		if (intersect(a, b)) {
			this->_gork->setX(_playerOldPosition.x);
		}

		//Bounding box for checking the y axis
		a = boundingBox(dr_a.x, dr_a.y, dr_a.w, dr_a.h);
		if (intersect(a, b)) {
			//set y position to old y position
			this->_gork->setY(_playerOldPosition.y);

			//get center of tile rect
			Vector2 center_b = Vector2(tileRect.x + (tileRect.w / 2), tileRect.y + (tileRect.h / 2));
			SDL_Rect gorkRect = this->_gork->destRect();
			Vector2 center_a = this->_gork->center();

			//check to see if player is grounded
			
			float wy = (gorkRect.w + tileRect.w) * (center_a.y - center_b.y);
			float hx = (gorkRect.h + tileRect.h) * (center_a.x - center_b.x);

			if (wy > hx) {
				if (wy > -hx) {
					//SDL_Log("colliding with top");
				}
				else {
					//SDL_Log("colliding with left");
				}
			}
			else {
				if (wy > -hx) {
					//SDL_Log("colliding with right");
				}
				else {
					//SDL_Log("colliding with bottom");
					//this means we can jump
					_gork->_canJump = true;
				}
			}
		}
	}
	
	//check collisions with the level
	for (Character * character : this->_characters) {
		//call the characters update which may do a number of things internally, such as moving the character, incrementing the animation, ect
		character->update(elapsedTime);
		
		//apply gravity to the character
		this->applyGravity(character);

		Vector2 _oldPosition = character->oldPosition();

		for (SDL_Rect tileRect : this->_level._collidableTiles) {
			SDL_Rect dr_a = character->destRect();

			//Bounding box for  the collidable tile
			bbox b = boundingBox(tileRect.x, tileRect.y, tileRect.w, tileRect.h);

			//Bounding box for checking the x axis
			bbox a = boundingBox(dr_a.x, _oldPosition.y, dr_a.w, dr_a.h);
			if (intersect(a, b)) {
				character->setX(_oldPosition.x);
			}

			//Bounding box for checking the y axis
			a = boundingBox(dr_a.x, dr_a.y, dr_a.w, dr_a.h);
			if (intersect(a, b)) {
				character->setY(_oldPosition.y);
			}
		}
	}
}

void Game::applyGravity(Entity * entity)
{
	//apply gravity to the character
	float _yAcceleration = entity->acceleration.y + .001f;
	entity->acceleration.y = std::min(0.03f, _yAcceleration);
}

void Game::applyGravity(Player * player, int elapsedTime)
{
	float _accelerationY = 0.0f;
	if (player->_jumped) {
		//We have jumped, subtract gravity instead to head upwards
		player->_jumpTimeElapsed += elapsedTime;
		if (player->_jumpTimeElapsed > player->_jumpTime) {
			player->_jumped = false;
			player->_jumpTimeElapsed = 0;
		}
		_accelerationY = player->getAccelerationY() - .001f;
		player->setAccelerationY(_accelerationY);
	}
	else {
		//otherwise apply gravity downwards
		_accelerationY = player->getAccelerationY() + .001f; //means we are heading down, if we - .001f, we will head up!
		player->setAccelerationY(std::min(0.03f, _accelerationY));
	}
	
}


//I'm ok with the objects drawing themselves
void Game::draw(Graphics &graphics) {

	//clear the screen, prep to be ready to render more stuff
	graphics.clear();

	//draw the background
	this->_background->draw(graphics);

	//draw the parallax layers
	for (Layer * layer : this->layers) {
		layer->draw(graphics, &this->camera);
	}

	//draw the level
	this->_level.draw(graphics, &this->camera);

	//draw the player
	this->_gork->draw(graphics, &this->camera);


	//draw all the other characters
	for (Character * character : this->_characters) {
		character->draw(graphics, &this->camera);
	}

	//this will take what is on the renderer and render it to the screen
	graphics.flip();
}

void Game::updateCamera(int x, int y)
{
	this->camera.x = x - (this->camera.w / 2);
	this->camera.y = y - (this->camera.h / 2);
	if (this->camera.x < 0) {
		this->camera.x = 0;
	}
	if (this->camera.y < 0) {
		this->camera.y = 0;
	}
}
