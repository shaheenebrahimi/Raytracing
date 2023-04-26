#include "Ellipsoid.h"

#include <iostream>

using namespace std;

Ellipsoid::Ellipsoid() {
    this->position = glm::vec3(0.0f);
    this->rotation = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
    this->scale = glm::vec3(1.0f);
    this->mat = nullptr;
    this->transform = glm::mat4(1);
}

Ellipsoid::Ellipsoid(glm::vec3 position, glm::vec4 rotation, glm::vec3 scale, Material* mat) {
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
    this->mat = mat;
    this->transform = getTransformationMatrix();
}

Hit* Ellipsoid::collider(Ray& ray) {
    glm::vec3 p_prime = inverse(transform) * glm::vec4(ray.p, 1.0f);
    glm::vec3 v_prime = normalize(inverse(transform) * glm::vec4(ray.v, 0.0f));
    float a = dot(v_prime, v_prime);
    float b = 2 * dot(v_prime, p_prime);
    float c = dot(p_prime, p_prime) - 1;
    float d = pow(b, 2) - (4 * a * c);
    if (d > 0) {
        float t1_prime = (-b + sqrt(d)) / (2 * a);
        float t2_prime = (-b - sqrt(d)) / (2 * a);
        
        glm::vec3 x1_prime = p_prime + t1_prime*v_prime;
        glm::vec3 x2_prime = p_prime + t2_prime*v_prime;

        glm::vec3 x1 = transform * glm::vec4(x1_prime, 1.0f);
        glm::vec3 x2 = transform * glm::vec4(x2_prime, 1.0f);

        glm::vec3 n1 = normalize(inverse(transpose(transform)) * glm::vec4(x1_prime, 0.0f));
        glm::vec3 n2 = normalize(inverse(transpose(transform)) * glm::vec4(x2_prime, 0.0f));

        float t1 = length(x1 - ray.p);
        float t2 = length(x2 - ray.p);

        if (dot(ray.v, x1 - ray.p) < 0) t1 *= -1;
        if (dot(ray.v, x2 - ray.p) < 0) t2 *= -1;

        // return closest hit in front of camera
        float epsilon = 0.001f; // not same surface
        if (t1 > epsilon && t2 > epsilon) { // both valid
            if (t1 < t2) // return closest
                return new Hit (x1, n1, t1);
            else
                return new Hit (x2, n2, t2);
        }
        else if (t1 > epsilon) { // only t1 valid
            return new Hit (x1, n1, t1);
        }
        else if (t2 > epsilon) { // only t2 valid
            return new Hit (x2, n2, t2);
        }
        
    }
    return nullptr;
}