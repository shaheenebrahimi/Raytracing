#include "Scene.h"
#include "Ellipsoid.h"
#include "Plane.h"
#include "BlinnPhong.h"
#include "Reflective.h"
#include "Triangle.h"
#include "Mesh.h"

#include <iostream>

Scene::Scene() { this->background = glm::vec3(0.0f, 0.0f, 0.0f); }

Scene::Scene(int sceneNum) {
    this->background = glm::vec3(0.0f, 0.0f, 0.0f);
    switch(sceneNum) {
        case 1: loadSceneA(); break;
        case 2: loadSceneA(); break;
        case 3: loadSceneB(); break;
        case 4: loadSceneC(); break;
        case 5: loadSceneC(); break;
        case 6: loadSceneD(); break;
        case 7: loadSceneE(); break;
        case 8: {
            this->cam = Camera(glm::vec3(-3,0,0), glm::vec3(1,0,0), glm::vec3(0,1,0), (float) 60.0f * (M_PI / 180.0f));
            loadSceneA(); break;
        }
        default: break;
    }
}

void Scene::loadSceneA() {
    // Light
    lights.push_back(new Light(glm::vec3(-2.0f, 1.0f, 1.0f), 1.0f));

    // Red sphere
    Shape* redSphere = new Ellipsoid(
        glm::vec3(-0.5f, -1.0f, 1.0f), // position
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), // rotation
        glm::vec3(1.0f, 1.0f, 1.0f), // scale
        new BlinnPhong( // material
            glm::vec3(1.0f,0.0f,0.0f), // kd
            glm::vec3(1.0f,1.0f,0.5f), // ks
            glm::vec3(0.1f,0.1f,0.1f), // ka
            100.0f
        )
    );

    // Green sphere
    Shape* greenSphere = new Ellipsoid(
        glm::vec3(0.5f, -1.0f, -1.0f), // position
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), // rotation
        glm::vec3(1.0f, 1.0f, 1.0f), // scale
        new BlinnPhong( // material
            glm::vec3(0.0f,1.0f,0.0f), // kd
            glm::vec3(1.0f,1.0f,0.5f), // ks
            glm::vec3(0.1f,0.1f,0.1f), // ka
            100.0f // s
        )
    );

    // Blue sphere
    Shape* blueSphere = new Ellipsoid(
        glm::vec3(0.0f, 1.0f, 0.0f), // position
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), // rotation
        glm::vec3(1.0f, 1.0f, 1.0f), // scale
        new BlinnPhong( // material
            glm::vec3(0.0f,0.0f,1.0f), // kd
            glm::vec3(1.0f,1.0f,0.5f), // ks
            glm::vec3(0.1f,0.1f,0.1f), // ka
            100.0f // s
        )
    );

    // Add to scene
    shapes.push_back(redSphere);
    shapes.push_back(greenSphere);
    shapes.push_back(blueSphere);
}

void Scene::loadSceneB() {
    // Light
    lights.push_back(new Light(glm::vec3(1.0f, 2.0f, 2.0f), 0.5f));
    lights.push_back(new Light(glm::vec3(-1.0f, 2.0f, -1.0f), 0.5f));

    // Red sphere
    Shape* redSphere = new Ellipsoid(
        glm::vec3(0.5f, 0.0f, 0.5f), // position
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), // rotation
        glm::vec3(0.5f, 0.6f, 0.2f), // scale
        new BlinnPhong( // material
            glm::vec3(1.0f,0.0f,0.0f), // kd
            glm::vec3(1.0f,1.0f,0.5f), // ks
            glm::vec3(0.1f,0.1f,0.1f), // ka
            100.0f
        )
    );

    // // Green sphere
    Shape* greenSphere = new Ellipsoid(
        glm::vec3(-0.5f, 0.0f, -0.5f), // position
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), // rotation
        glm::vec3(1.0f, 1.0f, 1.0f), // scale
        new BlinnPhong( // material
            glm::vec3(0.0f,1.0f,0.0f), // kd
            glm::vec3(1.0f,1.0f,0.5f), // ks
            glm::vec3(0.1f,0.1f,0.1f), // ka
            100.0f // s
        )
    );

    // plane
    Shape* plane = new Plane(
        glm::vec3(0.0f, 1.0f, 0.0f), // normal
        glm::vec3(0.0f, -1.0f, 0.0f), // position
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), // rotation
        new BlinnPhong( // material
            glm::vec3(1.0f,1.0f,1.0f), // kd
            glm::vec3(0.0f,0.0f,0.0f), // ks
            glm::vec3(0.1f,0.1f,0.1f), // ka
            0.0f // s
        )
    );

    // Add to scene
    shapes.push_back(redSphere);
    shapes.push_back(greenSphere);
    shapes.push_back(plane);
}

void Scene::loadSceneC() {
    // Light
    lights.push_back(new Light(glm::vec3(-1.0f, 2.0f, 1.0f), 0.5f));
    lights.push_back(new Light(glm::vec3(0.5f, -0.5f, 0.0f), 0.5f));

    // Red sphere
    Shape* redSphere = new Ellipsoid(
        glm::vec3(0.5f, -0.7f, 0.5f), // position
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), // rotation
        glm::vec3(0.3f, 0.3f, 0.3f), // scale
        new BlinnPhong( // material
            glm::vec3(1.0f,0.0f,0.0f), // kd
            glm::vec3(1.0f,1.0f,0.5f), // ks
            glm::vec3(0.1f,0.1f,0.1f), // ka
            100.0f
        )
    );

    // // Green sphere
    Shape* blueSphere = new Ellipsoid(
        glm::vec3(1.0f, -0.7f, 0.0f), // position
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), // rotation
        glm::vec3(0.3f, 0.3f, 0.3f), // scale
        new BlinnPhong( // material
            glm::vec3(0.0f,0.0f,1.0f), // kd
            glm::vec3(1.0f,1.0f,0.5f), // ks
            glm::vec3(0.1f,0.1f,0.1f), // ka
            100.0f // s
        )
    );

    Shape* reflSphere1 = new Ellipsoid(
        glm::vec3(-0.5f, 0.0f, -0.5f), // position
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), // rotation
        glm::vec3(1.0f, 1.0f, 1.0f), // scale
        new Reflective() // material
    );

    Shape* reflSphere2 = new Ellipsoid(
        glm::vec3(1.5f, 0.0f, -1.5f), // position
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), // rotation
        glm::vec3(1.0f, 1.0f, 1.0f), // scale
        new Reflective() // material
    );

    // plane
    Shape* floor = new Plane(
        glm::vec3(0.0f, 1.0f, 0.0f), // normal
        glm::vec3(0.0f, -1.0f, 0.0f), // position
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), // rotation
        new BlinnPhong( // material
            glm::vec3(1.0f,1.0f,1.0f), // kd
            glm::vec3(0.0f,0.0f,0.0f), // ks
            glm::vec3(0.1f,0.1f,0.1f), // ka
            0.0f // s
        )
    );

    Shape* wall = new Plane(
        glm::vec3(0.0f, 0.0f, 1.0f), // normal
        glm::vec3(0.0f, 0.0f, -3.0f), // position
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), // rotation
        new BlinnPhong( // material
            glm::vec3(1.0f,1.0f,1.0f), // kd
            glm::vec3(0.0f,0.0f,0.0f), // ks
            glm::vec3(0.1f,0.1f,0.1f), // ka
            0.0f // s
        )
    );

    // Add to scene
    shapes.push_back(redSphere);
    shapes.push_back(blueSphere);
    shapes.push_back(reflSphere1);
    shapes.push_back(reflSphere2);
    shapes.push_back(floor);
    shapes.push_back(wall);
}

void Scene::loadSceneD() {
    // Light
    lights.push_back(new Light(glm::vec3(-1.0f, 1.0f, 1.0f), 1.0f));

    // objects
    Shape* bunny = new Mesh(
        RESOURCE_DIR + "bunny.obj",
        glm::vec3(0.0f, 0.0f, 0.0f), // position
        glm::vec4(0.0f, 1.0f, 0.0f, 0.0f), // rotation
        glm::vec3(1.0f, 1.0f, 1.0f), // scale
        new BlinnPhong(
            glm::vec3(0.0f,0.0f,1.0f), // kd
            glm::vec3(1.0f,1.0f,0.5f), // ks
            glm::vec3(0.1f,0.1f,0.1f), // ka
            100.0f
        )
    );

    shapes.push_back(bunny);
}

void Scene::loadSceneE() {
    // Light
    lights.push_back(new Light(glm::vec3(1.0f, 1.0f, 2.0f), 1.0f));

    // objects
    Shape* bunny = new Mesh(
        RESOURCE_DIR + "bunny.obj",
        glm::vec3(0.3f, -1.5f, 0.0f), // position
        glm::vec4(20.0f*DEG_TO_RAD, 1.0f, 0.0f, 0.0f), // rotation
        glm::vec3(1.5f, 1.5f, 1.5f), // scale
        new BlinnPhong(
            glm::vec3(0.0f,0.0f,1.0f), // kd
            glm::vec3(1.0f,1.0f,0.5f), // ks
            glm::vec3(0.1f,0.1f,0.1f), // ka
            100.0f
        )
    );

    shapes.push_back(bunny);
}

Collision* Scene::shootRay(Ray& ray) {
    Hit* closestHit = nullptr;
    Shape* closestObj = nullptr;
    for (Shape* obj : shapes) {
        Hit* hit = obj->collider(ray);
        if (hit) {
            if (closestHit == nullptr || hit->t < closestHit->t) {
                closestHit = hit;
                closestObj = obj;
            }
        }
    }
    if (closestHit) return new Collision(closestHit, closestObj);
    else return nullptr;
}

glm::vec3 Scene::computeColor(Ray& ray, int depth) {
    Collision* col = shootRay(ray);
    if (col) {
        glm::vec3 fragPos = col->hit->x;
        glm::vec3 fragNor = normalize(col->hit->n);
        if (col->obj->mat->type == Material::BLINN_PHONG) {
            std::vector<Light*> activeLights;
            for (Light* l : lights) {
                glm::vec3 l_vec = l->position - fragPos;
                Ray sray (fragPos, normalize(l_vec));
                Collision* scol = shootRay(sray);
                if (!scol || length(scol->hit->x - fragPos) > length(l_vec)) { // if not occluded
                    activeLights.push_back(l);
                }
            }
            return col->obj->mat->computeFrag(ray.v, fragPos, fragNor, activeLights);
        }
        else if (col->obj->mat->type == Material::REFLECTIVE) {
            if (depth == Scene::MAX_BOUNCES) {
                return background;
            }
            glm::vec3 reflection = glm::reflect(ray.v, fragNor);
            Ray rray (fragPos, reflection);
            return computeColor(rray, depth+1);
        }
        return background;
    }
    else {
        return background;
    }
}