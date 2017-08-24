#include "bounding_box.h"

BoundingBox::BoundingBox()
{
}

BoundingBox::BoundingBox(SDL_Rect destRect) : _destRect(destRect)
{	
	this->top = this->_destRect.x;
	this->bottom = this->_destRect.x + this->_destRect.h;
	this->left = this->_destRect.y;
	this->right = this->_destRect.y + this->_destRect.w;
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
	if (this->left > -bbox.right) {
		return false;
	}
	return true;
}
