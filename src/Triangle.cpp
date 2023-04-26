#include "Triangle.h"

Triangle::Triangle() {
    this->vert0 = glm::vec3(0);
    this->vert1 = glm::vec3(0);
    this->vert2 = glm::vec3(0);
    this->nor0 = glm::vec3(0);
    this->nor1 = glm::vec3(0);
    this->nor2 = glm::vec3(0);
    this->mat = nullptr;
}

Triangle::Triangle(glm::vec3 vert0, glm::vec3 vert1, glm::vec3 vert2, glm::vec3 nor0, glm::vec3 nor1, glm::vec3 nor2, Material* mat) {
    this->vert0 = vert0;
    this->vert1 = vert1;
    this->vert2 = vert2;
    this->nor0 = nor0;
    this->nor1 = nor1;
    this->nor2 = nor2;
    this->mat = mat;
}

Hit* Triangle::collider(Ray& ray) {
    float epsilon = 0.0001f;

    glm::vec3 edge1 = vert1 - vert0;
    glm::vec3 edge2 = vert2 - vert0;

    glm::vec3 p_vec = glm::cross(ray.v, edge2);

    float det = dot(edge1, p_vec);
    if (det < epsilon && det > -epsilon) // lies in triangle plane
        return nullptr;
    float inv_det = 1.0f / det;

    // calculate U parameter and test bounds
    glm::vec3 t_vec = ray.p - vert0;
    float u = dot(t_vec, p_vec) * inv_det;
    if (u < 0.0f || u > 1.0f) // barycentric
        return nullptr;

    glm::vec3 q_vec = glm::cross(t_vec, edge1);

    // calculate V parameter and test bounds
    float v = dot(ray.v, q_vec) * inv_det;
    if (v < 0.0f || u + v > 1.0)
        return nullptr;

    // calculate W parameter, ray intersects triangle
    float w = 1.0f - u - v;

    // calculate t'
    float t = dot(edge2, q_vec) * inv_det;
    if (t < epsilon)
        return nullptr;

    // compute barycentric
    glm::vec3 x = w * vert0 + u * vert1 + v * vert2;
    glm::vec3 n = normalize(w * nor0 + u * nor1 + v * nor2);
    
    return new Hit(x, n, t);

}