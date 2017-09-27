#include "RayTracer.h"

void Raytracer::setImageDimensions(unsigned int width, unsigned int height)
{
}

void Raytracer::setImageDpi(unsigned int dpi)
{
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
}
