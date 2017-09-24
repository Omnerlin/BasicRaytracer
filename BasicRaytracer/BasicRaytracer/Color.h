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

	double brightness() {
		return (red + green + blue) / 3;
	}

	Color colorScalar(double scalar) {
		return Color(red*scalar, green*scalar, blue * scalar, special);
	}

	Color colorAdd(Color color) {
		return Color(red + color.Red(), green + color.Green(), blue + color.Blue(), special);
	}

	Color colorMult(Color color) {
		return Color(red * color.Red(), green * color.Green(), blue * color.Blue(), special);
	}

	Color colorAverage(Color color) {
		return Color((red + color.Red()) / 2, (green + color.Green()) / 2, (blue + color.Blue()) / 2, special);
	}

	Color clip() {
		double total = red + green + blue;
		double excessLight = total - 3;

		if (excessLight > 0) {
			red = red + excessLight * (red / total);
			green = green + excessLight * (green / total);
			blue = blue + excessLight * (blue / total);
		}
		if (red > 1) red = 1;
		if (red < 0) red = 0;
		if (green > 1) green = 1;
		if (green < 0) green = 0;
		if (blue > 1) blue = 1;
		if (blue < 0) blue = 0;

		return Color(red, green, blue, special);
	}
};