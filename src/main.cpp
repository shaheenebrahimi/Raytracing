#include <iostream>
#include <string>

// #define TINYOBJLOADER_IMPLEMENTATION
// #include "tiny_obj_loader.h"

#include "Image.h"
#include "Camera.h"
#include "Scene.h"
#include "Ray.h"
#include "Ellipsoid.h"
#include "BlinnPhong.h"
#include "Image.h"

#include<memory>
#include <glm/glm.hpp>

using namespace std;

void raytrace(Scene& scn, shared_ptr<Image> img, int resolution) {
    scn.setCamResolution(resolution);
	for (int r = 0; r < resolution; r++) { // iterate through pixels
		for (int c = 0; c < resolution; c++) {
			Ray ray = scn.cam.getRay(r, c);
			glm::vec3 fragColor = 255.0f * scn.computeColor(ray);

			float red = (fragColor[0] < 0) ? 0 : fragColor[0];
			float green = (fragColor[1] < 0) ? 0 : fragColor[1];
			float blue = (fragColor[2] < 0) ? 0 : fragColor[2];
			red = (red > 255) ? 255 : red;
			green = (green > 255) ? 255 : green;
			blue = (blue > 255) ? 255 : blue;

			img->setPixel(c, r, (unsigned char)red, (unsigned char)green, (unsigned char)blue);
		}
	}
}

int main(int argc, char **argv)
{
	if(argc < 4) {
		cout << "Not sufficient parameters" << endl;
		return 0;
	}
	int scene = atoi(argv[1]);
	int resolution = atoi(argv[2]); // size of output file
	string filename = argv[3]; // name of output file

	shared_ptr<Image> image = make_shared<Image>(resolution, resolution);

	Scene scn (scene); // Build Scene

	raytrace(scn, image, resolution); // raytrace

	image->writeToFile(filename);
	
	return 0;
}
