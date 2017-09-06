#pragma once
#include "Vect.h"

class Camera
{
private:
	Vect position, direction, right, down;
	
public:
	Camera() : position(Vect(0, 0, 0)), direction(Vect(0, 0, 1)), right(Vect(0, 0, 0)), down(Vect(0, 0, 0)) {}
	Camera(Vect pos, Vect dir, Vect right, Vect down) : position(pos), direction(dir), right(right), down(down) {}

	Vect getPosition() { return position; }
	Vect getDirection() { return direction; }
	Vect getRight() { return right; }
	Vect getDown() { return down; }

};