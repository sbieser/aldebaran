#include "graphics.h"
#include "background.h"
#include "sprite.h"

Background::Background()
{
}

Background::Background(Graphics & graphics, const std::string & filePath, int destWidth, int destHeight, int timeToScroll)
	: _destWidth(destWidth), _destHeight(destHeight), _timeToScroll(timeToScroll), _scrollingOffset(0), _timeElapsed(0)
{
	this->_sprite = new Sprite(graphics, filePath, 0, 0);
}

Background::~Background()
{
	this->_sprite->~Sprite();
}

void Background::update(int elapsedTime)
{
	if (this->_timeToScroll != 0) {
		this->_timeElapsed += elapsedTime;
		if (this->_timeElapsed > this->_timeToScroll) {
			this->_timeElapsed = 0;
			--this->_scrollingOffset;
			if (this->_scrollingOffset < -this->_destWidth) {
				this->_scrollingOffset = 0;
			}
		}
	}
}

void Background::draw(Graphics & graphics)
{
	if (this->_timeToScroll == 0) {
		SDL_Rect destRect = { 0, 0, this->_destWidth, this->_destHeight };
		graphics.blitSurface(this->_sprite->getTexture(), &this->_sprite->getSourceRect(), &destRect);
	}
	else {
		//blit differently if we are scrolling the background image
		SDL_Rect bgDestRestfh = { this->_scrollingOffset, 0, this->_destWidth, this->_destHeight };
		SDL_Rect bgDestRestsh = { this->_scrollingOffset + this->_destWidth, 0, this->_destWidth, this->_destHeight };
		graphics.blitSurface(this->_sprite->getTexture(), &this->_sprite->getSourceRect(), &bgDestRestfh);
		graphics.blitSurface(this->_sprite->getTexture(), &this->_sprite->getSourceRect(), &bgDestRestsh);
	}
}
