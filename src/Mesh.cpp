#include "Mesh.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include <iostream>

using namespace std;

Mesh::Mesh(const string& meshName, glm::vec3 position, glm::vec4 rotation, glm::vec3 scale, Material* mat) {
    this->position = position;
	this->rotation = rotation;
	this->scale = scale;
	this->mat = mat;
	this->transform = getTransformationMatrix();
    loadMesh(meshName); // load obj and populate the triangles
}

Hit* Mesh::collider(Ray& ray) {
    Hit* closestHit = nullptr;

	glm::vec3 p_prime = inverse(transform) * glm::vec4(ray.p, 1.0f);
    glm::vec3 v_prime = normalize(inverse(transform) * glm::vec4(ray.v, 0.0f));
	Ray pray (p_prime, v_prime);

	if (boundingShape->collider(pray)) { // determine if intersects bounding shape
        for (Triangle* tri : triangles) {
            Hit* hit_prime = tri->collider(pray);
			if (hit_prime) {
				glm::vec3 x = transform * glm::vec4(hit_prime->x, 1.0f);
				glm::vec3 n = normalize(inverse(transpose(transform)) * glm::vec4(hit_prime->n, 0.0f));
				float t = length(x - ray.p);
				if (dot(ray.v, x - ray.p) < 0) t *= -1;
				if (t > 0) {
					Hit* hit = new Hit(x, n, t);
					if (closestHit == nullptr || t < closestHit->t) {
						closestHit = hit;
					}
				}
            }
        }
		return closestHit;
	}
    return nullptr;
}

void Mesh::loadMesh(const string& meshName) {
    vector<float> posBuf;
    vector<float> norBuf;
	tinyobj::attrib_t attrib;
	vector<tinyobj::shape_t> shapes;
	vector<tinyobj::material_t> materials;
	string errStr;
	bool rc = tinyobj::LoadObj(&attrib, &shapes, &materials, &errStr, meshName.c_str());
	if(!rc) {
		cerr << errStr << endl;
	} else {
		// Loop over shapes
		for(size_t s = 0; s < shapes.size(); s++) {
			// Loop over faces (polygons)
			size_t index_offset = 0;
			for(size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
				size_t fv = shapes[s].mesh.num_face_vertices[f];
				// Loop over vertices in the face.
				for(size_t v = 0; v < fv; v++) {
					// access to vertex
					tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
					posBuf.push_back(attrib.vertices[3*idx.vertex_index+0]);
					posBuf.push_back(attrib.vertices[3*idx.vertex_index+1]);
					posBuf.push_back(attrib.vertices[3*idx.vertex_index+2]);
					if(!attrib.normals.empty()) {
						norBuf.push_back(attrib.normals[3*idx.normal_index+0]);
						norBuf.push_back(attrib.normals[3*idx.normal_index+1]);
						norBuf.push_back(attrib.normals[3*idx.normal_index+2]);
					}
				}
				index_offset += fv;
			}
		}
        bufToTriangles(posBuf, norBuf);
		boundingShape = getBoundingShape(posBuf, norBuf);
	}
}

void Mesh::bufToTriangles(vector<float>& posBuf, vector<float>& norBuf) {
    for (int i = 0; i < posBuf.size()/9; i++) {
        glm::vec3 vert0 (posBuf[9*i], posBuf[9*i+1], posBuf[9*i+2]);
        glm::vec3 vert1 (posBuf[9*i+3], posBuf[9*i+4], posBuf[9*i+5]);
        glm::vec3 vert2 (posBuf[9*i+6], posBuf[9*i+7], posBuf[9*i+8]);
        glm::vec3 nor0 (norBuf[9*i], norBuf[9*i+1], norBuf[9*i+2]);
        glm::vec3 nor1 (norBuf[9*i+3], norBuf[9*i+4], norBuf[9*i+5]);
        glm::vec3 nor2 (norBuf[9*i+6], norBuf[9*i+7], norBuf[9*i+8]);
        Triangle* tri = new Triangle(vert0, vert1, vert2, nor0, nor1, nor2, this->mat);
        triangles.push_back(tri);
    }
}

Ellipsoid* Mesh::getBoundingShape(vector<float>& posBuf, vector<float>& norBuf) {
	// Scale the vertex positions so that they fit within [-1, +1] in all three dimensions.
	glm::vec3 vmin(posBuf[0], posBuf[1], posBuf[2]);
	glm::vec3 vmax(posBuf[0], posBuf[1], posBuf[2]);
	for(int i = 0; i < (int)posBuf.size(); i += 3) {
		glm::vec3 v(posBuf[i], posBuf[i+1], posBuf[i+2]);
		vmin.x = min(vmin.x, v.x);
		vmin.y = min(vmin.y, v.y);
		vmin.z = min(vmin.z, v.z);
		vmax.x = max(vmax.x, v.x);
		vmax.y = max(vmax.y, v.y);
		vmax.z = max(vmax.z, v.z);
	}

	glm::vec3 center = 0.5f*(vmin + vmax);
	// float radius = length(vmax - center);
	glm::vec3 radii = scale*1.2f*((vmax - vmin) / 2.0f); // might clip other obj files
	
    return new Ellipsoid(center, glm::vec4(0,0,0,1), radii, nullptr);
}
