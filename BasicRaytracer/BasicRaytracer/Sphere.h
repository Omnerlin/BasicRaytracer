#pragma once
#include "Vect.h"
#include "Object.h"

class Sphere : public Object
{
private:
	Vect center;
	double radius;
	Color color;

public:
	Sphere() : center(Vect(0, 0, 0)), radius(1.0), color(Color(0.5, 0.5, 0.5, 0)) {}
	Sphere(Vect center, double radius, Color color) : center(center), radius(radius), color(color) {}


	Vect getCenter() { return center; }
	double getRadius() { return radius; }
	Color getColor() { return color; }
	
	Vect getNormalAt(Vect point);
	double findIntersection(Ray ray);
};
