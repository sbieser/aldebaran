#ifndef LAYER_H
#define LAYER_H

#include <string>

class Graphics;
class Sprite;

/// <summary>
/// Meant more for the parallax scrolling stuff, lets keep this seperated from the scrolling
// background stuff.Currently doesn't seem right for them to be a part of each other...
/// </summary>
class Layer {
public:
	Layer();
	Layer(Graphics &graphics, const std::string &filePath, float posX, float posY, int destWidth, int destHeight);
	~Layer();
	void draw(Graphics &graphics);
protected:
private:
	int _destWidth;
	int _destHeight;
	Sprite * _sprite;
};
#endif // !LAYER_H
