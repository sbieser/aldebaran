#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include <SDL.h>

class BoundingBox {
public:
	BoundingBox();
	BoundingBox(SDL_Rect destRect);
	~BoundingBox();
	bool checkCollision(BoundingBox bbox);
	int top;
	int bottom;
	int left;
	int right;
	SDL_Rect destRect;
protected:
private:
};


#endif // !BOUNDING_BOX_H
