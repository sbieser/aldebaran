#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <string>
#include "sprite.h"

class Graphics;

class Background : public Sprite {
public:
	Background();
	Background(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int sourceWidth, int sourceHeight, int destWidth, int destHeight, int timeToScroll);
	~Background();
	void update(int elapsedTime);
	void draw(Graphics &graphics);
protected:
private:
	int _scrollingOffset;
	int _timeToScroll;
	int _timeElapsed;
	int _destWidth;
	int _destHeight;
};
#endif // !BACKGROUND_H