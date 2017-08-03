#include "tiled_object.h"
#include <string>

Tiled_Object::Tiled_Object(shapes type, int x, int y, int width, int height) : _type(type), _x(x), _y(y), _width(width), _height(height)
{

}

Tiled_Object::Tiled_Object(shapes type, int x, int y, int width, int height, std::string pointsString) : Tiled_Object(type, x, y, width, height)
{
	//process the points here!!
	//they will come in like this:
	//"0,0 10,1 11,5 15,5 15,12"
	//points = new std::vector<Vector2*>();

	std::string space_delimiter = " ";
	std::string comma_delimiter = ",";
	size_t pos = 0;
	std::string token;
	
	//std::vector<std::string> tokens;
	while ((pos = pointsString.find(space_delimiter)) != std::string::npos) {
		token = pointsString.substr(0, pos);
		pointsString.erase(0, pos + space_delimiter.length());
		
		//we now we need to take the token and split it even more, or just
		//look at the first and last characters
		size_t comma_pos = token.find(comma_delimiter);
		if (comma_pos != std::string::npos) {
			std::string x_string = token.substr(0, pos);
			std::string y_string = token.substr(pos + 1, (pos + 1) - token.length());
			int x = std::stoi(x_string);
			int y = std::stoi(y_string);
			_points.push_back(Vector2(x, y));
		}
	}
}

Tiled_Object::~Tiled_Object()
{
}
