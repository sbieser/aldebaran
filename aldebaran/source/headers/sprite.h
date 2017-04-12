#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <SDL.h>

class Graphics;

class Sprite {
public:
	Sprite();
	Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, float posX, float posY);	

	/// <summary>
	/// Finalizes an instance of the <see cref="Sprite"/> class.
	/// </summary>
	virtual ~Sprite();
	
	/// <summary>
	/// Updates this instance.
	/// </summary>
	virtual void update();

	void draw(Graphics &graphics, int x, int y);

private:
	SDL_Rect _srouceRect;
	SDL_Texture *_spriteSheet;
	float x;
	float y;
};

#endif // !SPRITE_H
