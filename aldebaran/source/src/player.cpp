#include <algorithm>
#include "player.h"
#include "graphics.h"


namespace player_constants {
	const float WALK_SPEED = 0.2f;
}

Player::Player() {}

Player::Player(Graphics &graphics, float x, float y) : AnimatedSprite(graphics, "content/sprites/gorksprite.png", 0, 0, 16, 16, x, y, 3, 100), _dx(0), _dy(0), _ax(), _ay(0) {
	//not sure this is necessary
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
	//this->_dx = -player_constants::WALK_SPEED;

	//testing this out
	float newAx = this->_ax - .001f;
	this->_ax = std::min(-player_constants::WALK_SPEED, newAx);
	
	
	
	this->playAnimation("walk_left");
	this->_facing = LEFT;
}

void Player::moveRight() {
	//this->_dx = player_constants::WALK_SPEED;
	

	//testing this out
	float newAx = this->_ax + .001f;
	this->_ax = std::min(player_constants::WALK_SPEED, newAx);


	
	this->_ax += .001f;
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

void Player::applyGravity()
{
	//TODO: Tweak this, not sure if this is a real thing we are going to do
	this->_dy = player_constants::WALK_SPEED;
}

void Player::stopDeltaX()
{
	this->_dx = 0;
}

void Player::stopDeltaY()
{
	this->_dy = 0;
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

BoundingBox Player::nextMove(float elapsedTime)
{
	float nextX = this->_x + (this->_dx * elapsedTime);
	float nextY = this->_y + (this->_dy * elapsedTime);
	SDL_Rect nextDestRect = { nextX, nextY, this->_sourceRect.w * this->_scale, this->_sourceRect.h * this->_scale };
	BoundingBox bbox = BoundingBox(nextDestRect);
	return bbox;
}

void Player::update(float elapsedTime) {
	//move by dx
	
	//update velocity
	this->_dx += this->_ax * elapsedTime;
	this->_dy += this->_ay * elapsedTime;
	
	this->_x += this->_dx * elapsedTime;
	this->_y += this->_dy * elapsedTime;
	AnimatedSprite::update(elapsedTime);
}

void Player::draw(Graphics &graphics) {
	AnimatedSprite::draw(graphics);
}