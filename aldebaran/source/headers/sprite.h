#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <SDL.h>
#include "bounding_box.h"


class Graphics;

//TODO Might want to expand on the bounding box method. Maybe bounding box is its own class that can offer a lot
//	more than just x,y,width,height. Maybe center position, positions of all corners, collision checking, ect
//TODO Add transparency to sprites

class Sprite {
public:	
	/// <summary>
	/// Default constructor to initialize the <see cref="Sprite"/> class.
	/// </summary>
	Sprite();
		
	/// <summary>
	/// Initializes a new instance of the <see cref="Sprite"/> class.
	/// Simplified in that you only need the graphics, filePath, and intial position of the sprite
	/// </summary>
	/// <param name="graphics">The graphics.</param>
	/// <param name="filePath">The file path.</param>
	/// <param name="posX">The position x.</param>
	/// <param name="posY">The position y.</param>
	Sprite(Graphics &graphics, const std::string &filePath, float posX, float posY);
	
	/// <summary>
	/// Initializes a new instance of the <see cref="Sprite"/> class.
	/// </summary>
	/// <param name="graphics">The graphics.</param>
	/// <param name="surface">The surface.</param>
	/// <param name="posX">The position x.</param>
	/// <param name="posY">The position y.</param>
	Sprite(SDL_Texture * spriteSheet, float posX, float posY);

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
	
	/// <summary>
	/// Bounding box of this sprite
	/// </summary>
	/// <returns></returns>
	BoundingBox bbox();
	
	/// <summary>
	/// Sets the scale.
	/// </summary>
	/// <param name="scale">The scale.</param>
	void setScale(float scale);
	
	/// <summary>
	/// Sets the x.
	/// </summary>
	/// <param name="x">The x.</param>
	void setX(float x);	
	/// <summary>
	/// Sets the y.
	/// </summary>
	/// <param name="y">The y.</param>
	void setY(float y);

	/// <summary>
	/// Creates a destination rectangle based on the sprites position, width, height and scale
	/// </summary>
	/// <returns></returns>
	SDL_Rect getDestinationRect();
	
	/// <summary>
	/// Returns the source rectangle on the texture
	/// </summary>
	/// <returns></returns>
	SDL_Rect getSourceRect();
	
	/// <summary>
	/// Gets the texture.
	/// </summary>
	/// <returns></returns>
	SDL_Texture * getTexture();

protected:
	float _x;
	float _y;
	float _scale;

	//_sourceRect is the rectangle that defines the space on the texture we want to draw from. This is different than
	//_destRect, which is the rectangle that is actually drawn to the window. All collision detection should happen with 
	//a _destRect
	SDL_Rect _sourceRect;
	SDL_Texture *_spriteSheet;
private:	
};

#endif // !SPRITE_H
