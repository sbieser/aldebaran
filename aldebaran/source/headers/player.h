#ifndef PLAYER_H
#define PLAYER_H

#include "animated_sprite.h"
#include "globals.h"
#include "bounding_box.h";

class Graphics;
class Input;
struct SDL_Rect;

//TODO: Add some kind of method to handle input, so it is not all in the main loop
class Player : public AnimatedSprite {
public:
	Player();
	Player(Graphics & graphics, float x, float y);
	void update(int elapsedTime);

	/// <summary>
	/// Moves the player by -dx
	/// </summary>
	void moveLeft();	

	/// <summary>
	/// Moves the player right by dx
	/// </summary>
	void moveRight();
	
	/// <summary>
	/// Moves the player up by dy
	/// </summary>
	void moveUp();
	
	/// <summary>
	/// Moves the player down by dy
	/// </summary>
	void moveDown();
	
	/// <summary>
	/// Player performs a jump
	/// </summary>
	void jump();
	
	/// <summary>
	/// Stops moving the player
	/// </summary>
	void stopMoving();
	
	/// <summary>
	/// Applies the gravity to the player
	/// </summary>
	void applyGravity(int elapsedTime);

	void stopDeltaX();
	void stopDeltaY();

	BoundingBox nextMoveX(int elapsedTime);
	BoundingBox nextMoveY(int elapsedTime);

	int getX();
	int getY();
	
	void handleInput(Input & input, std::vector<BoundingBox> collidableObjects, int elapsedTime);
protected:
private:
	bool _jumped;
	double _jumpTime;
	double _jumpTimeElapsed;

	/// <summary>
	/// Change in x position during the frame
	/// </summary>
	float _dx;
	/// <summary>
	/// Change in y position during the frame
	/// </summary>
	float _dy;

	/// <summary>
	/// The x acceleration
	/// </summary>
	float _ax;
	/// <summary>
	/// The y acceleration
	/// </summary>
	float _ay;

	/// <summary>
	/// Direction the player is facing
	/// </summary>
	Direction _facing;

	// Inherited via AnimatedSprite
	virtual void animationDone(std::string currentAnimation) override;

	// Inherited via AnimatedSprite
	virtual void setupAnimation() override;
};

#endif // !PLAYER_H
