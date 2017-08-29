#ifndef PLAYER_H
#define PLAYER_H

#include "animated_sprite.h"
#include "globals.h"
#include "bounding_box.h";

class Graphics;

//TODO: Gravity should really be some kind of constant that gets updated in the update function, using std::min or something
//TODO: But then to add a jump function that alters the gravity to something else
class Player : public AnimatedSprite {
public:
	Player();
	Player(Graphics &graphics, float x, float y);
	void draw(Graphics &graphics);
	void update(float elapsedTime);

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
	/// Stops moving the player
	/// </summary>
	void stopMoving();
	
	/// <summary>
	/// Applies the gravity to the player
	/// </summary>
	void applyGravity();

	void stopDeltaX();
	void stopDeltaY();
	
	void setXPosition(int x);
	void setYPosition(int y);

	BoundingBox nextMove(float elapsedTime);
	

	/// <summary>
	/// Change in x position during the frame
	/// </summary>
	float _dx;
	/// <summary>
	/// Change in y position during the frame
	/// </summary>
	float _dy;
protected:
private:	
	/// <summary>
	/// Change in x position during the frame
	/// </summary>
	//float _dx;
	
	/// <summary>
	/// Change in y position during the frame
	/// </summary>
	//float _dy;
	
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
