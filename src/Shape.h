#pragma once
#ifndef SHAPE_H
#define SHAPE_H

#define _USE_MATH_DEFINES
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Ray.h"
#include "Hit.h"
#include "Material.h"

#include <vector>
#include <iostream>


class Shape {
public:
    glm::vec3 position;
    glm::vec4 rotation;
    glm::vec3 scale;
    glm::mat4 transform;
    Material* mat;

    virtual Hit* collider(Ray& ray) = 0;

    glm::mat4 getTransformationMatrix() {
        glm::mat4 T = glm::translate(glm::mat4(1.0f), position);
        glm::mat4 R = glm::rotate(glm::mat4(1.0f), rotation[0], glm::vec3(rotation[1], rotation[2], rotation[3]));
        glm::mat4 S = glm::scale(glm::mat4(1.0f), scale);
        return T * R * S;
    }
};

#endif

