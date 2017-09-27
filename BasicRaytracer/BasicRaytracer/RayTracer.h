#pragma once
#include "Source.h"
#include "Sphere.h"
#include "Plane.h"
#include <string>
#include <vector>
#include <memory>

struct RGBType {
	double r;
	double g;
	double b;
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
	void renderImageToBuffer(); 

	// Adds a renderable object to the scene for rendering
	void addSceneObject(Object* object);
	
	// Adds a light to the scene
	void addLight(Source *lightSource);

	// Creates Raytracer with default basic image resolution (640 x 480) with 72 Dpi
	Raytracer() : imageWidth(640), imageHeight(480), dpi(72), pixelBuffer(std::unique_ptr<RGBType[]> (new RGBType[640*480])) {}

	// Construct Raytracer with custom imageDimensions. Create new pixel buffer to fit these dimensions
	Raytracer(unsigned int imageWidth, unsigned int imageHeight, int dpi) 
		: imageWidth(imageWidth), imageHeight(imageHeight), dpi(dpi), pixelBuffer(std::unique_ptr<RGBType[]>(new RGBType[imageWidth * imageHeight])) {}


private:
	int imageWidth;
	int imageHeight;
	int dpi;

	std::vector<Object*> sceneObjects; // Objects contained in our scene
	std::vector<Source*> lightSources; // Lights that are contained in our scene

	// Buffer that stores all pixel information
	std::unique_ptr<RGBType[]> pixelBuffer;
};