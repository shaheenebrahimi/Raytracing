#pragma once
#ifndef LIGHT_H
#define LIGHT_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

class Light {
public:
    glm::vec3 position;
    float intensity;

    Light(glm::vec3 position, float intensity);
};

#endif