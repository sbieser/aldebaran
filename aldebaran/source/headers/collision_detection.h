#ifndef COLLISION_DETECTION_H
#define COLLISION_DETECTION_H
namespace collision_detection {
		
	/// <summary>
	/// Sides of a collidable object
	/// </summary>
	enum Side {
		NONE = 0,
		TOP,
		BOTTOM,
		LEFT,
		RIGHT
	};

	/// <summary>
	/// Define the structure to hold the
	/// </summary>
	struct bbox {
		int _top;
		int _bottom;
		int _left;
		int _right;
		bbox(int top, int bottom, int left, int right) : _top(top), _bottom(bottom), _left(left), _right(right) { /*initializes itself*/ }
	};

	bbox boundingBox(int x, int y, int w, int h) {
		return bbox(y, y + h, x, x + w);
	}
	
	bool intersect(bbox a, bbox b) {
		if (a._bottom <= b._top) {
			return false;
		}
		if (a._top >= b._bottom) {
			return false;
		}
		if (a._right <= b._left) {
			return false;
		}
		if (a._left >= b._right) {
			return false;
		}
		return true;
	}
}
#endif // !COLLISION_DETECTION_H
