#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "Ray.h"
#include "Camera.h"
#include "Light.h"
#include "Sphere.h"
#include "Plane.h"

struct RGBType {
	double r; 
	double g;
	double b;
};


void savebmp(const char* filename, int w, int h, int dpi, RGBType* data) {
	FILE* f;
	int k = w*h;
	int s = 4 * k;
	int filesize = 54 + s;

	double factor = 39.375;
	int m = static_cast<int>(factor);

	int ppm = dpi*m;

	unsigned char bmpfileheader[14] = { 'B','M', 0,0,0,0, 0,0,0,0, 54,0,0,0 };
	unsigned char bmpinfoheader[40] = { 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0 };

	bmpfileheader[2] = (unsigned char)(filesize);
	bmpfileheader[3] = (unsigned char)(filesize >> 8);
	bmpfileheader[4] = (unsigned char)(filesize >> 16);
	bmpfileheader[5] = (unsigned char)(filesize >> 24);

	bmpinfoheader[4] = (unsigned char)(w);
	bmpinfoheader[5] = (unsigned char)(w >> 8);
	bmpinfoheader[6] = (unsigned char)(w >> 16);
	bmpinfoheader[7] = (unsigned char)(w >> 24);

	bmpinfoheader[8] = (unsigned char)(h);
	bmpinfoheader[9] = (unsigned char)(h >> 8);
	bmpinfoheader[10] = (unsigned char)(h >> 16);
	bmpinfoheader[11] = (unsigned char)(h >> 24);

	bmpinfoheader[21] = (unsigned char)(s);
	bmpinfoheader[22] = (unsigned char)(s >> 8);
	bmpinfoheader[23] = (unsigned char)(s >> 16);
	bmpinfoheader[24] = (unsigned char)(s >> 24);

	bmpinfoheader[25] = (unsigned char)(ppm);
	bmpinfoheader[26] = (unsigned char)(ppm >> 8);
	bmpinfoheader[27] = (unsigned char)(ppm >> 16);
	bmpinfoheader[28] = (unsigned char)(ppm >> 24);

	bmpinfoheader[29] = (unsigned char)(ppm);
	bmpinfoheader[30] = (unsigned char)(ppm >> 8);
	bmpinfoheader[31] = (unsigned char)(ppm >> 16);
	bmpinfoheader[32] = (unsigned char)(ppm >> 24);

	f = fopen(filename, "wb");

	fwrite(bmpfileheader, 1, 14, f);
	fwrite(bmpinfoheader, 1, 40, f);

	for (int i = 0; i < k; i++) {
		RGBType rgb = data[i];

		double red = (data[i].r) * 255;
		double green = (data[i].g) * 255;
		double blue = (data[i].b) * 255;

		unsigned char color[3] = { (int)floor(blue), (int)floor(green), (int)floor(red) };
		fwrite(color, 1, 3, f);
	}

	fclose(f);
}



int main()
{
	std::cout << "Rendering" << std::endl;
	std::cout << "Size of pixel array: " << sizeof(RGBType) * 640 * 480 << std::endl;
	int dpi = 72;
	int width = 640;
	int height = 480;
	int n = width*height;
	int thisone;

	// Array of pixel colors to use for writing to the image.
	RGBType* pixels = new RGBType[n];

	Vect origin(0, 0, 0);
	Vect X(1, 0, 0);
	Vect Y(0, 1, 0);
	Vect Z(0, 0, 1);

	// Abritrary camera starting position
	Vect campos(3, 1.5, -4);

	// Position that the camera is looking at.
	Vect lookAt(0, 0, 0);

	// Difference in position between where the camera is and it's subject
	Vect diffBetween( 
		campos.getX() - lookAt.getX(),
		campos.getY() - lookAt.getY(),
		campos.getZ() - lookAt.getZ()
	);

	// Find the direction of the camera based on the difference 
	// between where is is and what it is looking at.
	Vect camdir = diffBetween.negative().normalize();
	Vect camright = Y.crossProduct(camdir).normalize();
	Vect camdown = camright.crossProduct(camdir);

	// Create the scene camera
	Camera scene_cam(campos, camdir, camright, camdown);

	// Create some colors we want to use
	Color lightColor(1.0, 1.0, 1.0, 0);
	Color fancyGreen(0.5, 1.0, 0.5, 0.3);
	Color gray(0.5, 0.5, 0.5, 0);
	Color black(0, 0, 0, 0);
	Color maroon(0.5, 0.25, 0.25, 0);

	// Set up our scene light
	Vect lightPosition(-7, 10, -10);
	Light sceneLight(lightPosition, lightColor);

	// Make a sphere
	Sphere sphere(origin, 1, fancyGreen);

	// Make a plane
	Plane plane(Y, -1, maroon);

	// Write each pixel color to the corrosponding pixel.
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			thisone = y*width + x;
			pixels[thisone].r = 0.2;
			pixels[thisone].g = 0.9;
			pixels[thisone].b = 0.1;
		}
	}

	// Save Pixel data to a bitmap
	savebmp("scene.bmp", width, height, dpi, pixels);
	delete[] pixels;
	return 0;
}