#pragma once
#ifndef MESH_H
#define MESH_H

#include <string>
#include "Triangle.h"
#include "Ellipsoid.h"

class Mesh : public Shape {
public:
    Shape* boundingShape;
    std::vector<Triangle*> triangles;

    Mesh(const std::string& objPath, glm::vec3 position, glm::vec4 rotation, glm::vec3 scale, Material* mat);
    void loadMesh(const std::string& meshName);
    void bufToTriangles(std::vector<float>& posBuf, std::vector<float>& norBuf);
    Ellipsoid* getBoundingShape(std::vector<float>& posBuf, std::vector<float>& norBuf);
    Hit* collider(Ray& ray);
};

#endif