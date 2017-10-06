#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include "animated_sprite.h"
#include "vector_2.h"

class Graphics;

class Entity : public AnimatedSprite {
public:
	Entity();
	Entity(Graphics & graphics, const std::string filePath, float posX, float posY);
	~Entity();

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
	/// Applies the gravity to the player
	/// </summary>
	void applyGravity(int elapsedTime);

	/// <summary>
	/// Updates the animated sprite with a timer
	/// </summary>
	/// <param name="elapsedTime">The elapsed time.</param>
	void update(int elapsedTime);

protected:
	/// <summary>
	/// The entity acceleration
	/// </summary>
	Vector2 _acceleration;

	/// <summary>
	/// The entity velocity
	/// </summary>
	Vector2 _velocity;

	/// <summary>
	/// Direction the entity is facing
	/// </summary>
	Direction _facing;

	/// <summary>
	/// Determines if the player has jumped
	/// </summary>
	bool _jumped;
	double _jumpTime;
	double _jumpTimeElapsed;
private:	
};
#endif // !ENTITY_H
