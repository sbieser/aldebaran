#include <algorithm>
#include "entity.h"

namespace entity_constants {
	const float WALK_SPEED = 0.03f;
}

Entity::Entity()
{
}

Entity::Entity(Graphics & graphics, const std::string filePath, float posX, float posY)
	: AnimatedSprite(graphics, filePath, posX, posY),
	acceleration(Vector2()), velocity(Vector2())
{
}

Entity::~Entity()
{
}

void Entity::moveLeft()
{
	//base class should probably define the movement characteristics, not the animation, maybe it doesn't have one?
	//testing this out
	float _xAcceleration = this->acceleration.x - .001f;
	this->acceleration.x = std::max(-entity_constants::WALK_SPEED, _xAcceleration);
	this->_facing = LEFT;
}

void Entity::moveRight()
{
	float _xAcceleration = this->acceleration.x + .001f;
	this->acceleration.x = std::min(entity_constants::WALK_SPEED, _xAcceleration);
	this->_facing = RIGHT;
}

void Entity::moveUp()
{
	float _yAcceleration = this->acceleration.x - .001f;
	this->acceleration.y = std::min(entity_constants::WALK_SPEED, _yAcceleration);
	this->_facing = UP;
}

void Entity::moveDown()
{
	float _yAcceleration = this->acceleration.x + .001f;
	this->acceleration.y = std::min(entity_constants::WALK_SPEED, _yAcceleration);
	this->_facing = DOWN;
}

void Entity::update(int elapsedTime)
{
	this->_oldPosition = Vector2(this->_x, this->_y);

	//this should update the position since this class contains the veloctiy and all that jazz
	//move the player
	this->velocity.x = this->acceleration.x * elapsedTime;
	this->_x += this->velocity.x * elapsedTime;
	this->velocity.y = this->acceleration.y * elapsedTime;
	this->_y += this->velocity.y * elapsedTime;

	AnimatedSprite::update(elapsedTime);
}

Vector2 Entity::oldPosition()
{
	return this->_oldPosition;
}
