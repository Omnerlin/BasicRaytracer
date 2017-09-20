#pragma once
class Color {

private:
	double red, green, blue, special;


public:
	Color() : red(0.5), green(0.5), blue(0.5), special(0) {}
	Color(double r, double g, double b, double s) : red(r), green(g), blue(b), special(s) {}

	double Red() { return red; }
	double Green() { return green; }
	double Blue() { return blue; }
	double Special() { return special; }

	void setRed(double r) { red = r; }
	void setGreen(double g) { green = g; }
	void setBlue(double b) { blue = b; }
	void setSpecial(double s) { special = s; }

};