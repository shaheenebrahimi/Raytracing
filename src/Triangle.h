#pragma once
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"

class Triangle : public Shape{
public:
    glm::vec3 vert0;
    glm::vec3 vert1;
    glm::vec3 vert2;
    glm::vec3 nor0;
    glm::vec3 nor1;
    glm::vec3 nor2;

    Triangle();
    Triangle(glm::vec3 vert0, glm::vec3 vert1, glm::vec3 vert2, glm::vec3 nor0, glm::vec3 nor1, glm::vec3 nor2, Material* mat);

    Hit* collider(Ray& ray);

};

#endif