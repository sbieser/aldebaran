#ifndef TILED_TILESET_H
#define TILED_TILESET_H

#include <string>

struct SDL_Texture;

class Tiled_Tileset {
public:
	//Tiled_Tileset();
	//don't know what else there should be
private:
	int _firstgid;
	int _tilewidth;
	int _tileheight;
	int _tilecount;
	int _columns;
	std::string _name;
	std::string _source;
	SDL_Texture* _sourceTexture;
};

#endif // !TILED_TILESET_H
