#pragma once
#ifndef BLINN_PHONG_H
#define BLINN_PHONG_H

#include "Material.h"
#include "Collision.h"

#include <glm/glm.hpp>

class BlinnPhong : public Material {
public:
    glm::vec3 kd;
    glm::vec3 ks;
    glm::vec3 ka;
    float s;

    BlinnPhong();
    BlinnPhong(glm::vec3 kd, glm::vec3 ks, glm::vec3 ka, float s);
    glm::vec3 computeFrag(glm::vec3 ray, glm::vec3 pos, glm::vec3 nor, std::vector<Light*>& lights);
};

#endif