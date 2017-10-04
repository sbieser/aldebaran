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
	virtual void moveLeft();

	/// <summary>
	/// Moves the player right by dx
	/// </summary>
	virtual void moveRight();

	/// <summary>
	/// Moves the player up by dy
	/// </summary>
	virtual void moveUp();

	/// <summary>
	/// Moves the player down by dy
	/// </summary>
	virtual void moveDown();
	
	/// <summary>
	/// Updates the animated sprite with a timer
	/// </summary>
	/// <param name="elapsedTime">The elapsed time.</param>
	virtual void update(int elapsedTime) = 0;

protected:
private:	
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
};
#endif // !ENTITY_H
