#include <algorithm>
#include "player.h"
#include "graphics.h"
#include "input.h"

namespace player_constants {
	const float WALK_SPEED = 0.03f;
}

Player::Player() {}

Player::Player(Graphics &graphics, float x, float y) 
	: AnimatedSprite(graphics, "content/sprites/gorksprite.png", x, y),
	_dx(0), _dy(0), _ax(0), _ay(0), _jumped(false), _jumpTime(300), _jumpTimeElapsed(0), _canJump(false) {
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
	//nothing yet
}

void Player::moveLeft() {
	//testing this out
	float newAx = this->_ax - .001f;
	this->_ax = std::max(-player_constants::WALK_SPEED, newAx);
	
	this->playAnimation("walk_left");
	this->_facing = LEFT;
}

void Player::moveRight() {
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
	float _accelerationY = 0.0f;
	if (this->_jumped) {
		//We have jumped, subtract gravity instead to head upwards
		this->_jumpTimeElapsed += elapsedTime;
		if (this->_jumpTimeElapsed > this->_jumpTime) {
			this->_jumped = false;
			this->_jumpTimeElapsed = 0;
		}	
		_accelerationY = this->_ay - .001f;
		this->_ay = _accelerationY;
	}
	else {
		//otherwise apply gravity downwards
		_accelerationY = this->_ay + .001f; //means we are heading down, if we - .001f, we will head up!
		this->_ay = std::min(player_constants::WALK_SPEED, _accelerationY);
	}
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

BoundingBox Player::nextMoveX(int elapsedTime)
{
	//this anticpates the next move with acceleration
	float nextDx = this->_ax * elapsedTime;
	float nextX = this->_x + (nextDx * elapsedTime);

	SDL_Rect nextDestRect = { nextX, this->_y, this->_sourceRect.w * this->_scale, this->_sourceRect.h * this->_scale };
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

int Player::getX()
{
	return this->_x;
}

int Player::getY()
{
	return this->_y;
}

float Player::getAccelerationY()
{
	return this->_ay;
}

void Player::setAccelerationY(float accelerationY)
{
	this->_ay = accelerationY;
}

Vector2 Player::getOldPosition()
{
	return this->_oldPosition;

}

//TODO: no way for me to tell what objects these collidable objects belong to, how do I 'kill' another game entity??
void Player::handleInput(Input & input /*, std::vector<BoundingBox> collidableObjects, int elapsedTime*/)
{
	if (input.isKeyHeld(SDL_SCANCODE_LEFT) == true) {
		this->moveLeft();
	}
	else if (input.isKeyHeld(SDL_SCANCODE_RIGHT) == true) {
		this->moveRight();
	}
	else {
		this->stopMoving();
	}
	if (input.wasKeyPressed(SDL_SCANCODE_SPACE) == true && this->_canJump) {
		//how do we affect gravity!
		this->_canJump = false;
		this->setAccelerationY(0.0f);
		this->jump();
	}

	/*
	//check x asix collisions
	BoundingBox xMovedBbox = this->nextMoveX(elapsedTime);
	for (BoundingBox collidableBbox : collidableObjects) {
		if (xMovedBbox.checkCollision(collidableBbox)) {
			this->stopDeltaX();
		}
	}

	//check for collisions on the y axis
	this->applyGravity(elapsedTime);
	BoundingBox yMovedBbox = this->nextMoveY(elapsedTime);
	for (BoundingBox collidableBbox : collidableObjects) {
		if (yMovedBbox.checkCollision(collidableBbox)) {
			this->stopDeltaY();
			float wy = (this->bbox().destRect.w + collidableBbox.destRect.w) * (this->bbox().center().y - collidableBbox.center().y);
			float hx = (this->bbox().destRect.h + collidableBbox.destRect.h) * (this->bbox().center().x - collidableBbox.center().x);

			if (wy > hx) {
				if (wy > -hx) {
					SDL_Log("colliding with top");
				}
				else {
					SDL_Log("colliding with left");
				}
			}
			else {
				if (wy > -hx) {
					SDL_Log("colliding with right");
				}
				else {
					SDL_Log("colliding with bottom");
					//this means we can jump
					this->_canJump = true;
				}
			}
		}
	}*/
}

void Player::update(int elapsedTime) {
	//save the old position, just in case we need to correct for collisions
	this->_oldPosition = Vector2(this->_x, this->_y);

	//move by dx	
	this->_dx = this->_ax * elapsedTime;
	this->_dy = this->_ay * elapsedTime;
	this->_x += this->_dx * elapsedTime;
	this->_y += this->_dy * elapsedTime;
	AnimatedSprite::update(elapsedTime);

	//SDL_Log("Player Acceleration: %f,%f", this->_ax, this->_ay);
	//SDL_Log("Player velocity: %f,%f", this->_dx, this->_dy);

	//elapsedTime is varying depending on how much of the level is drawn! I need to fix my timestep!!!
	//SDL_Log("Player elapsedTime: %d", elapsedTime);
}