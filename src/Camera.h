#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include "Ray.h"

class Camera {
public:
	glm::vec3 position; // eye or origin
	glm::vec3 lookat;
	glm::vec3 up;
	float fov;
	float focalDist;
	int resolution;

	Camera();
	Camera(glm::vec3 position, glm::vec3 lookat, glm::vec3 up, float fov);
	virtual ~Camera();

	Ray getRay(int r, int c);
	void setResolution(int resolution);
	void init();
	
private:
	glm::vec3 screen;
	glm::vec3 axis1;
	glm::vec3 axis2;
	glm::vec3 startBound;
	float stepSize;
	float offset;
};

#endif
