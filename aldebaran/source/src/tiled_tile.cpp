#include "tiled_tile.h"
#include "tiled_frame.h"

Tiled_Tile::Tiled_Tile(SDL_Rect sourceRect, int localid) : _sourceRect(sourceRect), _localid(localid), _frameIndex(0), _hasAnimation(false), collision(false)
{
}

Tiled_Tile::~Tiled_Tile()
{
	//nothing else to do??
}

SDL_Rect Tiled_Tile::getSourceRect()
{
	if (this->_hasAnimation) {
		return this->_animation[this->_frameIndex]->_tile->_sourceRect;
	}
	else {
		return this->_sourceRect;
	}
}

void Tiled_Tile::update(int elapsedTime)
{
	if (this->_hasAnimation) {
		this->_timeElapsed += elapsedTime;
		if (this->_timeElapsed > this->_animation[this->_frameIndex]->_duration) {
			this->_timeElapsed -= this->_animation[this->_frameIndex]->_duration;
			if (this->_frameIndex < this->_animation.size() - 1) {
				this->_frameIndex++;
			}
			else {
				this->_frameIndex = 0;
			}
		}
	}
}

void Tiled_Tile::addAnimation(Tiled_Tile * tile, int duration)
{
	if (!_hasAnimation) {
		//just set that it is going to have an animation if not already set!
		_hasAnimation = true;
	}
	this->_animation.push_back(new Tiled_Frame(tile, duration));
}

void Tiled_Tile::addObject(Tiled_Object * object)
{
	this->_objectGroup.push_back(object);
}
