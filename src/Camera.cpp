#define _USE_MATH_DEFINES
#include <cmath> 
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

Camera::Camera() {
	this->resolution = 512.0f;
	this->position = glm::vec3(0.0f, 0.0f, 5.0f);
	this->lookat = glm::vec3(0.0f, 0.0f, -1.0f);
	this->up = glm::vec3(0.0f, 1.0f, 0.0f);
	this->fov = (float)(45.0f*M_PI/180.0f);
	this->focalDist = 1.0f;
	this->init();
}

Camera::Camera(glm::vec3 position, glm::vec3 lookat, glm::vec3 up, float fov) {
	this->resolution = 512.0f;
	this->position = position;
	this->lookat = normalize(lookat);
	this->up = normalize(up);
	this->fov = fov;
	this->focalDist = 1.0f;
	this->resolution = resolution;
	this->init();
}

Camera::~Camera() { }

void Camera::init() {
	float bound = focalDist * tan(fov/2);
	this->screen = position + focalDist*lookat;
	this->axis1 = cross(lookat, up);
	this->axis2 = up;
	this->startBound = screen - (bound * axis1) - (bound * axis2);
	this->stepSize = (2*bound) / float(resolution);
	this->offset = stepSize/2; // get middle of pixel
}

void Camera::setResolution(int resolution) {
	this->resolution = resolution;
	init();
}

// get pixel coordinate in world space
Ray Camera::getRay(int r, int c) {
	glm::vec3 pixelCoord = startBound + (c*stepSize + offset) * axis1 + (r*stepSize + offset) * axis2;
	glm::vec3 direction = normalize(pixelCoord - position);
	return Ray(this->position, direction);
}