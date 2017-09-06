#pragma once
#include <math.h>

class Vect {
private:
	double x, y, z;

public:

	// Methods
	double getX() { return x; }
	double getY() { return y; }
	double getZ() { return z; }
	double magnitude();
	Vect normalize();
	Vect negative();
	double dotProduct(Vect v);
	Vect crossProduct(Vect v);
	Vect add(Vect v);
	Vect multiply(double scalar);

	// Constructors
	Vect() : x(0), y(0), z(0) {}
	Vect(double x, double y, double z) : x(x), y(y), z(z) {}
};


