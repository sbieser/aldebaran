#ifndef TILED_LAYER_H
#define TILED_LAYER_H

#include <string>
#include <vector>

class Tiled_Layer {
public:
	Tiled_Layer();
	Tiled_Layer(int width, int height, std::string name, std::string data);
private:
	int _width;
	int _height;
	std::string _name;
	std::vector<std::vector<int>> _data;
};

#endif // !TILED_LAYER_H
