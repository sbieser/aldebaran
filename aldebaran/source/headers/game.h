#ifndef GAME_H
#define GAME_H

#include <vector>
#include <SDL.h>
#include "sprite.h";
#include "player.h"
#include "tiled_level.h"
#include "character.h"

class Graphics;
class Background;
class Layer;
class Input;
class Entity;

//TODO: Need to have some options for configuring what kind of game this is.
//For example, can player control all 4 directions? Gravity applied? ect
class Game {
public:
	Game();
	~Game();
private:	
	/// <summary>
	/// The main game loop
	/// </summary>
	void start();
	
	/// <summary>
	/// Reads the input from input devices and populates Input
	/// </summary>
	/// <param name="input">The input.</param>
	/// <param name="event">The event.</param>
	void readInput(Input & input, SDL_Event event);
	
	/// <summary>
	/// Draws all objects in the game
	/// </summary>
	/// <param name="graphics">The graphics.</param>
	void draw(Graphics & graphics);
	
	/// <summary>
	/// Updates the camera.
	/// </summary>
	/// <param name="x">The x.</param>
	/// <param name="y">The y.</param>
	void updateCamera(int x, int y);
	
	/// <summary>
	/// Nothing  currently
	/// </summary>
	/// <param name="elapsedTime">The elapsed time.</param>
	void update(int elapsedTime);
			
	/// <summary>
	/// Applies game world gravity to the entity
	/// </summary>
	void applyGravity(Entity * entity);

	void applyGravity(Player * player, int elapsedTime);

	/// <summary>
	/// The camera
	/// </summary>
	SDL_Rect camera;
	




	//The following are just testing objects

	/// <summary>
	/// The background, which can be static or scrolling, yay!
	/// </summary>
	Background * _background;

	//animated gork!
	Player * _gork;
	Tiled_Level _level;

	std::vector<Layer *> layers;

	std::vector<Character *> _characters;
	
	/// <summary>
	/// The amount of gravity to apply to all game objects
	/// </summary>
	float _gravity;
};

#endif // !GAME_H
