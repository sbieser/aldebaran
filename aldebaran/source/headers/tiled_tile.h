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
/// 
/// The types of collisions include:
/// Rectangle:
/// <objectgroup draworder="index">
///		<object id = "8" x = "0" y = "0" width = "16" height = "16" / >
///	< / objectgroup>
///
/// Ellipse:
/// <objectgroup draworder="index">
///		<object id = "9" x = "0" y = "0" width = "16" height = "16">
///			<ellipse / >
///		< / object>
///	< / objectgroup>
///
/// Triangle:
///	<objectgroup draworder = "index">
///		<object id = "10" x = "0" y = "0">
///			<polygon points = "0,0 16,16 0,16" / >
///		< / object>
///	< / objectgroup>
///
/// Polyline:
/// <objectgroup draworder="index">
///		<object id = "11" x = "0" y = "0">
///			<polyline points = "0,0 10,1 11,5 15,5 15,12" / >
///		< / object>
///	< / objectgroup>
/// NOTE: Does not need to be a closed polyline, not sure how useful this would be.
/// NOTE: Each tile can have any number of collision objects
/// 
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

};

#endif // !TILED_TILE_H
