#pragma once
#include "Ray.h"
#include "Color.h"

class Object
{
public:
	virtual Color getColor() { return Color(0.0, 0.0, 0.0, 0.0); }

	virtual Vect getNormalAt(Vect point) {
		return Vect();
	}

	virtual double findIntersection(Ray ray) {
		return 0;
	}


	Object() {}
};
