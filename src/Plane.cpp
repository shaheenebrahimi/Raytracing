#include "Plane.h"

using namespace std;

Plane::Plane(glm::vec3 normal, glm::vec3 position, glm::vec4 rotation, Material* mat) {
    this->normal = normalize(normal);
    this->position = position;
    this->rotation = rotation;
    this->scale = glm::vec3(1.0f, 1.0f, 1.0f);
    this->mat = mat;
    this->transform = getTransformationMatrix();
}

Hit* Plane::collider(Ray& ray) {
    float t = dot(normal, position - ray.p) / dot(normal, ray.v);
    glm::vec3 x = ray.p + t*ray.v;
    float epsilon = 0.001f;
    if (t > epsilon) return new Hit (x, normal, t);
    else return nullptr;
}