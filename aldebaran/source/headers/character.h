#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include "entity.h"

class Graphics;

class Character : Entity {
public:
	Character();
	Character(Graphics & graphics, const std::string filePath, float posX, float posY);
	~Character();
protected:
private:

	// Inherited via Entity
	virtual void animationDone(std::string currentAnimation) override;
	virtual void setupAnimation() override;
};
#endif // !CHARACTER_H
