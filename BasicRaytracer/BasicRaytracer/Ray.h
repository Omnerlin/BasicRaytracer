#pragma once
#include "Vect.h"

class Ray {
private:
	Vect origin, direction;

public:
	Ray(): origin(Vect(0,0,0)), direction(Vect(1,0,0)) {}
	Ray(Vect origin, Vect direction) : origin(origin), direction(direction) {}

	Vect getOrigin() { return origin; }
	Vect getDirection() { return direction; }
};