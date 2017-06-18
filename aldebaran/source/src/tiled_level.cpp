#include <SDL.h>
#include "tiled_level.h"
#include "graphics.h"
#include <vector>

Tiled_Level::Tiled_Level() {}

Tiled_Level::Tiled_Level(std::string mapName,Graphics &graphics) :
	_mapName(mapName),
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

	//get the basics of the tiled name
	int width, height, tilewidth, tileheight;
	mapElement->QueryIntAttribute("width", &width);
	mapElement->QueryIntAttribute("height", &height);
	mapElement->QueryIntAttribute("tilewidth", &tilewidth);
	mapElement->QueryIntAttribute("tileheight", &tileheight);

	this->_size = Vector2(width, height);
	this->_tilesize = Vector2(tilewidth, tileheight);

	if (mapElement != nullptr) {

		//this is getting all the tileset elements
		tinyxml2::XMLElement* tilesetElement = mapElement->FirstChildElement("tileset");
		int tileoffset = 0;
		while (tilesetElement != nullptr) {
			int outFirstgid, outTilewidth, outTileheight, outTilecount, outColumns, _outTilesetwidth, _outTilesetheight;
			std::string outName;
			std::string outSource;
			tilesetElement->QueryIntAttribute("firstgid", &outFirstgid);
			tilesetElement->QueryIntAttribute("tilewidth", &outTilewidth);
			tilesetElement->QueryIntAttribute("tileheight", &outTileheight);
			tilesetElement->QueryIntAttribute("tilecount", &outTilecount);
			tilesetElement->QueryIntAttribute("columns", &outColumns);
			outName = tilesetElement->Attribute("name");
			
			
			tinyxml2::XMLElement * imageElement = tilesetElement->FirstChildElement("image");
			if (imageElement != nullptr) {
				outSource = imageElement->Attribute("source");
				imageElement->QueryIntAttribute("width", &_outTilesetwidth);
				imageElement->QueryIntAttribute("height", &_outTilesetheight);
			}

			//constructor will do all the loading as well
			Tiled_Tileset * tileset = new Tiled_Tileset(graphics, outSource, outFirstgid, outTilewidth, outTileheight, outTilecount, outColumns, outName, tileoffset, _outTilesetwidth, _outTilesetheight);
			
			//co-routine to get all the tile properties
			tinyxml2::XMLElement * tileElement = tilesetElement->FirstChildElement("tile");
			while (tileElement != nullptr) {
				int id;
				//get the local id of the tile with additional properties
				tileElement->QueryIntAttribute("id", &id);
				
				//lets see if this tile has animation properties
				tinyxml2::XMLElement * animationElement = tileElement->FirstChildElement("animation");
				if (animationElement != nullptr) {
					tinyxml2::XMLElement * frameElement = animationElement->FirstChildElement("frame");
					while (frameElement != nullptr) {
						int tileid, duration;
						frameElement->QueryIntAttribute("tileid", &tileid);
						frameElement->QueryIntAttribute("duration", &duration);
						frameElement = frameElement->NextSiblingElement("frame");
					
						tileset->addAnimation(id, tileid, duration);
					}
				}
				//get the next tile to process additional properties in the tileset
				tileElement = tileElement->NextSiblingElement("tile");
			}

			//add the tileset to the vector of tilesets
			this->_tilesets.push_back(tileset);
			//update the tileoffset
			tileoffset = tileoffset + outTilecount;
			//get the next tileset
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
		for (Tiled_Tileset * tileset : this->_tilesets) {
			if (tilegid >= tileset->_firstgid && tilegid < (tileset->_firstgid + tileset->_tilecount)) {
				return tileset;
			}
		}
	}
	return nullptr;
}

void Tiled_Level::update(int elapsedTime) {
	//call update on all the tilesets
	for (Tiled_Tileset * tileset : this->_tilesets) {
		tileset->update(elapsedTime);
	}
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
