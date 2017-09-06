#include "Vect.h"

double Vect::magnitude() {
	return sqrt((x*x) + (y*y) + (z*z));
}

Vect Vect::normalize() {
	double mag = magnitude();
	return Vect(x / mag, y / mag, z / mag);
}

Vect Vect::negative() {
	return Vect(-x, -y, -z);
}

double Vect::dotProduct(Vect v) {
	return x * v.getX() + y * v.getY() + z * v.getZ();
}

Vect Vect::crossProduct(Vect v) {
	return Vect(
		y*v.getZ() - z*v.getY(),
		z*v.getX() - x * v.getZ(),
		x*v.getY() - y*v.getX()
	);
}

Vect Vect::add(Vect v) {
	return Vect(x + v.getX(), y + v.getY(), z + v.getZ());
}

Vect Vect::multiply(double scalar) {
	return Vect(x * scalar, y * scalar, z * scalar);
}