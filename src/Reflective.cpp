#include "Reflective.h"

Reflective::Reflective() {
    type = REFLECTIVE;
}

glm::vec3 Reflective::computeFrag(glm::vec3 ray, glm::vec3 pos, glm::vec3 nor, std::vector<Light*>& lights) {
    return glm::vec3(0,0,0);
}

