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
	_acceleration(Vector2()), _velocity(Vector2())
{
}

Entity::~Entity()
{
}

void Entity::moveLeft()
{
	//base class should probably define the movement characteristics, not the animation, maybe it doesn't have one?
	//testing this out
	float _xAcceleration = this->_acceleration.x - .001f;
	this->_acceleration.x = std::max(-entity_constants::WALK_SPEED, _xAcceleration);
	this->_facing = LEFT;
}

void Entity::moveRight()
{
	float _xAcceleration = this->_acceleration.x + .001f;
	this->_acceleration.x = std::min(entity_constants::WALK_SPEED, _xAcceleration);
	this->_facing = RIGHT;
}

void Entity::moveUp()
{
	float _yAcceleration = this->_acceleration.x - .001f;
	this->_acceleration.y = std::min(entity_constants::WALK_SPEED, _yAcceleration);
	this->_facing = UP;
}

void Entity::moveDown()
{
	float _yAcceleration = this->_acceleration.x + .001f;
	this->_acceleration.y = std::min(entity_constants::WALK_SPEED, _yAcceleration);
	this->_facing = DOWN;
}
