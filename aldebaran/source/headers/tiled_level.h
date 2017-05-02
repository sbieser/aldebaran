#ifndef LEVEL_H
#define LEVEL_H

#include<string>
#include "globals.h"
#include "tinyxml2.h"

class Graphics;
class SDL_Texture;

class Tiled_Level {
public:
	Tiled_Level();
	Tiled_Level(std::string mapName, Vector2 spwanPoint, Graphics &graphics);
	~Tiled_Level();
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
	tinyxml2::XMLError loadMap(std::string mapName, Graphics &graphics);

	
};

#endif // !LEVEL_H
