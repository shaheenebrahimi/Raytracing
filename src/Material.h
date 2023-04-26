#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H

#include "Light.h"
#include "Ray.h"
// #include "Scene.h"

#include <glm/glm.hpp>
#include <vector>
#include <cmath>

class Material {
public:
    enum Type { 
        BLINN_PHONG = 0,
        REFLECTIVE
    };
    Type type;
    virtual glm::vec3 computeFrag(glm::vec3 ray, glm::vec3 pos, glm::vec3 nor, std::vector<Light*>& lights) = 0;
};

#endif