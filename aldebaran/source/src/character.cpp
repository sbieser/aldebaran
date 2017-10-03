#include "character.h"

Character::Character()
{
}

Character::Character(Graphics & graphics, const std::string filePath, float posX, float posY)
	: Entity(graphics, filePath, posX, posY)
{
}

Character::~Character()
{
}

void Character::animationDone(std::string currentAnimation)
{
	//no need to do anything here
}

void Character::setupAnimation()
{
	//this->addAnimation(3, 16, 0, "walk_front", 16, 16);
	Entity::addAnimation(3, )
}
