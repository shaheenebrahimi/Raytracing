#pragma once
#ifndef HIT_H
#define HIT_H

#include <glm/glm.hpp>

class Hit {
public:
    glm::vec3 x; // position
    glm::vec3 n; // normal
    float t;

    Hit(glm::vec3 x, glm::vec3 n, float t) { this->x = x; this->n = n; this->t = t; }
};

#endif