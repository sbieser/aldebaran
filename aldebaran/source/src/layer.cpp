#include "layer.h"
#include "graphics.h"
#include "sprite.h"

Layer::Layer()
{
}

Layer::Layer(Graphics & graphics, const std::string & filePath, float posX, float posY, int destWidth, int destHeight)
	: _destWidth(destWidth), _destHeight(destHeight)
{
	//create the surface first, we are going to do some color keying
	SDL_Surface * surface = graphics.loadImage(filePath);
	if (SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 225, 30, 191)) < 0) {
		printf("SDL_SetColorKey failed: %s\n", SDL_GetError());
	}

	SDL_Texture * texture = SDL_CreateTextureFromSurface(graphics.getRenderer(), surface);
	this->_sprite = new Sprite(texture, posX, posY);
}

Layer::~Layer()
{
}

void Layer::draw(Graphics & graphics)
{
	//this->_sprite->draw(graphics);
	SDL_Rect destRect = { 0, 0, _destWidth, _destHeight };
	SDL_Rect sourceRect = this->_sprite->getSourceRect();
	graphics.blitSurface(this->_sprite->getTexture(), &sourceRect, &destRect);
}
