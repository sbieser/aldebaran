#include "sprite.h"
#include "graphics.h"
#include "globals.h"

Sprite::Sprite() {

}

Sprite::Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, float posX, float posY, float scale) : _x(posX), _y(posY), _scale(scale) {
	// Create a texture using the renderer and the surface 
	this->_spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filePath));

	// The sprite sheet might be bigger than the actual image we want to draw (common on sprite sheets), need to have
	// the source x,y and how big of a rectangle the source image we want to draw is. x,y = 0,0 is the upper left hand corner
	// of the texture. width and height are the source image dimensions.
	this->_sourceRect.x = sourceX;
	this->_sourceRect.y = sourceY;
	this->_sourceRect.w = width;
	this->_sourceRect.h = height;
	
	// If _spriteSheet is null, unable to load
	if (this->_spriteSheet == NULL) {
		printf("\nError: Unable to load image\n");
	}
}

Sprite::~Sprite() {
}

void Sprite::draw(Graphics &graphics) {
	SDL_Rect destReact = this->getDestinationRect();
	graphics.blitSurface(this->_spriteSheet, &this->_sourceRect, &destReact);
}

//TODO: Not sure if should be using _sourceRect, a _destRect is more representative of what the bounding box is
SDL_Rect Sprite::bbox()
{
	int scaledw = this->_sourceRect.w * this->_scale;
	int scaledh = this->_sourceRect.h * this->_scale;
	SDL_Rect bboxRect = { this->_x, this->_y, scaledw, scaledh };
	return bboxRect;
}

SDL_Rect Sprite::getDestinationRect()
{
	SDL_Rect destRect = { this->_x, this->_y, this->_sourceRect.w * this->_scale, this->_sourceRect.h * this->_scale };
	return destRect;
}

void Sprite::update() {

}