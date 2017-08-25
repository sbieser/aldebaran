#include "bounding_box.h"

BoundingBox::BoundingBox()
{
}

BoundingBox::BoundingBox(SDL_Rect destRect) : destRect(destRect)
{	
	this->top = this->destRect.y;
	this->bottom = this->destRect.y + this->destRect.h;
	this->left = this->destRect.x;
	this->right = this->destRect.x + this->destRect.w;
}

BoundingBox::~BoundingBox()
{
}

bool BoundingBox::checkCollision(BoundingBox bbox)
{
	if (this->bottom <= bbox.top) {
		return false;
	}
	if (this->top >= bbox.bottom) {
		return false;
	}
	if (this->right <= bbox.left) {
		return false;
	}
	if (this->left >= bbox.right) {
		return false;
	}
	return true;
}
