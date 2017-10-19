#include <SDL.h>
#include <vector>
#include "tiled_level.h"
#include "tiled_object.h"
#include "tiled_tileset.h"
#include "tiled_layer.h"
#include "tiled_tile.h"
#include "graphics.h"
#include "bounding_box.h";

Tiled_Level::Tiled_Level() {}

Tiled_Level::Tiled_Level(std::string mapName,Graphics &graphics) :
	_mapName(mapName),
	_size(Vector2(0, 0)),
	_scale(2) {
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
				//Id of the tile we are adding additional properties to
				int id;
				//get the local id of the tile with additional properties
				tileElement->QueryIntAttribute("id", &id);
				
				//Animation loading code
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

				//something here is causing a bug, skip for now, we found an alternative way to do collisions
				//much simpler
				/*
				tinyxml2::XMLElement * objectgroupElement = tileElement->FirstChildElement("objectgroup");
				if (objectgroupElement != nullptr) {
					tinyxml2::XMLElement * objectElement = objectgroupElement->FirstChildElement("object");
					while (objectElement != nullptr) {

						bool objectFound = false;
						int objectid, x, y;
						shapes shapeType;
						std::string points = "";
						objectElement->QueryIntAttribute("id", &objectid);
						objectElement->QueryIntAttribute("x", &x);
						objectElement->QueryIntAttribute("y", &y);

						//now what kind of object are you??

						tinyxml2::XMLElement * polylineELement = objectElement->FirstChildElement("polyline");
						if (polylineELement != nullptr) {
								///		<object id = "11" x = "0" y = "0">
								///			<polyline points = "0,0 10,1 11,5 15,5 15,12" / >
								///		< / object>

							shapeType = shapes::POLYLINE;
							points = polylineELement->Attribute("points");
							objectFound = true;
						}
						
						tinyxml2::XMLElement * ellipseElement = objectElement->FirstChildElement("ellipse");
						if (ellipseElement != nullptr) {
								///		<object id = "9" x = "0" y = "0" width = "16" height = "16">
								///			<ellipse / >
								///		< / object>
							int width, height;
							shapeType = shapes::ELLIPSE;
							objectElement->QueryIntAttribute("width", &width);
							objectElement->QueryIntAttribute("height", &height);
							objectFound = true;
						}

						tinyxml2::XMLElement * polygonElement = objectElement->FirstChildElement("polygon");
						if (polygonElement != nullptr) {
								///		<object id = "10" x = "0" y = "0">
								///			<polygon points = "0,0 16,16 0,16" / >
								///		< / object>
							shapeType = shapes::TRIANGLE;
							points = polylineELement->Attribute("points");
							objectFound = true;
						}

						if (!objectFound) {
								///		<object id = "8" x = "0" y = "0" width = "16" height = "16" / >
							shapeType = shapes::RECTANGLE;
							int width, height;
							objectElement->QueryIntAttribute("width", &width);
							objectElement->QueryIntAttribute("height", &height);
						}

						if (points.empty()) {
							tileset->addObject(id, new Tiled_Object(shapeType, x, y, width, height));
						}
						else {
							tileset->addObject(id, new Tiled_Object(shapeType, x, y, width, height, points));
						}
						
						//get the next object element
						objectElement = objectElement->NextSiblingElement("object");
					}
				}*/


				//find collidable objects here!!
				tinyxml2::XMLElement * propertiesElement = tileElement->FirstChildElement("properties");
				if (propertiesElement != nullptr) {
					tinyxml2::XMLElement * propertyElement = propertiesElement->FirstChildElement("property");
					while (propertyElement != nullptr) {
					
						//lets find something like a collision tile for now, there might be other important properties but
						//collision is just fine now
						std::string type = propertyElement->Attribute("name");
						if (type.compare("collision") == 0) {
							std::string value = propertyElement->Attribute("value");
							if (value.compare("true") == 0) {
								//should be added to a list of collidable objects or tiles
								tileset->getTile(id)->collision = true;
							}
						}
						//find the next element
						propertyElement = propertyElement->NextSiblingElement("property");
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
			this->_layers.push_back(layer);

			//do this last
			layerElement = layerElement->NextSiblingElement("layer");
		}

		//lets go through all the layers and find all the collidable objects
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
						Tiled_Tile * tile = tileset->getTile(tileset->getLocalTileId(tilegid));
						if (tile->collision) {
							SDL_Rect destRect = { col * tileset->_tilewidth * this->_scale, row * tileset->_tileheight * this->_scale, tileset->_tilewidth * this->_scale, tileset->_tileheight * this->_scale };
							this->_collidableObjects.push_back(BoundingBox(destRect));
							this->_collidableTiles.push_back(destRect);

							//apply the scale later, because we want to test camera offset i suppose :/
							//SDL_Rect optDestRect = { col * tileset->_tilewidth,  row * tileset->_tileheight , tileset->_tilewidth, tileset->_tileheight };
							//this->_optCollidableObjects.push_back(optDestRect);
							
						}
					}
				}
			}
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

/*
bool Tiled_Level::collidesWithPosition(float x, float y)
{
	for (Tiled_Layer * layer : this->_layers) {
		int tilegid = layer->getTileFromPosition(x, y);
		Tiled_Tileset* tileset = this->getTileset(tilegid);
		Tiled_Tile * tile = tileset->getTile(tileset->getLocalTileId(tilegid));
		if (tile->collision) {
			return true;
		}
	}
	return false;
}
*/

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
					SDL_Rect destRect = { col * tileset->_tilewidth * this->_scale, row * tileset->_tileheight * this->_scale, tileset->_tilewidth * this->_scale, tileset->_tileheight * this->_scale };
					//blit to the surface
					graphics.blitSurface(tileset->_sourceTexture, &sourceRect, &destRect);
				}
			}
		}
	}
}

void Tiled_Level::draw(Graphics & graphics, SDL_Rect * camera)
{

	//For each layer in the tilemap
	for (auto layer : this->_layers) {
		//for each row in the layer
		
		int startRow = camera->y / (this->_tilesize.y * this->_scale);
		if (startRow < 0) {
			startRow = 0;
		}
		int startCol = camera->x / (this->_tilesize.x * this->_scale);
		if (startCol < 0) {
			startCol = 0;
		}


		int endRow = (camera->y + camera->h) / (this->_tilesize.y * this->_scale);
		if (endRow > layer->_height) {
			endRow = layer->_height;
		}
			
		int endCol = (camera->x + camera->w) / (this->_tilesize.x * this->_scale);
		if (endCol > layer->_width) {
			endCol = layer->_width;
		}
		
		//int startRow = 0;
		//int endRow = layer->_height;
		//int startCol = 0;
		//int endCol = layer->_width;
		//SDL_Log("startRow: %d, startCol: %d, endRow: %d, endCol: %d", startRow, startCol, endRow, endCol);

		for (int row = startRow; row < endRow; row++) {
			//for each column in the layer
			//for (int col = 0; col < layer->_width; col++) {
			for (int col = startCol; col < endCol; col++) {
				//find the tilegid from the layers data
				int tilegid = layer->getTile(row, col);
				//find out which tileset the tilefid belongs to
				Tiled_Tileset* tileset = this->getTileset(tilegid);
				if (tileset != nullptr) {
					//if not nullptr (or 0), then get the source rect from the tileset using the tilegid
					SDL_Rect sourceRect = tileset->getSourceRect(tilegid);
					//get the destination rect, scale by 2 to make the destination bigger
					
					//sort of works but collision off
					SDL_Rect destRect = { (col * tileset->_tilewidth * this->_scale) - camera->x, (row * tileset->_tileheight * this->_scale) - camera->y, tileset->_tilewidth * this->_scale, tileset->_tileheight * this->_scale };

					//blit to the surface
					graphics.blitSurface(tileset->_sourceTexture, &sourceRect, &destRect);
				}
			}
		}
	}




}
