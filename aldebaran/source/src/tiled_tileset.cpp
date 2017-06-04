#include <SDL.h>
#include "tiled_tileset.h"
#include "tiled_tile.h"
#include "graphics.h"

Tiled_Tileset::Tiled_Tileset()
{

}

Tiled_Tileset::Tiled_Tileset(Graphics &graphics, const std::string &filePath, int firstguid, int tilewidth, int tileheight, int tilecount, int columns, std::string name, int tileoffset, int tilesetwidth, int tilesetheight) : _firstgid(firstguid), _tilewidth(tilewidth), _tileheight(tileheight), _tilecount(tilecount), _columns(columns), _name(name), _tileoffset(tileoffset), _tilesetwidth(tilesetwidth), _tilesetheight(tilesetheight)
{
	//Can not use the path to find the 
	std::string filename = filePath.substr(filePath.find_last_of("/") + 1);

	//Use the graphics object to load the image to get the source texture
	//Anyway to make use of filePath more directly instead of just asking for the filename and looking into content/tilesets
	//
	this->_sourceTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage("content/tilesets/"+ filename));

	//no we need to load up our _localTles vector;
	//was trying to get the width and height of the source texture, it should probably be passed in via tilesetwidth and tilesetheight

	//we have width and height of the tileset, as well as the width and height of the tile
	int rows = this->_tilesetheight / this->_tileheight;
	int cols = this->_tilesetwidth / this->_tilewidth;
	int localCounter = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			SDL_Rect sourceRect;
			sourceRect.x = j * this->_tilewidth;
			sourceRect.y = i * this->_tileheight;
			sourceRect.h = this->_tileheight;
			sourceRect.w = this->_tilewidth;
			_localTiles.push_back(new Tiled_Tile(sourceRect, localCounter));
			localCounter = localCounter + 1;
		}
	}
}

SDL_Rect Tiled_Tileset::getSourceRect(int tilegid) {
	int localid = this->getLocalTileId(tilegid);
	return this->_localTiles[localid]->getSourceRect();
}

int Tiled_Tileset::getLocalTileId(int tilegid)
{
	return tilegid - this->_tileoffset - 1;
}

void Tiled_Tileset::addAnimation(int localid, int animationtileid, int duration)
{
	this->_localTiles[localid]->addAnimation(this->_localTiles[animationtileid], duration);
}

void Tiled_Tileset::update(int elapsedTime)
{
	for (Tiled_Tile *tile : this->_localTiles) {
		tile->update(elapsedTime);
	}
}
