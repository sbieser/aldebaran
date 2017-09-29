#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include "animated_sprite.h"

class Graphics;

class Character : AnimatedSprite {
public:
	Character();
	Character(Graphics & graphics, const std::string filePath, float posX, float posY);
	~Character();
protected:
private:
};
#endif // !CHARACTER_H
