#include "sprite.h"
#include "graphics.h"
#include "globals.h"

Sprite::Sprite() {

}

Sprite::Sprite(Graphics & graphics, const std::string & filePath, float posX, float posY)
	: Sprite(SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filePath)), posX, posY)
{}

Sprite::Sprite(SDL_Texture * spriteSheet, float posX, float posY)
	: _x(posX), _y(posY), _scale(1)
{
	// Create a texture using the renderer and the surface 
	this->_spriteSheet = spriteSheet;
	// If _spriteSheet is null, unable to load
	if (this->_spriteSheet == NULL) {
		printf("SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
	}

	int w, h;
	if (SDL_QueryTexture(this->_spriteSheet, nullptr, nullptr, &w, &h) < 0) {
		// Unrecoverable error, exit here.
		printf("SDL_QueryTexture failed: %s\n", SDL_GetError());
	}

	this->_sourceRect = { 0, 0, w, h };
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
	SDL_DestroyTexture(this->_spriteSheet);
}

void Sprite::draw(Graphics &graphics) {
	//SDL_Log("Sprite::draw");
	//something seems off about this
	SDL_Rect destReact = this->getDestinationRect();
	graphics.blitSurface(this->_spriteSheet, &this->_sourceRect, &destReact);
}

//TODO: Not sure if should be using _sourceRect, a _destRect is more representative of what the bounding box is
BoundingBox Sprite::bbox()
{
	return BoundingBox(this->getDestinationRect());
}

void Sprite::setScale(float scale)
{
	this->_scale = scale;
}

void Sprite::setX(float x)
{
	this->_x = x;
}

void Sprite::setY(float y)
{
	this->_y = y;
}

SDL_Rect Sprite::getDestinationRect()
{
	SDL_Rect destRect = { this->_x, this->_y, this->_sourceRect.w * this->_scale, this->_sourceRect.h * this->_scale };
	return destRect;
}

SDL_Rect Sprite::getSourceRect()
{
	return this->_sourceRect;
}

SDL_Texture * Sprite::getTexture()
{
	return this->_spriteSheet;
}

void Sprite::update() {
	//nothing to update currently right??
}