#include "animated_sprite.h"
#include "graphics.h"

AnimatedSprite::AnimatedSprite() {}

AnimatedSprite::AnimatedSprite(Graphics & graphics, const std::string & filePath, int posX, int posY)
	: Sprite(graphics, filePath, posX, posY), 
	_timeToUpdate(50), _frameIndex(0), _visible(true), _currentAnimationOnce(false), _currentAnimation(""), _timeElapsed(0)
{
	//but this will be wrong, the _sourceRect will be all wonky because it is a sprite sheet
}

//sourceX, sourceY, width, height, and scale should be removed eventually
AnimatedSprite::AnimatedSprite(Graphics & graphics, const std::string & filePath, int sourceX, int sourceY, int width, int height, float posX, float posY, float scale, float timeToUpdate) 
	: Sprite(graphics, filePath, sourceX, sourceY, width, height, posX, posY, scale),
	//: Sprite(graphics, filePath, posX, posY),
	_frameIndex(0),
	_timeToUpdate(timeToUpdate),
	_visible(true),
	_currentAnimationOnce(false),
	_currentAnimation(""),
	_timeElapsed(0)
{

}

void AnimatedSprite::addAnimation(int frames, int x, int y, std::string name, int width, int height) {
	std::vector<SDL_Rect> rectangles;
	for (int i = 0; i < frames; i++) {
		SDL_Rect newRect = { (i * width) + x, y, width, height };
		rectangles.push_back(newRect);
	}
	this->_animations.insert({ name, rectangles });
}

void AnimatedSprite::setTimeToUpdate(int timeToUpdate)
{
	this->_timeToUpdate = timeToUpdate;
}

void AnimatedSprite::resetAnimation() {
	this->_animations.clear();
}

void AnimatedSprite::playAnimation(std::string animation, bool once) {
	this->_currentAnimationOnce = once;
	if (this->_currentAnimation != animation) {
		this->_currentAnimation = animation;
		this->_frameIndex = 0;
		this->_sourceRect = this->_animations[this->_currentAnimation][this->_frameIndex];
	}
}

void AnimatedSprite::setVisible(bool visible) {
	this->_visible = visible;
}

void AnimatedSprite::stopAnimation() {
	this->_frameIndex = 0;
	this->animationDone(this->_currentAnimation);
}

void AnimatedSprite::update(int elapsedTime) {
	Sprite::update();

	this->_timeElapsed += elapsedTime;
	if (this->_timeElapsed > this->_timeToUpdate) {
		// Needed to reset the _timeElapsed so as to not run the animation forever quickly
		this->_timeElapsed -= this->_timeToUpdate;
		if (this->_frameIndex < this->_animations[this->_currentAnimation].size() - 1) {
			this->_frameIndex++;
			this->_sourceRect = this->_animations[this->_currentAnimation][this->_frameIndex];
		}
		else {
			
			if (this->_currentAnimationOnce == true) {
				this->setVisible(false);
			}
			this->_frameIndex = 0;
			this->_sourceRect = this->_animations[this->_currentAnimation][this->_frameIndex];
			this->animationDone(this->_currentAnimation);
		}
	}
}

//TODO: animated sprite blits in this function, but I feel like this should be done in the sprite class.
//TODO: We are not using this, get rid of this
void AnimatedSprite::draw(Graphics &graphics) {
	if (this->_visible) {	
		//this is the destination the image will land on
		SDL_Rect destinationRectangle;
		destinationRectangle.x = this->_x;
		destinationRectangle.y = this->_y;
		destinationRectangle.w = this->_sourceRect.w * this->_scale;
		destinationRectangle.h = this->_sourceRect.h * this->_scale;
		SDL_Rect sourceRectangle = this->_animations[this->_currentAnimation][this->_frameIndex];
		//Since this->_sourceRect is protected, we can set this as long as we are a subclass of Sprite
		this->_sourceRect = sourceRectangle;
		Sprite::draw(graphics);
	}
}

//TODO: Need to send info to Sprite::draw
void AnimatedSprite::draw(Graphics & graphics, SDL_Rect * camera)
{
	//original
	/*if (this->_visible) {
		//this is the destination the image will land on
		int newPositionX = this->_x - camera->x;
		int newPositionY = this->_y - camera->y;

		SDL_Rect sourceRectangle = this->_animations[this->_currentAnimation][this->_frameIndex];
		SDL_Rect destinationRectangle;
		destinationRectangle.x = newPositionX;
		destinationRectangle.y = newPositionY;
		destinationRectangle.w = sourceRectangle.w * this->_scale;
		destinationRectangle.h = sourceRectangle.h * this->_scale;
		graphics.blitSurface(this->_spriteSheet, &sourceRectangle, &destinationRectangle);
	}
	*/

	if (this->_visible) {
		//this is the destination the image will land on
		int newPositionX = this->_x - camera->x;
		int newPositionY = this->_y - camera->y;

		SDL_Rect destinationRectangle;
		destinationRectangle.x = newPositionX;
		destinationRectangle.y = newPositionY;
		destinationRectangle.w = this->_sourceRect.w * this->_scale;
		destinationRectangle.h = this->_sourceRect.h * this->_scale;
		graphics.blitSurface(this->_spriteSheet, &this->_sourceRect, &destinationRectangle);
	}
}