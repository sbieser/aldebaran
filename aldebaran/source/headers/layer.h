#ifndef LAYER_H
#define LAYER_H

#include <string>

class Graphics;
class Sprite;
struct SDL_Rect;

/// <summary>
/// Meant more for the parallax scrolling stuff, lets keep this seperated from the scrolling
// background stuff.Currently doesn't seem right for them to be a part of each other...
/// </summary>
class Layer {
public:
	Layer();
	Layer(Graphics & graphics, const std::string & filePath, float posX, float posY, int destWidth, int destHeight);
	~Layer();
	void draw(Graphics & graphics);
	void update(SDL_Rect * camera);
protected:
private:
	int _destWidth;
	int _destHeight;
	int _x;
	int _lastCameraX;
	Sprite * _sprite;
};
#endif // !LAYER_H
