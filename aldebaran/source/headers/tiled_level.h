#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include "vector_2.h"
#include "tinyxml2.h"

class SDL_Texture;
class Graphics;
class Tiled_Layer;
class Tiled_Tileset;
class Tiled_Tile;
class BoundingBox;

struct SDL_Rect;

class Tiled_Level {
public:
	Tiled_Level();
	Tiled_Level(std::string mapName, Graphics &graphics);
	~Tiled_Level();
	
	/// <summary>
	/// Updates the specified elapsed time.
	/// </summary>
	/// <param name="elapsedTime">The elapsed time.</param>
	void update(int elapsedTime);
		
	/// <summary>
	/// Iterates each layer in the tilemap and renders each tile individually.
	/// </summary>
	/// <param name="graphics">The graphics.</param>
	void draw(Graphics &graphics);

	//testing
	void draw(Graphics &graphics, SDL_Rect* camera);
	
	/// <summary>
	/// Get the tileset associated to the tileset. Internally we use each tilesets firstgid and tilecount to determine which
	/// is the tileset we need.
	/// </summary>
	/// <param name="tilegid">The tilegid.</param>
	/// <returns></returns>
	Tiled_Tileset* getTileset(int tilegid);
	
	/// <summary>
	/// Asks the level if the given position collides with any of the layers tiles
	/// </summary>
	/// <param name="x">The x.</param>
	/// <param name="y">The y.</param>
	/// <returns></returns>
	//bool collidesWithPosition(float x, float y);

	/// <summary>
	/// A vector of all the collidable objects represented as bounding boxes
	/// </summary>
	std::vector<BoundingBox> _collidableObjects;
	std::vector<SDL_Rect> _optCollidableObjects;

private:
	int _scale;
	std::string _mapName;
	Vector2 _spwanPoint;
	Vector2 _size;
	Vector2 _tilesize;
	
	/// <summary>
	/// Each layer of the tiled map
	/// </summary>
	std::vector<Tiled_Layer*> _layers;	
	/// <summary>
	/// Each tileset of the tiled map
	/// </summary>
	std::vector<Tiled_Tileset*> _tilesets;	

	/// <summary>
	/// Loads the map.
	/// </summary>
	/// <param name="mapName">Name of the map.</param>
	/// <param name="graphics">The graphics.</param>
	tinyxml2::XMLError loadMap(std::string mapName, Graphics &graphics);
};

#endif // !LEVEL_H
