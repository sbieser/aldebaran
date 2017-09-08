#include <math.h>
#include "circle.h"

Circle::Circle( )
{
}

Circle::Circle(float radius, float x, float y) : radius(radius), x(x), y(y)
{
}

Circle::~Circle()
{
}

bool Circle::checkCollision(Circle circle)
{
	//return false;
	float r = this->radius + circle.radius;
	r *= r;
	return r < pow(this->x + circle.x, 2) + pow(this->y + circle.y, 2);
}
