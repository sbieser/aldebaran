#include <SDL.h>
#include "tiled_level.h"
#include "graphics.h"
//#include "tinyxml2.h"
#include <vector>

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != tinyxml2::XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

Tiled_Level::Tiled_Level() {}

Tiled_Level::Tiled_Level(std::string mapName, Vector2 spwanPoint, Graphics &graphics) :
	_mapName(mapName),
	_spwanPoint(spwanPoint),
	_size(Vector2(0, 0)) {
	this->loadMap(mapName, graphics);
}

Tiled_Level::~Tiled_Level() {


}

tinyxml2::XMLError Tiled_Level::loadMap(std::string mapName, Graphics &graphics) {
	//TMP LOAD BACKGROUND
	//this->_backgroundTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage("content/backgrounds/bkBlue.png"));
	//this->_size = Vector2(1280, 960);

	tinyxml2::XMLDocument doc;
	std::string path = "content/maps/" + mapName;
	printf("HELLO");
	tinyxml2::XMLError xmlError = doc.LoadFile(path.c_str());
	XMLCheckResult(xmlError);
	//tinyxml2::XMLNode* pRoot = doc.FirstChild();

	
	tinyxml2::XMLElement* mapElement = doc.FirstChildElement("map");
	if (mapElement != nullptr) {
		
		
		//this is getting all the tileset elements
		tinyxml2::XMLElement* tilesetElement = mapElement->FirstChildElement("tileset");
		while (tilesetElement != nullptr) {
			tilesetElement = tilesetElement->NextSiblingElement("tileset");
		
		}

		//TODO: Get all the layers as well
	}


}

void Tiled_Level::update(int elapsedTime) {

}

void Tiled_Level::draw(Graphics &graphics) {
	SDL_Rect sourceRect = { 0, 0, 64, 64 };
	SDL_Rect destRect = { 0, 0, 64 * 2, 64 * 2 };

	for (int x = 0; x < this->_size.x / 64; x++) {
		for (int y = 0; y < this->_size.y / 64; y++) {
			destRect.x = x * 64 * 2;
			destRect.y = y * 64 * 2;
			//destRect.h = 64;
			//destRect.w = 64;
			graphics.blitSurface(this->_backgroundTexture, &sourceRect, &destRect);
		}
	}
}
