#ifndef LEVEL_H
#define LEVEL_H

#include<string>
#include "globals.h"

class Graphics;
class SDL_Texture;

class Level {
public:
	Level();
	Level(std::string mapName, Vector2 spwanPoint, Graphics &graphics);
	~Level();
	void update(int elapsedTime);
	void draw(Graphics &graphics);
private:
	std::string _mapName;
	Vector2 _spwanPoint;
	Vector2 _size;
	SDL_Texture* _backgroundTexture;
	
	/// <summary>
	/// Loads the map.
	/// </summary>
	/// <param name="mapName">Name of the map.</param>
	/// <param name="graphics">The graphics.</param>
	void loadMap(std::string mapName, Graphics &graphics);

	
};

#endif // !LEVEL_H
