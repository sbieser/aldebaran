#include "character.h"
#include <stdlib.h> 

Character::Character()
{
}

Character::Character(Graphics & graphics, float posX, float posY)
	: Entity(graphics, "content/sprites/plain_character.png", posX, posY),
	_updateTime(_randomUpdateTime()), _timeElapsed(0)
{
	this->setupAnimation();
	this->playAnimation("idle");

	//this->_updateTime = _randomUpdateTime();
}

Character::~Character()
{
}

int Character::_randomUpdateTime()
{
	int a[5] = { 100, 200, 300, 400, 500 };
	return a[rand() % 4];
}

void Character::animationDone(std::string currentAnimation)
{
	//no need to do anything here
}

void Character::setupAnimation()
{
	this->addAnimation(3, 0, 0, "idle", 16, 16);
	this->addAnimation(3, 0, 16, "moving", 16, 16);
	this->addAnimation(3, 0, 32, "jump", 16, 16);
}

void Character::update(int elapsedTime)
{
	//set random timer to change the direction: left, right, or stop
	this->_timeElapsed += elapsedTime;
	if (this->_timeElapsed > this->_updateTime) {
		this->_timeElapsed = 0;
		this->_updateTime = this->_randomUpdateTime();
		switch (rand() % 2) {
			case 0: {
				this->moveLeft();
				break;
			}
			case 1: {
				this->moveRight();
				break;
			}
		}
	}
}
