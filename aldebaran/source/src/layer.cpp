#include "layer.h"
#include "graphics.h"
#include "sprite.h"

Layer::Layer()
{
}

Layer::Layer(Graphics & graphics, const std::string & filePath, int destWidth, int destHeight, float rate)
	: _destWidth(destWidth), _destHeight(destHeight), _x(0), _y(0), _lastCameraX(0), _lastCameraY(0), _rate(rate)
{
	//create the surface first, we are going to do some color keying
	SDL_Surface * surface = graphics.loadImage(filePath);
	if (SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 225, 30, 191)) < 0) {
		printf("SDL_SetColorKey failed: %s\n", SDL_GetError());
	}

	SDL_Texture * texture = SDL_CreateTextureFromSurface(graphics.getRenderer(), surface);
	this->_sprite = new Sprite(texture, 0, 0);
}

Layer::~Layer()
{
	this->_sprite->~Sprite();
}

void Layer::draw(Graphics & graphics, SDL_Rect * camera)
{
	
	float newYPosition = this->_y - camera->y;
	SDL_Rect destRectOne = { this->_x, newYPosition, this->_destWidth, this->_destHeight };
	SDL_Rect destRectTwo = { this->_x + this->_destWidth, newYPosition, this->_destWidth, this->_destHeight };
	SDL_Rect destRectThree = { this->_x - this->_destWidth, newYPosition, this->_destWidth, this->_destHeight };
	SDL_Rect sourceRect = this->_sprite->getSourceRect();
	graphics.blitSurface(this->_sprite->getTexture(), &sourceRect, &destRectOne);
	graphics.blitSurface(this->_sprite->getTexture(), &sourceRect, &destRectTwo);
	graphics.blitSurface(this->_sprite->getTexture(), &sourceRect, &destRectThree);
}

void Layer::update(SDL_Rect * camera)
{
	float x = this->_sprite->destRect().x;
	this->_sprite->setX(x - camera->x);
	if (this->_lastCameraX != camera->x) {
		//this->_y = this->_y - camera->y;
		float addValue = camera->x - this->_lastCameraX;
		if (addValue < 0) {
			addValue -= this->_rate;
		}
		else {
			addValue += this->_rate;
		}
		this->_x -= addValue;

		if (this->_x < -this->_destWidth || this->_x > this->_destWidth) {
			this->_x = 0;
		}
		this->_lastCameraX = camera->x;
	}
	
	//float y = this->_sprite->getDestinationRect().y;
	//if (this->_lastCameraY != camera->y) {
	//	this->_lastCameraY = camera->y;
	//	this->_y = this->_y - camera->y;
	//}
}
