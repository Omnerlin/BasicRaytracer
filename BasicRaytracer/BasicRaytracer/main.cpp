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


#include "RayTracer.h"


int main()
{

	Raytracer tracer(1920, 1080, 72);

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
	Sphere sphere(Vect(0, 0, 0), 1, fancyGreen);

	// Make a plane
	Plane plane(Vect(0, 1, 0), -1, maroon);

	// Add scene objects
	tracer.addSceneObject(dynamic_cast<Object*>(&sphere));
	tracer.addSceneObject(dynamic_cast<Object*>(&plane));

	// Add light
	tracer.addLight(dynamic_cast<Source*>(&sceneLight));

	tracer.setCameraPosition(Vect(3, 1.5, -2));
	tracer.renderImageToBuffer();
	tracer.saveImageToFile("Test2.bmp");

	return 0;
}


