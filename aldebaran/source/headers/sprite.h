#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <SDL.h>

class Graphics;

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
	/// </summary>
	/// <param name="graphics">The graphics.</param>
	/// <param name="x">The x.</param>
	/// <param name="y">The y.</param>
	void draw(Graphics &graphics /*, int x, int y*/);

private:
	SDL_Rect _sourceRect;
	SDL_Texture *_spriteSheet;
	float _scale;
	float _x;
	float _y;
};

#endif // !SPRITE_H
