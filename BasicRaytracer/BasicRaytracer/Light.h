#pragma once
#include "Vect.h"
#include "Color.h"
#include "Source.h"

class Light : public Source
{
private:
	Vect position;
	Color color;

public:
	Light() : position(Vect(0, 0, 0)), color(Color(1, 1, 1, 0)) {}
	Light(Vect position, Color color) : position(position), color(color) {}

	virtual Vect getPosition() { return position; }
	virtual Color getColor() { return color; }
};