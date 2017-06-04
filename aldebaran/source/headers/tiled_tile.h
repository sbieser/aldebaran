#ifndef TILED_TILE_H
#define TILED_TILE_H

#include <SDL.h>
#include <vector>

class Tiled_Frame;
class Tiled_Tile;

struct SDL_Rect;

class Tiled_Tile {
public:
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

	SDL_Rect _sourceRect;
protected:
private:
	//for animation
	int _frameIndex;
	double _timeElapsed;
	//double _timeToUpdate; //this is really the current frames duration

	int _localid;
	bool _hasAnimation;
	std::vector<Tiled_Frame*> _animation;
};

#endif // !TILED_TILE_H
