#include "graphics.h"
#include "background.h"



Background::Background()
{
}

//TODO: maybe this should inherit from Sprite class, lets play around with that idea!
Background::Background(Graphics & graphics, const std::string & filePath, int sourceX, int sourceY, int sourceWidth, int sourceHeight, int destWidth, int destHeight, int timeToScroll) :
	_destWidth(destWidth), _destHeight(destHeight), _timeToScroll(timeToScroll), _scrollingOffset(0), _timeElapsed(0)
{
	this->_backgroundTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filePath));

	this->_sourceRect.x = sourceX;
	this->_sourceRect.y = sourceY;
	this->_sourceRect.w = sourceWidth;
	this->_sourceRect.h = sourceHeight;

	if (this->_backgroundTexture == NULL) {
		printf("\nError: Unable to load background image\n");
	}
}

Background::~Background()
{
	//SDL_DestroyTexture(this->_backgroundTexture);
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
		graphics.blitSurface(this->_backgroundTexture, &this->_sourceRect, &destRect);
	}
	else {
		//blit differently if we are scrolling the background image
		SDL_Rect bgDestRestfh = { this->_scrollingOffset, 0, this->_destWidth, this->_destHeight };
		SDL_Rect bgDestRestsh = { this->_scrollingOffset + this->_destWidth, 0, this->_destWidth, this->_destHeight };
		graphics.blitSurface(this->_backgroundTexture, &this->_sourceRect, &bgDestRestfh);
		graphics.blitSurface(this->_backgroundTexture, &this->_sourceRect, &bgDestRestsh);
	}
}
