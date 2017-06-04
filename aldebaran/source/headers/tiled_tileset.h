#ifndef TILED_TILESET_H
#define TILED_TILESET_H

#include <string>
#include <vector>

class Graphics;
class Tiled_Tile;
struct SDL_Texture;
struct SDL_Rect;


/// <summary>
/// A class that represents the tileset element of a tiled map, which has the following format;
// <tileset firstgid = "1" name = "prtcave" tilewidth = "16" tileheight = "16" tilecount = "80" columns = "16">
// <image source = "../tilesets/PrtCave.png" width = "256" height = "80" / >
// < / tileset>
// 
// It is worth noting that tilesets tilegids continue to increase after the first tileset. If the first tileset has 80 tiles in it, the
// next tileset will start at tile 81 and continue increasing. This is why a tileoffset is needed to find the source rect.
//
// Also worth noting that tilesets indexes are 1 based, rather than 0. 0 indicates a blank tile in a tile layer. Because of this, many of the
// calcualtions made to find the source rect subtract by one because the source rect will be calculated on 0 based indexes. So consider the following 6x5 tileset:
//
//	[1]		[2]		[3]		[4]		[5]		[6]
//	[7]		[8]		[9]		[10]	[11]	[12]
//	[13]	[14]	[15]	[16]	[17]	[18]
//	[19]	[20]	[21]	[22]	[23]	[24]
//	[25]	[26]	[27]	[28]	[29]	[30]
//
// is transposed to the following table to make determine the right source rect, refering to the upper left hand 
//
//	[0,0]	[1,0]	[2,0]	[3,0]	[4,0]	[5,0]
//	[0,1]	[1,1]	[2,1]	[3,1]	[4,1]	[5,1]
//	[0,2]	[1,2]	[2,2]	[3,2]	[4,3]	[5,2]
//	[0,3]	[1,3]	[2,3]	[3,3]	[4,4]	[5,3]
//	[0,4]	[1,4]	[2,4]	[3,4]	[4,5]	[5,4]
//
/// <summary>
/// 
/// </summary>
class Tiled_Tileset {
public:
	Tiled_Tileset();
	
	/// <summary>
	/// Initializes a new instance of the <see cref="Tiled_Tileset"/> class.
	/// </summary>
	/// <param name="graphics">The graphics.</param>
	/// <param name="filePath">The file path.</param>
	/// <param name="firstguid">The firstguid.</param>
	/// <param name="tilewidth">The tilewidth.</param>
	/// <param name="tileheight">The tileheight.</param>
	/// <param name="tilecount">The tilecount.</param>
	/// <param name="columns">The columns.</param>
	/// <param name="name">The name.</param>
	/// <param name="tileoffset">The tileoffset.</param>
	Tiled_Tileset(Graphics &graphics, const std::string &filePath, int firstguid, int tilewidth, int tileheight, int tilecount, int columns, std::string name, int tileoffset, int tilesetwidth, int tilesetheight);
		
	/// <summary>
	/// Given a tilegid, gets the source rect needed to render this tile
	/// </summary>
	/// <param name="tilegid">The tilegid.</param>
	/// <returns></returns>
	SDL_Rect getSourceRect(int tilegid);
	
	/// <summary>
	/// Gets the local id of the tile, provided the tile global id. The local id, is local to the tileset, where the global id (gid) refers
	/// to an id used to identify the tile from the set of all tiles in a given layer.
	/// </summary>
	/// <param name="tilegid">The tilegid.</param>
	/// <returns></returns>
	int getLocalTileId(int tilegid);

	void addAnimation(int localid, int animationtileid, int duration);

	int _firstgid;
	int _tilewidth;
	int _tileheight;
	int _tilecount;
	int _columns;
	int _rows;
	int _tilesetwidth;
	int _tilesetheight;
	
	/// <summary>
	/// The tileoffset is an offset needed to subtract the tilegid from to get a normalize the tilegid to get a source rect from on the texture
	/// </summary>
	int _tileoffset;
	
	/// <summary>
	/// The source texture of the tileset
	/// </summary>
	SDL_Texture* _sourceTexture;
	
	/// <summary>
	/// Updates the specified elapsed time.
	/// </summary>
	/// <param name="elapsedTime">The elapsed time.</param>
	void update(int elapsedTime);
private:
	std::string _name;
	std::vector<Tiled_Tile*> _localTiles;
};

#endif // !TILED_TILESET_H
