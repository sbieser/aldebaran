#ifndef LAYER_H
#define LAYER_H

#include <string>

class Graphics;
class Sprite;
struct SDL_Rect;

/// <summary>
/// TODO: Probably need some way to specify what the transparency pixel is, if there exist one.
/// TODO: how to scroll image with camera in the y direction?
/// TODO: Should probably understand why x as float works but int does not
/// </summary>
class Layer {
public:
	Layer();
	
	/// <summary>
	/// Initializes a new instance of the <see cref="Layer"/> class.
	/// </summary>
	/// <param name="graphics">The graphics.</param>
	/// <param name="filePath">The file path.</param>
	/// <param name="destWidth">Width of the dest.</param>
	/// <param name="destHeight">Height of the dest.</param>
	/// <param name="rate">The rate.</param>
	Layer(Graphics & graphics, const std::string & filePath, int destWidth, int destHeight, float rate);
	~Layer();
	void draw(Graphics & graphics, SDL_Rect * camera);
	void update(SDL_Rect * camera);
protected:
private:
	int _destWidth;
	int _destHeight;
	float _x;
	float _y;
	float _rate;
	float _lastCameraX;
	float _lastCameraY;
	Sprite * _sprite;
};
#endif // !LAYER_H
