#include <algorithm>
#include "player.h"
#include "graphics.h"


namespace player_constants {
	const float WALK_SPEED = 0.1f;
}

Player::Player() {}

Player::Player(Graphics &graphics, float x, float y) 
	//: AnimatedSprite(graphics, "content/sprites/gorksprite.png", 0, 0, 16, 16, x, y, 3, 100), 
	: AnimatedSprite(graphics, "content/sprites/gorksprite.png", x, y),
	_dx(0), _dy(0), _ax(0), _ay(0), _jumped(false), _jumpTime(300), _jumpTimeElapsed(0) {
	//not sure this is necessary
	this->setupAnimation();
	this->playAnimation("idle_front");
}

void Player::setupAnimation() {
	this->addAnimation(3, 16, 0, "walk_front", 16, 16);
	this->addAnimation(1, 0, 0, "idle_front", 16, 16);
	
	this->addAnimation(3, 16, 16, "walk_left", 16, 16);
	this->addAnimation(1, 0, 16, "idle_left", 16, 16);

	this->addAnimation(3, 16, 32, "walk_right", 16, 16);
	this->addAnimation(1, 0, 32, "idle_right", 16, 16);

	this->addAnimation(3, 16, 48, "walk_back", 16, 16);
	this->addAnimation(1, 0, 48, "idle_back", 16, 16);
}

void Player::animationDone(std::string currentAnimation) {

}

void Player::moveLeft() {
	//this->_dx = -player_constants::WALK_SPEED;

	//testing this out
	float newAx = this->_ax - .001f;
	this->_ax = std::max(-player_constants::WALK_SPEED, newAx);
	
	this->playAnimation("walk_left");
	this->_facing = LEFT;
}

void Player::moveRight() {
	//this->_dx = player_constants::WALK_SPEED;
	

	//testing this out
	float newAx = this->_ax + .001f;
	this->_ax = std::min(player_constants::WALK_SPEED, newAx);

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

void Player::jump()
{
	this->_jumped = true;
}

void Player::stopMoving() {
	//this->_dx = 0;
	//this->_dy = 0;

	//TESTING
	if (this->_dx < 0) {
		float newAx = this->_ax + .001f;
		if (newAx >= 0) {
			newAx = 0;
		}
		this->_ax = newAx;
	}
	else if (this->_dx > 0) {
		float newAx = this->_ax - .001f;
		if (newAx <= 0) {
			newAx = 0;
		}
		this->_ax = newAx;
	}
	else {
		this->_ax = 0;
	}

	//chang the facing animation
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

void Player::applyGravity(int elapsedTime)
{
	float newAy = 0.0f;
	if (this->_jumped) {
		this->_jumpTimeElapsed += elapsedTime;
		if (this->_jumpTimeElapsed > this->_jumpTime) {
			this->_jumped = false;
			this->_jumpTimeElapsed = 0;
		}
		
		newAy = this->_ay - .001f;
		this->_ay = newAy;
	}
	else {
		//testing this out
		newAy = this->_ay + .001f; //means we are heading down, if we - .001f, we will head up!
		this->_ay = std::min(player_constants::WALK_SPEED, newAy);
	}
	//SDL_Log("applyGravity::this->_ay: %f", newAy);
	//this->_ay = newAy;
	
	//TODO: Tweak this, not sure if this is a real thing we are going to do
	//this->_dy = player_constants::WALK_SPEED;
}

void Player::stopDeltaX()
{
	this->_ax = 0;
	this->_dx = 0;
}

void Player::stopDeltaY()
{
	this->_ay = 0;
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

BoundingBox Player::nextMove(int elapsedTime)
{		
	//float nextX = this->_x + (this->_dx * elapsedTime);
	//float nextY = this->_y + (this->_dy * elapsedTime);
	
	//this anticpates the next move with acceleration
	float nextDx = this->_ax * elapsedTime;
	float nextX = this->_x + (nextDx * elapsedTime);

	float nextDy = this->_ay * elapsedTime;
	float nextY = this->_y + (nextDy * elapsedTime);

	SDL_Rect nextDestRect = { nextX, nextY, this->_sourceRect.w * this->_scale, this->_sourceRect.h * this->_scale };
	BoundingBox bbox = BoundingBox(nextDestRect);
	return bbox;
}

BoundingBox Player::nextMoveX(int elapsedTime)
{
	//this anticpates the next move with acceleration
	float nextDx = this->_ax * elapsedTime;
	float nextX = this->_x + (nextDx * elapsedTime);

	SDL_Rect nextDestRect = { nextX, this->_y, this->_sourceRect.w * this->_scale, this->_sourceRect.h * this->_scale };
	BoundingBox bbox = BoundingBox(nextDestRect);
	return bbox;
}

BoundingBox Player::nextMoveX(int elapsedTime, SDL_Rect * camera)
{
	//this anticpates the next move with acceleration
	float nextDx = this->_ax * elapsedTime;
	float nextX = this->_x + (nextDx * elapsedTime);

	SDL_Rect nextDestRect = { nextX - camera->x, this->_y, this->_sourceRect.w * this->_scale, this->_sourceRect.h * this->_scale };
	BoundingBox bbox = BoundingBox(nextDestRect);
	return bbox;
}

BoundingBox Player::nextMoveY(int elapsedTime)
{
	//this anticpates the next move with acceleration
	float nextDy = this->_ay * elapsedTime;
	float nextY = this->_y + (nextDy * elapsedTime);

	SDL_Rect nextDestRect = { this->_x, nextY, this->_sourceRect.w * this->_scale, this->_sourceRect.h * this->_scale };
	BoundingBox bbox = BoundingBox(nextDestRect);
	return bbox;
}

BoundingBox Player::nextMoveY(int elapsedTime, SDL_Rect * camera)
{
	//this anticpates the next move with acceleration
	float nextDy = this->_ay * elapsedTime;
	float nextY = this->_y + (nextDy * elapsedTime);

	SDL_Rect nextDestRect = { this->_x, nextY - camera->y, this->_sourceRect.w * this->_scale, this->_sourceRect.h * this->_scale };
	BoundingBox bbox = BoundingBox(nextDestRect);
	return bbox;
}

int Player::getX()
{
	return this->_x;
}

int Player::getY()
{
	return this->_y;
}

void Player::update(int elapsedTime) {

	//move by dx	
	this->_dx = this->_ax * elapsedTime;
	this->_dy = this->_ay * elapsedTime;

	this->_x += this->_dx * elapsedTime;
	this->_y += this->_dy * elapsedTime;
	AnimatedSprite::update(elapsedTime);
}

void Player::draw(Graphics &graphics) {
	AnimatedSprite::draw(graphics);
}

void Player::draw(Graphics & graphics, SDL_Rect * camera)
{
	AnimatedSprite::draw(graphics, camera);
}
