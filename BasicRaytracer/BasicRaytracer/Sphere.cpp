#include "Sphere.h"

Vect Sphere::getNormalAt(Vect point)
{
	// normal always points away from the center of the sphere.
	Vect normal = point.add(center.negative()).normalize();
	return normal;
}

double Sphere::findIntersection(Ray ray)
{
	Vect rayOrigin = ray.getOrigin();
	double rayOriginX = rayOrigin.getX();
	double rayOriginY = rayOrigin.getY();
	double rayOriginZ = rayOrigin.getZ();

	Vect rayDirection = ray.getDirection();
	double rayDirectionX = rayDirection.getX();
	double rayDirectionY = rayDirection.getY();
	double rayDirectionZ = rayDirection.getZ();

	Vect sphereCenter = center;
	double sphereCenterX = sphereCenter.getX();
	double sphereCenterY = sphereCenter.getY();
	double sphereCenterZ = sphereCenter.getZ();

	double a = 1; // normalized

	double b = (2 * (rayOriginX - sphereCenterX) * rayDirectionX) +
		(2 * (rayOriginY - sphereCenterY) * rayDirectionY) +
		(2 * (rayOriginZ - sphereCenterZ) * rayDirectionZ);

	double c = pow(rayOriginX - sphereCenterX, 2) +
		pow(rayOriginY - sphereCenterY, 2) +
		pow(rayOriginZ - sphereCenterZ, 2) - (radius*radius);

	double discriminant = b*b - 4 * c;

	if (discriminant > 0) {
		// the ray intersects the sphere.

		// the first root
		double root1 = ((-1 * b - sqrt(discriminant)) / 2) - 0.0000001;
		if (root1 > 0) {
			// the first root is the smallest positive root
			return root1;
		}
		else {
			// the second root is the smallest positive root.
			double root2 = ((sqrt(discriminant) - b) / 2) - 0.0000001;
			return root2;
		}
	}
	else {
		// The ray missed the sphere
		return -1;
	}
}
