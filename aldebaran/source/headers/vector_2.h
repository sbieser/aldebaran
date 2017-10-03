#ifndef VECTOR_2_H
#define VECTOR_2_H
struct Vector2 {
	float x;
	float y;
	Vector2() : x(0), y(0) {}
	Vector2(int x, int y) : x(x), y(y) {}
	Vector2 zero() {
		return Vector2(0, 0);
	}
};
#endif // !VECTOR_2_H
