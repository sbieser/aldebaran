#include <SDL.h>
#include "tiled_level.h"
#include "graphics.h"
#include <vector>
#include <algorithm>

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
	tinyxml2::XMLDocument doc;
	
	//path to maps is static, can not be dynamic, not a huge loss
	std::string path = "content/maps/" + mapName;
	tinyxml2::XMLError xmlError = doc.LoadFile(path.c_str());

	if (xmlError != tinyxml2::XML_SUCCESS) {
		printf("Error: %i\n", xmlError);
		return xmlError;
	}

	//map is the root element, we use this to get tilesets and layers
	tinyxml2::XMLElement* mapElement = doc.FirstChildElement("map");
	if (mapElement != nullptr) {

		//this is getting all the tileset elements
		tinyxml2::XMLElement* tilesetElement = mapElement->FirstChildElement("tileset");
		int tileoffset = 0;
		while (tilesetElement != nullptr) {
			int outFirstgid, outTilewidth, outTileheight, outTilecount, outColumns;
			std::string outName;
			std::string outSource;
			tilesetElement->QueryIntAttribute("firstgid", &outFirstgid);
			tilesetElement->QueryIntAttribute("tilewidth", &outTilewidth);
			tilesetElement->QueryIntAttribute("tileheight", &outTileheight);
			tilesetElement->QueryIntAttribute("tilecount", &outTilecount);
			tilesetElement->QueryIntAttribute("columns", &outColumns);
			outName = tilesetElement->Attribute("name");
			
			tinyxml2::XMLElement* imageElement = tilesetElement->FirstChildElement("image");
			if (imageElement != nullptr) {
				outSource = imageElement->Attribute("source");
			}

			Tiled_Tileset *tileset = new Tiled_Tileset(graphics, outSource, outFirstgid, outTilewidth, outTileheight, outTilecount, outColumns, outName, tileoffset);
			this->_tilesets.push_back(tileset);

			//update the tileoffset
			tileoffset = tileoffset + outTilecount;

			tilesetElement = tilesetElement->NextSiblingElement("tileset");
		}

		tinyxml2::XMLElement* layerElement = mapElement->FirstChildElement("layer");
		while (layerElement != nullptr) {
			std::string outName;
			std::string outEncoding;
			std::string outData;
			int outWidth, outHeight;
			layerElement->QueryIntAttribute("width", &outWidth);
			layerElement->QueryIntAttribute("height", &outHeight);
			outName = layerElement->Attribute("name");

			tinyxml2::XMLElement* dataElement = layerElement->FirstChildElement("data");
			if (dataElement != nullptr) {
				outEncoding = dataElement->Attribute("encoding");
				outData = dataElement->GetText();
				printf(outData.c_str());
			}

			Tiled_Layer* layer = new Tiled_Layer(outWidth, outHeight, outName, outEncoding, outData);
			_layers.push_back(layer);

			//do this last
			layerElement = layerElement->NextSiblingElement("layer");
		}
	}
	return xmlError;
}

Tiled_Tileset* Tiled_Level::getTileset(int tilegid)
{
	if (tilegid == 0) {
		return nullptr;
	}
	else {
		for (auto *tileset : this->_tilesets) {
			if (tilegid >= tileset->_firstgid && tilegid < (tileset->_firstgid + tileset->_tilecount)) {
				return tileset;
			}
		}
	}
	return nullptr;
}

void Tiled_Level::update(int elapsedTime) {

}

void Tiled_Level::draw(Graphics &graphics) {
	//For each layer in the tilemap
	for (auto layer : this->_layers) {
		//for each row in the layer
 		for (int row = 0; row < layer->_height; row++) {
			//for each column in the layer
			for (int col = 0; col < layer->_width; col++) {
				//find the tilegid from the layers data
				int tilegid = layer->getTile(row, col);
				//find out which tileset the tilefid belongs to
				Tiled_Tileset* tileset = this->getTileset(tilegid);
				if (tileset != nullptr) {
					//if not nullptr (or 0), then get the source rect from the tileset using the tilegid
					SDL_Rect sourceRect = tileset->getSourceRect(tilegid);
					//get the destination rect, scale by 2 to make the destination bigger
					SDL_Rect destRect = { col * tileset->_tilewidth * 2, row * tileset->_tileheight * 2, tileset->_tilewidth * 2, tileset->_tileheight * 2};
					//blit to the surface
					graphics.blitSurface(tileset->_sourceTexture, &sourceRect, &destRect);
				}
			}
		}
	};
}
