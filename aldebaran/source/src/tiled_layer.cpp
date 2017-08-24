#include "tiled_layer.h"
#include <sstream>

Tiled_Layer::Tiled_Layer()
{
}

Tiled_Layer::Tiled_Layer(int width, int height, std::string name, std::string encoding, const std::string &data) : _width(width), _height(height), _name(name), _encoding(encoding)
{
	//Now need to take the data and convert to std::vector<std::vector<int>>
	//use encoding to decide how to parse the data
	if (this->_encoding.compare("csv") == 0) {
		//data is comma separated, so we need to explode data by ','
		std::stringstream ss(data);
		int i;
		while (ss >> i)
		{
			_data.push_back(i);
			if (ss.peek() == ',' || ss.peek() == ' ')
				ss.ignore();
		}
	}
}

int Tiled_Layer::getTile(int row, int col)
{
	//Multiply row by the number of tiles in the width, then add col to get the index.
	//If row is 0, then we are looking at the first row and col is sufficient to be the index.
	int index = row * this->_width + col;
	return this->_data[index];
}

int Tiled_Layer::getTileFromPosition(float x, float y)
{
	//still works!!
	int row = x / 16;
	int col = y / 16;
	return this->getTile(row, col);
}

