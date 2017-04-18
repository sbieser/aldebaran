#ifndef GAME_H
#define GAME_H

#include "sprite.h";

class Graphics;

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
	void update(float elapsedTime);
	
	/// <summary>
	/// The controllable character
	/// </summary>
	Sprite _player;
	Sprite _gork;
	//Sprite _gorkResized;
};

#endif // !GAME_H
