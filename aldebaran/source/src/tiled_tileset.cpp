
#include <SDL.h>
#include "tiled_tileset.h"
#include "graphics.h"

Tiled_Tileset::Tiled_Tileset()
{

}

Tiled_Tileset::Tiled_Tileset(Graphics &graphics, const std::string &filePath, int firstguid, int tilewidth, int tileheight, int tilecount, int columns, std::string name, int tileoffset) : _firstgid(firstguid), _tilewidth(tilewidth), _tileheight(tileheight), _tilecount(tilecount), _columns(columns), _name(name), _tileoffset(tileoffset)
{
	//Can not use the path to find the 
	std::string filename = filePath.substr(filePath.find_last_of("/") + 1);

	//Use the graphics object to load the image to get the source texture
	//Anyway to make use of filePath more directly instead of just asking for the filename and looking into content/tilesets
	//
	this->_sourceTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage("content/tilesets/"+ filename));
}

SDL_Rect Tiled_Tileset::getSourceRect(int tilegid) {
	
	//We subtract the tileoffset from the tilegid because an un-normalized tilegid will produce source rects that extend
	//beyond the boundaries of the source texture
	tilegid = tilegid - _tileoffset;

	//row and col is the tile we are trying to locate
	int row, col;
	//x and y is the position of the source rect
	int x, y;
	//mod is needed to calculate the position of the column if not in the first row or not the right most edge tiles
	int mod;

	//Can quick determine if tilegid is in the first row by comparing with the max number of columns
	if (tilegid < this->_columns) {
		//We are in the first row, we subtract 1 because while the tileset is 1 indexed, to get the source rect we use 0 based indexes.
		col = tilegid - 1;
		x = col * this->_tilewidth;
		y = 0;
	}
	else {
		//else in rows after the first
		mod = tilegid % this->_columns;
		if (mod == 0) {
			//then tilegid lies on the right most edge of the tileset
			row = (tilegid / this->_columns) - 1;
			col = this->_columns - 1;
			x = col * this->_tilewidth;
			y = row * this->_tileheight;
		}
		else {
			row = tilegid / this->_columns;
			col = mod - 1;
			x = col * this->_tilewidth;
			y = row * this->_tileheight;
		}
	}

	SDL_Rect sourceRect;
	sourceRect.h = this->_tileheight;
	sourceRect.w = this->_tilewidth;
	sourceRect.x = x;
	sourceRect.y = y;

	return sourceRect;
}