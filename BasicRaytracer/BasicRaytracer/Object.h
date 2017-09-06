#pragma once
#include "Ray.h"
#include "Color.h"

class Object
{
public:
	Color getColor() { return Color(0.0, 0.0, 0.0, 0.0); }

	double findIntersection(Ray ray) {
		return 0;
	}


	Object() {}
};
