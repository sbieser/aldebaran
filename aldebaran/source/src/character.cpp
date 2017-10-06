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
	this->moveLeft();
	this->playAnimation("move_left");

	//this->_updateTime = _randomUpdateTime();
}

Character::~Character()
{
}

void Character::moveLeft()
{
	this->playAnimation("move_left");
	Entity::moveLeft();
}

void Character::moveRight()
{
	this->playAnimation("move_right");
	Entity::moveRight();
}

int Character::_randomUpdateTime()
{
	int a[5] = { 1000, 2000, 3000, 4000, 5000 };
	return a[rand() % 4];
}

void Character::animationDone(std::string currentAnimation)
{
	//no need to do anything here
}

void Character::setupAnimation()
{
	this->addAnimation(3, 0, 0, "move_left", 16, 16);
	this->addAnimation(3, 0, 16, "move_right", 16, 16);
	this->addAnimation(3, 0, 32, "jump", 16, 16);
}

void Character::update(int elapsedTime, std::vector<BoundingBox> collidableObjects)
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


	//move x position and check for collissions
	this->_velocity.x = this->_acceleration.x * elapsedTime;
	this->_x += this->_velocity.x * elapsedTime;
	for (BoundingBox collidableBbox : collidableObjects) {
		if (this->bbox().checkCollision(collidableBbox)) {
			this->_x -= this->_velocity.x * elapsedTime;
		}
	}
	
	this->_velocity.y = this->_acceleration.y * elapsedTime;
	this->_y += this->_velocity.y * elapsedTime;
	for (BoundingBox collidableBbox : collidableObjects) {
		if (this->bbox().checkCollision(collidableBbox)) {
			this->_y -= this->_velocity.y * elapsedTime;
		}
	}

	Entity::applyGravity(elapsedTime);
	
	Entity::update(elapsedTime);
}
