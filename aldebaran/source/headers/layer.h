#ifndef LAYER_H
#define LAYER_H

#include <string>

class Graphics;

/// <summary>
/// Meant more for the parallax scrolling stuff, lets keep this seperated from the scrolling
// background stuff.Currently doesn't seem right for them to be a part of each other...
/// </summary>
class Layer {
public:
	Layer();
	Layer(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height);
	~Layer();
	void draw(Graphics &graphics);
protected:
private:
};
#endif // !LAYER_H
