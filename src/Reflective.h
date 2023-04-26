#include "Material.h"

class Reflective : public Material {
public:
    Reflective();
    glm::vec3 computeFrag(glm::vec3 ray, glm::vec3 pos, glm::vec3 nor, std::vector<Light*>& lights);
};