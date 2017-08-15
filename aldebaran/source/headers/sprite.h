#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <SDL.h>

class Graphics;

//TODO Add bounding box function, return the position that would be destination source and image width and height
//TODO Add transparency to sprites

class Sprite {
public:	
	/// <summary>
	/// Default constructor to initialize the <see cref="Sprite"/> class.
	/// </summary>
	Sprite();
	
	/// <summary>
	/// Initializes a new instance of the <see cref="Sprite"/> class.
	/// </summary>
	/// <param name="graphics">The graphics.</param>
	/// <param name="filePath">The file path.</param>
	/// <param name="sourceX">The source x.</param>
	/// <param name="sourceY">The source y.</param>
	/// <param name="width">The width.</param>
	/// <param name="height">The height.</param>
	/// <param name="posX">The position x.</param>
	/// <param name="posY">The position y.</param>
	Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, float posX, float posY, float scale);

	/// <summary>
	/// Finalizes an instance of the <see cref="Sprite"/> class.
	/// </summary>
	virtual ~Sprite();
	
	/// <summary>
	/// Updates this instance.
	/// </summary>
	virtual void update();
	
	/// <summary>
	/// Draws the specified graphics.
	/// NOTE: Doesn't feel right to have x and y here, it should be derived from somewhere else.
	/// But perhaps having it all parameterized allows other outside sources to mess with the position and
	/// scale?? Hmmm.
	/// Position seems more like something a class that contains a Sprite would have, not the sprite itself
	/// </summary>
	/// <param name="graphics">The graphics.</param>
	void draw(Graphics &graphics);

	///New
	SDL_Rect bbox();

protected:
	float _x;
	float _y;
	SDL_Rect _sourceRect;
	float _scale;
	SDL_Texture *_spriteSheet;
private:
};

#endif // !SPRITE_H
