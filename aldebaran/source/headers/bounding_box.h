#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include <SDL.h>
#include "vector_2.h"

class BoundingBox {
public:
	BoundingBox();
	BoundingBox(SDL_Rect destRect);
	~BoundingBox();
	bool checkCollision(BoundingBox bbox);
	Vector2 center();
	int top;
	int bottom;
	int left;
	int right;
	SDL_Rect destRect;
protected:
private:
};


#endif // !BOUNDING_BOX_H
