#include "player.h"
#include "graphics.h"

namespace player_constants {
	const float WALK_SPEED = 0.2f;
}

Player::Player() {}

//AnimatedSprite::AnimatedSprite(Graphics & graphics, const std::string & filePath, int sourceX, int sourceY, int width, int height, float posX, float posY, float scale, float timeToUpdate) :
Player::Player(Graphics &graphics, float x, float y) : AnimatedSprite(graphics, "content/sprites/gorksprite.png", 0, 0, 16, 16, x, y, 3, 100), _dx(0), _dy(0) {
	//not sure this is necessary
	//graphics.loadImage("content/sprites/gorksprite.png");

	this->setupAnimation();
	this->playAnimation("idle_front");
}

void Player::setupAnimation() {
	this->addAnimation(3, 16, 0, "walk_front", 16, 16, Vector2(0, 0));
	this->addAnimation(1, 0, 0, "idle_front", 16, 16, Vector2(0, 0));
	
	this->addAnimation(3, 16, 16, "walk_left", 16, 16, Vector2(0, 0));
	this->addAnimation(1, 0, 16, "idle_left", 16, 16, Vector2(0, 0));

	this->addAnimation(3, 16, 32, "walk_right", 16, 16, Vector2(0, 0));
	this->addAnimation(1, 0, 32, "idle_right", 16, 16, Vector2(0, 0));

	this->addAnimation(3, 16, 48, "walk_back", 16, 16, Vector2(0, 0));
	this->addAnimation(1, 0, 48, "idle_back", 16, 16, Vector2(0, 0));
}

void Player::animationDone(std::string currentAnimation) {

}

void Player::moveLeft() {
	this->_dx = -player_constants::WALK_SPEED;
	this->playAnimation("walk_left");
	this->_facing = LEFT;
}

void Player::moveRight() {
	this->_dx = player_constants::WALK_SPEED;
	this->playAnimation("walk_right");
	this->_facing = RIGHT;
}

void Player::moveUp()
{
	this->_dy = -player_constants::WALK_SPEED;
	this->_facing = UP;
}

void Player::moveDown()
{
	this->_dy = player_constants::WALK_SPEED;
	this->_facing = DOWN;
}

void Player::stopMoving() {
	this->_dx = 0;
	this->_dy = 0;
	switch (this->_facing) {
		case LEFT: {
			this->playAnimation("idle_left");
			break;
		}
		case RIGHT: {
			this->playAnimation("idle_right");
			break;
		}
		default: {
			this->playAnimation("idle_front");
		}
	}
}

void Player::setXPosition(int x)
{
	this->_dx = 0;
	this->_x = x;
}

void Player::setYPosition(int y)
{
	this->_dy = 0;
	this->_y = y;
}

/*
void Player::setPosition(int x, int y)
{
	this->_dx = 0;
	this->_dy = 0;
	this->_x = x;
	this->_y = y;
}

void Player::stopDeltaX()
{
	this->_dx = 0;
}

void Player::stopDeltaY()
{
	this->_dy = 0;
}
*/

void Player::update(float elapsedTime) {
	//move by dx
	this->_x += this->_dx * elapsedTime;
	this->_y += this->_dy * elapsedTime;
	AnimatedSprite::update(elapsedTime);
}

void Player::draw(Graphics &graphics) {
	AnimatedSprite::draw(graphics);
}