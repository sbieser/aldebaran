#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include "entity.h"

class Graphics;

class Character : public Entity {
public:
	Character();
	Character(Graphics & graphics, float posX, float posY);
	~Character();
protected:
private:

	int _updateTime;
	int _timeElapsed;

	int _randomUpdateTime();

	// Inherited via Entity
	virtual void animationDone(std::string currentAnimation) override;

	virtual void setupAnimation() override;

	virtual void update(int elapsedTime) override;

};
#endif // !CHARACTER_H
