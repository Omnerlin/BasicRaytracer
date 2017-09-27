#include "RayTracer.h"
void Raytracer::setImageDimensions(unsigned int width, unsigned int height)
{
	imageWidth = width;
	imageHeight = height;
	pixelBuffer = std::vector<RGBType>(width*height);
}

void Raytracer::setImageDpi(unsigned int dpi)
{
	this->dpi = dpi;
}

void Raytracer::saveImageToFile(const char* filename)
{
	FILE* f;
	int k = imageWidth*imageHeight;
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

	bmpinfoheader[4] = (unsigned char)(imageWidth);
	bmpinfoheader[5] = (unsigned char)(imageWidth >> 8);
	bmpinfoheader[6] = (unsigned char)(imageWidth >> 16);
	bmpinfoheader[7] = (unsigned char)(imageWidth >> 24);

	bmpinfoheader[8] = (unsigned char)(imageHeight);
	bmpinfoheader[9] = (unsigned char)(imageHeight >> 8);
	bmpinfoheader[10] = (unsigned char)(imageHeight >> 16);
	bmpinfoheader[11] = (unsigned char)(imageHeight >> 24);

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
		RGBType rgb = pixelBuffer[i];

		double red = (pixelBuffer[i].r) * 255;
		double green = (pixelBuffer[i].g) * 255;
		double blue = (pixelBuffer[i].b) * 255;

		unsigned char color[3] = { (unsigned char)floor(blue), (unsigned char)floor(green), (unsigned char)floor(red) };
		fwrite(color, 1, 3, f);
	}

	fclose(f);
}

void Raytracer::renderImageToBuffer()
{
	std::cout << "Rendering" << std::endl;
	int dpi = 72;
	double aspectRatio = (double)imageWidth / (double)imageHeight;
	int n = imageWidth*imageHeight;
	int currentPixel; // Used for telling which pixel we are manipulating 

	Vect origin(0, 0, 0);
	Vect X(1, 0, 0);
	Vect Y(0, 1, 0);
	Vect Z(0, 0, 1);

	// Position that the camera is looking at.
	Vect lookAt(0, 0, 0);

	// Difference in position between where the camera is and it's subject
	Vect diffBetween(
		cameraPosition.getX() - lookAt.getX(),
		cameraPosition.getY() - lookAt.getY(),
		cameraPosition.getZ() - lookAt.getZ()
	);

	// Find the direction of the camera based on the difference 
	// between where it is and what it is looking at.
	Vect camdir = diffBetween.negative().normalize();
	Vect camright = Y.crossProduct(camdir).normalize();
	Vect camdown = camright.crossProduct(camdir);

	// Create the scene camera
	Camera scene_cam(cameraPosition, camdir, camright, camdown);

	double xamnt, yamnt;

	// Write each pixel color to the corrosponding pixel.
	for (unsigned int x = 0; x < imageWidth; x++) {
		for (unsigned int y = 0; y < imageHeight; y++) {
			currentPixel = y*imageWidth + x;

			// start with no anti-aliasing
			if (imageWidth > imageHeight) {
				// the image is wider than it is tall
				xamnt = ((x + 0.5) / imageWidth) * aspectRatio - (((imageWidth - imageHeight) / (double)imageHeight) / 2);
				yamnt = ((imageHeight - y) + 0.5) / imageHeight;
			}
			else if (imageHeight > imageWidth) {
				// The image is taller than it is wide.
				xamnt = (x + 0.5) / imageWidth;
				yamnt = (((imageHeight - y) + 0.5) / imageHeight) / aspectRatio - (((imageHeight - imageWidth) / (double)imageWidth) / 2);
			}
			else {
				// the image is square
				xamnt = (x + 0.5) / imageWidth;
				yamnt = ((imageHeight - y) + 0.5) / imageHeight;
			}


			Vect camRayOrigin = scene_cam.getPosition();
			Vect camRayDirection = camdir.add(camright.multiply(xamnt - 0.5).add(camdown.multiply(yamnt - 0.5))).normalize();
			Ray camRay(camRayOrigin, camRayDirection);

			// our container of intersections 
			std::vector<double> intersections;
			for (unsigned int i = 0; i < sceneObjects.size(); i++) {
				intersections.push_back(sceneObjects.at(i)->findIntersection(camRay));
			}

			int indexOfWinningObject = getWinningObjectIndex(intersections);

			if (indexOfWinningObject == -1) {
				// Nothing was hit. Color the background black.
				pixelBuffer[currentPixel].r = 0;
				pixelBuffer[currentPixel].g = 0;
				pixelBuffer[currentPixel].b = 0;
			}
			else
			{
				if (intersections[indexOfWinningObject] > accuracy) {
					// Set the color of the pixel to the color of the intersection
					Vect intersectionPosition = camRayOrigin.add(camRayDirection.multiply(intersections[indexOfWinningObject]));
					Vect intersectingRayDirection = camRayDirection;

					Color intersectionColor = getColorAt(intersectionPosition, intersectingRayDirection, indexOfWinningObject);

					pixelBuffer[currentPixel].r = intersectionColor.Red();
					pixelBuffer[currentPixel].g = intersectionColor.Green();
					pixelBuffer[currentPixel].b = intersectionColor.Blue();
				}
			}
		}
	}
}

void Raytracer::addSceneObject(Object * object)
{
	if (object != nullptr)
	sceneObjects.push_back(object);
}

void Raytracer::addLight(Source * lightSource)
{
	if(lightSource != nullptr)
	lightSources.push_back(lightSource);
}

void Raytracer::setCameraPosition(Vect & position)
{
	cameraPosition = position;
}

int Raytracer::getWinningObjectIndex(std::vector<double>& objectIntersections)
{
	// find and return the index of the winning intersection
	int indexOfMin;

	// prevent unecessary calculations
	if (objectIntersections.size() == 0) {
		// if there are no intersections
		return -1;
	}

	else if (objectIntersections.size() == 1) {
		if (objectIntersections.at(0) > 0) {
			// if that intersection is greater than zero then it's our index of minimum value
			return 0;
		}
		else {
			// otherwise the only intersection value is negative (ray missed everything)
			return -1;
		}
	}
	else {
		// otherwise there is more than one intersection 
		// need to find the maximum distance first.
		double max = 0;
		for (unsigned int i = 0; i < objectIntersections.size(); i++) {
			if (max < objectIntersections.at(i)) {
				max = objectIntersections.at(i);
			}
		}
		// then starting from the maximum value find the minimum
		if (max > 0) {
			// we only want positive intersects
			for (unsigned int i = 0; i < objectIntersections.size(); i++) {
				if (objectIntersections.at(i) > 0 && objectIntersections.at(i) <= max) {
					max = objectIntersections.at(i);
					indexOfMin = i;
				}
			}
			return indexOfMin;
		}
		else {
			// all of the intersections were negative
			return -1;
		}
	}
}

Color Raytracer::getColorAt(Vect intersectionPosition, Vect intersectingRayDirection, int indexOfWinningObject)
{
	Color winningObjectColor = sceneObjects[indexOfWinningObject]->getColor();
	Vect winningObjectNormal = sceneObjects[indexOfWinningObject]->getNormalAt(intersectionPosition);
	Color finalColor = winningObjectColor.colorScalar(ambientLight);

	for (unsigned int i = 0; i < lightSources.size(); i++) {
		Vect lightDirection = lightSources[i]->getPosition().add(intersectionPosition.negative()).normalize();
		float cosineAngle = (float)winningObjectNormal.dotProduct(lightDirection);

		if (cosineAngle > 0) {
			// Test for shadows
			bool shadowed = false;
			Vect distanceToLight = lightSources[i]->getPosition().add(intersectionPosition.negative()).normalize();
			float distanceToLightMagnitude = (float)distanceToLight.magnitude();

			// Cast a secondary ray from the intersection point toward the light.
			// If it intersects with anything before making it back to the light,
			// Our base intersection is in shadow.
			Ray shadowRay(intersectionPosition, lightSources[i]->getPosition().add(intersectionPosition.negative()).normalize());

			std::vector<double> secondaryIntersections;

			for (unsigned int j = 0; j < sceneObjects.size() && shadowed == false; j++) {
				secondaryIntersections.push_back(sceneObjects[j]->findIntersection(shadowRay));
			}

			// Loop through all secondary intersection tests to see if secondary intersection occurred
			for (unsigned int k = 0; k < secondaryIntersections.size(); k++) {
				if (secondaryIntersections[k] > accuracy) {
					if (secondaryIntersections[k] <= distanceToLightMagnitude) {
						shadowed = true;
					}
				}
				break;
			}
			if (!shadowed) {
				finalColor = finalColor.colorAdd(winningObjectColor.colorMult(lightSources[i]->getColor()).colorScalar(cosineAngle));

				if (winningObjectColor.Special() > 0 && winningObjectColor.Special() <= 1) {
					// special 0-1 refers to shininess.
					double dot1 = winningObjectNormal.dotProduct(intersectingRayDirection.negative());
					Vect scalar1 = winningObjectNormal.multiply(dot1);
					Vect add1 = scalar1.add(intersectingRayDirection);
					Vect scalar2 = add1.multiply(2);
					Vect add2 = intersectingRayDirection.negative().add(scalar2);
					Vect reflectionDirection = add2.normalize();

					double specular = reflectionDirection.dotProduct(lightDirection);

					if (specular > 0) {
						specular = pow(specular, 10);
						finalColor = finalColor.colorAdd(lightSources[i]->getColor().colorScalar(specular*winningObjectColor.Special()));
					}
				}
			}

		}
	}
	return finalColor.clip();
}
