#ifndef CIRCLE_H
#define CIRCLE_H

class Circle {
public:	
	/// <summary>
	/// Default constructor of the <see cref="Circle"/> class.
	/// </summary>
	Circle();
	Circle(float radius, float x, float y);
	~Circle();
	bool checkCollision(Circle circle);
	float radius;
	float x;
	float y;
protected:
private:
};
#endif // !CIRCLE_H
