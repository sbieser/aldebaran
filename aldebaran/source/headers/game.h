#ifndef GAME_H
#define GAME_H

#include <vector>
#include "sprite.h";
#include "player.h"
#include "tiled_level.h"

class Graphics;
class SDL_Texture;
class Background;
class Layer;
struct SDL_Rect;

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
	void gameloop();
	
	/// <summary>
	/// Draws the specified graphics.
	/// </summary>
	/// <param name="graphics">The graphics.</param>
	void draw(Graphics &graphics);
	
	/// <summary>
	/// Nothing  currently
	/// </summary>
	/// <param name="elapsedTime">The elapsed time.</param>
	void update(int elapsedTime);
		
	/// <summary>
	/// The camera
	/// </summary>
	SDL_Rect camera;
	
	/// <summary>
	/// The background, which can be static or scrolling, yay!
	/// </summary>
	Background * _background;
	//Layer * _layer;

	//animated gork!
	Player * _gork;
	Tiled_Level _level;

	std::vector<Layer *> layers;
	
};

#endif // !GAME_H
