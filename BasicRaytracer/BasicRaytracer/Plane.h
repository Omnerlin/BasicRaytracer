#pragma once
#include "Object.h"
#include "Vect.h"

class Plane : public Object
{
private:
	Vect normal;
	Color color;
	double distance;

public:
	Vect getNormal() { return normal; }
	double getDistance() { return distance; }
	Color getColor() { return color; }

	Vect getNormalAt(Vect point) {
		return normal;
	}

	double findIntersection(Ray ray) {
		Vect rayDirection = ray.getDirection();

		double a = rayDirection.dotProduct(normal);

		if (a == 0) {
			// ray is parallel to the plane
			return -1;
		}
		else {
			double b = normal.dotProduct(ray.getOrigin().add(normal.multiply(distance).negative()));
			return -1 * b / a;
		}
	}

	Plane() : normal(Vect(1,0,0)), distance(0), color(Color(0.5, 0.5, 0.5, 0)) {}
	Plane(Vect normal, double distance, Color color) : normal(normal), distance(distance), color(color) {}

};