#pragma once
#ifndef COLLISION_H
#define COLLISION_H

#include "Hit.h"
#include "Shape.h"

#include <glm/glm.hpp>

class Collision {
public:
    Hit* hit;
    Shape* obj;
    Collision(Hit* hit, Shape* obj) { this->hit = hit; this->obj = obj; }
};

#endif
