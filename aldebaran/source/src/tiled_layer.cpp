#include "..\headers\tiled_layer.h"

Tiled_Layer::Tiled_Layer()
{
}

Tiled_Layer::Tiled_Layer(int width, int height, std::string name, std::string data) : _width(width), _height(height), _name(name)
{
	//Now need to take the data and convert to std::vector<std::vector<int>>

}
