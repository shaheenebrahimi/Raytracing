#pragma once
#ifndef RAY_H
#define RAY_H

#include <glm/glm.hpp>

class Ray {
public:
    glm::vec3 p; // start point
    glm::vec3 v; // direction

    Ray(glm::vec3 p, glm::vec3 v) { this->p = p; this->v = v; }
};

#endif