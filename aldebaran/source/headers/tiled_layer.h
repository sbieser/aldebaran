#ifndef TILED_LAYER_H
#define TILED_LAYER_H

#include <string>
#include <vector>

/// <summary>
/// Represents a layer in a tiled map. Layers have a name, width, and height. Additionally they have
/// the data composing the layer, which is a series of comma separated tilegids. A tilegid corresponds
/// to a tile in a tileset. A tilegid of 0 denotes a blank tile, not to be rendered. The data from a
/// layer is going to be stored in a single vector of ints. Consider the following data which is a
///	4 x 2 layer:
///
/// [0][0][1][0]
/// [0][2][1][2]
///
/// Would be transposed to an array like so:
///
/// [0][0][1][0] [0][2][1][2]
///
/// </summary>
class Tiled_Layer {
public:
	Tiled_Layer();
	Tiled_Layer(int width, int height, std::string name, std::string encoding, const std::string &data);
		
	/// <summary>
	/// Gets a tilegid based on a row and col
	/// </summary>
	/// <param name="row">The row.</param>
	/// <param name="col">The col.</param>
	/// <returns></returns>
	int getTile(int row, int col);
	
	/// <summary>
	/// Gets the tilegid from position.
	/// </summary>
	/// <param name="x">The x.</param>
	/// <param name="y">The y.</param>
	/// <returns></returns>
	int getTileFromPosition(float x, float y);
	
	int _width;
	int _height;
private:
	std::string _name;
	std::string _encoding;
	std::vector<int> _data;
};

#endif // !TILED_LAYER_H
