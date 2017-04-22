#include "animated_sprite.h"
#include "graphics.h"

AnimatedSprite::AnimatedSprite() {}

AnimatedSprite::AnimatedSprite(Graphics & graphics, const std::string & filePath, int sourceX, int sourceY, int width, int height, float posX, float posY, float scale, float timeToUpdate) :
	Sprite(graphics, filePath, sourceX, sourceY, width, height, posX, posY, scale),
	_frameIndex(0),
	_timeToUpdate(timeToUpdate),
	_visible(true),
	_currentAnimationOnce(false),
	_currentAnimation(""),
	_timeElapsed(0)
{

}

void AnimatedSprite::addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset) {
	std::vector<SDL_Rect> rectangles;
	for (int i = 0; i < frames; i++) {
		//SDL_Rect newRect = { (i + x) * width, y, width, height };
		SDL_Rect newRect = { (i * width) + x, y, width, height };
		rectangles.push_back(newRect);
	}
	this->_animations.insert({ name, rectangles });
	this->_offsets.insert({ name, offset });
}

void AnimatedSprite::resetAnimation() {
	this->_animations.clear();
	this->_offsets.clear();
}

void AnimatedSprite::playAnimation(std::string animation, bool once) {
	this->_currentAnimationOnce = once;
	if (this->_currentAnimation != animation) {
		this->_currentAnimation = animation;
		this->_frameIndex = 0;
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
		// Needed to reset the _timeElapsed so as to not run te animation forever quickly
		this->_timeElapsed -= this->_timeToUpdate;
		if (this->_frameIndex < this->_animations[this->_currentAnimation].size() - 1) {
			this->_frameIndex++;
		}
		else {
			
			if (this->_currentAnimationOnce == true) {
				this->setVisible(false);
			}
			this->_frameIndex = 0;
			this->animationDone(this->_currentAnimation);
		}
	}
}

void AnimatedSprite::draw(Graphics &graphics) {
	if (this->_visible) {
		
		//this is the destination the image will land on
		SDL_Rect destinationRectangle;
		destinationRectangle.x = this->_x + this->_offsets[this->_currentAnimation].x;
		destinationRectangle.y = this->_y + this->_offsets[this->_currentAnimation].y;
		destinationRectangle.w = this->_sourceRect.w * this->_scale;
		destinationRectangle.h = this->_sourceRect.h * this->_scale;


		//SDL_Rect sourceRect = this->_animations
		SDL_Rect sourceRectangle = this->_animations[this->_currentAnimation][this->_frameIndex];
		
		graphics.blitSurface(this->_spriteSheet, &sourceRectangle, &destinationRectangle);
	}
}