#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "Source.h"
#include "Sphere.h"
#include "Plane.h"
#include "Camera.h"
#include "Light.h"

// Struct for pixel coloring
struct RGBType 
{
	double r = 0.0;
	double g = 0.0;
	double b = 0.0;
};

class Raytracer
{

public:
	// Re-create pixel buffer to fit new dimensions
	void setImageDimensions(unsigned int width, unsigned int height);

	// Set the dpi for the image output
	void setImageDpi(unsigned int dpi);

	// Render an image to a bmp file with a filename
	void saveImageToFile(const char* filename);

	// Renders the image to the pixel buffer for displaying/saving
	// would eventually like to do this realtime with gpu
	void renderImageToBuffer(); 

	// Adds a renderable object to the scene for rendering
	void addSceneObject(Object* object);
	
	// Adds a light to the scene
	void addLight(Source *lightSource);

	// Sets the position of the scene camera
	void setCameraPosition(Vect &position);

	// Creates Raytracer with default basic image resolution (640 x 480) with 72 Dpi
	Raytracer() : imageWidth(640), imageHeight(480), dpi(72), pixelBuffer(std::vector<RGBType>(640 * 480)) {}

	// Construct Raytracer with custom imageDimensions. Create new pixel buffer to fit these dimensions
	Raytracer(unsigned int imageWidth, unsigned int imageHeight, int dpi) 
		: imageWidth(imageWidth), imageHeight(imageHeight), dpi(dpi), pixelBuffer(std::vector<RGBType>(imageWidth * imageHeight)) {}


private:
	int imageWidth; 
	int imageHeight;
	int dpi;

	// Might make these variables changeable later
	float ambientLight = 0.2; // ambient light in the scene
	float accuracy = 0.000001; // accuracy of rays

	// Get index of closest objects based on intersections given
	int getWinningObjectIndex(std::vector<double>& objectIntersections);

	// Return the color given at a certain intersection point, which is used to color a pixel
	Color getColorAt(Vect intersectionPosition, Vect intersectingRayDirection, int indexOfWinningObject);

	Vect cameraPosition; // Position of the camera

	std::vector<Object*> sceneObjects; // Objects contained in our scene
	std::vector<Source*> lightSources; // Lights that are contained in our scene
	std::vector<RGBType> pixelBuffer; 	// Buffer that stores all pixel information

};