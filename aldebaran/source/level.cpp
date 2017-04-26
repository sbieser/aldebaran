#include <SDL.h>
#include "level.h"
#include "graphics.h"

Level::Level() {}

Level::Level(std::string mapName, Vector2 spwanPoint, Graphics &graphics) :
	_mapName(mapName),
	_spwanPoint(spwanPoint),
	_size(Vector2(0, 0)) {
	this->loadMap(mapName, graphics);
}

Level::~Level() {


}

void Level::loadMap(std::string mapName, Graphics &graphics) {
	//TMP LOAD BACKGROUND
	this->_backgroundTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage("content/backgrounds/bkBlue.png"));
	this->_size = Vector2(1280, 960);
}

void Level::update(int elapsedTime) {

}

void Level::draw(Graphics &graphics) {
	SDL_Rect sourceRect = { 0, 0, 64, 64 };
	SDL_Rect destRect = { 0, 0, 64, 64 };

	for (int x = 0; x < this->_size.x / 64; x++) {
		for (int y = 0; y < this->_size.y / 64; y++) {
			destRect.x = x * 64;
			destRect.y = y * 64;
			//destRect.h = 64;
			//destRect.w = 64;
			graphics.blitSurface(this->_backgroundTexture, &sourceRect, &destRect);
		}
	}
}
