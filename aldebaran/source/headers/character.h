#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include "entity.h"
#include "bounding_box.h";

class Graphics;

class Character : public Entity {
public:
	Character();
	Character(Graphics & graphics, float posX, float posY);
	~Character();

	/// <summary>
	/// Moves the player by -dx
	/// </summary>
	void moveLeft();

	/// <summary>
	/// Moves the player right by dx
	/// </summary>
	void moveRight();

	void update(int elapsedTime, std::vector<BoundingBox> collidableObjects);

protected:
private:

	int _updateTime;
	int _timeElapsed;

	int _randomUpdateTime();

	// Inherited via Entity
	virtual void animationDone(std::string currentAnimation) override;

	virtual void setupAnimation() override;

};
#endif // !CHARACTER_H
