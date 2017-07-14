#ifndef TILED_TILE_H
#define TILED_TILE_H

#include <SDL.h>
#include <vector>

class Tiled_Frame;
class Tiled_Tile;

struct SDL_Rect;


/// <summary>
/// The data structure that contains all data and properties pertaining to a Tile in a tile set. This includes:
/// source rectangle for blitting, automatic handling of animations, and collision properties.
/// </summary>
class Tiled_Tile {
public:
	// Wondering if I need to pass in the XML struct instead, might make more sense, as all information contained
	// would have the animations and the collision boundaries
	Tiled_Tile(SDL_Rect sourceRect, int localid);
	~Tiled_Tile();
	
	/// <summary>
	/// Get the source rect of the tile, could be static tile or animated tile
	/// </summary>
	/// <returns></returns>
	SDL_Rect getSourceRect();
	
	/// <summary>
	/// Updates the tile animation
	/// </summary>
	void update(int elapsedTime);
	
	/// <summary>
	/// Adds an animation frame to the tile
	/// </summary>
	/// <param name="tile">The tile.</param>
	/// <param name="duration">The duration.</param>
	void addAnimation(Tiled_Tile * tile, int duration);
	
	/// <summary>
	/// The rect for the source image for the tile
	/// </summary>
	SDL_Rect _sourceRect;
protected:
private:
	//for animation
	int _frameIndex;
	double _timeElapsed;
	int _localid;
	bool _hasAnimation;
	std::vector<Tiled_Frame*> _animation;

	//how to represent collision?
	//here can be many of them by the way, they are collected in an 
	//objectgroup, which should be std::vector<Tiled_Object*> _objectrgroup;
};

#endif // !TILED_TILE_H
