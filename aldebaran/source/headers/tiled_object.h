#ifndef TILED_OBJECT_H
#define TILED_OBJECT_H

#include <vector>
#include "vector_2.h"

/// 
/// The types of collisions include:
/// Rectangle:
/// <objectgroup draworder="index">
///		<object id = "8" x = "0" y = "0" width = "16" height = "16" / >
///	< / objectgroup>
///
/// Ellipse:
/// <objectgroup draworder="index">
///		<object id = "9" x = "0" y = "0" width = "16" height = "16">
///			<ellipse / >
///		< / object>
///	< / objectgroup>
///
/// Triangle:
///	<objectgroup draworder = "index">
///		<object id = "10" x = "0" y = "0">
///			<polygon points = "0,0 16,16 0,16" / >
///		< / object>
///	< / objectgroup>
///
/// Polyline:
/// <objectgroup draworder="index">
///		<object id = "11" x = "0" y = "0">
///			<polyline points = "0,0 10,1 11,5 15,5 15,12" / >
///		< / object>
///	< / objectgroup>
/// NOTE: Does not need to be a closed polyline, not sure how useful this would be.
/// NOTE: Each tile can have any number of collision objects
/// NOTE: Triangle is a polyline that is closed
/// NOTE: Maybe use an enumerator for the type, rectangle, ellipse, triangle, polyline

enum shapes { RECTANGLE, ELLIPSE, TRIANGLE, POLYLINE };

class Tiled_Object {
public:
	//how do we load in the objects?
	Tiled_Object(shapes type, int x, int y, int width, int height);
	Tiled_Object(shapes type, int x, int y, int width, int height, std::string points);
	~Tiled_Object();
protected:
private:
	int _x;
	int _y;
	int _width;
	int _height;
	int _id;
	shapes _type;
	std::vector<Vector2> _points;
};
#endif // !TILED_OBJECT_H

