#pragma once
#include "Vect.h"
#include "Color.h"
class Source {
public:
	Source() {}
	~Source() {}
	virtual Vect getPosition() { return Vect(0, 0, 0); }
	virtual Color getColor() { return Color(1, 1, 1, 0); }

private:
};