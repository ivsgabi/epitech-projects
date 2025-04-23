/*
** EPITECH PROJECT, 2024
** Scene
** File description:
** Raytracer
*/

#include "Scene/Scene.hpp"
#include <iostream>

bool Scene::hits(const RayTracer::Ray& ray, double t_min, double t_max, RayTracer::HitRecord& rec,
    VisualComp::Color &color) const
{
    RayTracer::HitRecord tempRec;
    bool hit = false;

    for (const auto& object : this->_primitives) {
        if (object->hits(ray, t_min, t_max, tempRec)) {
            hit = true;
            rec = tempRec;
            color = object->getColor();
        }
    }
    return hit;
}

double Scene::computeTotalLighting(const Math::Point3D &hitPoint, const Math::Vector3D &primitiveNormal) const
{
    double i = 0;

    for (auto &light : this->_lights) {
        i += light->computeLighting(hitPoint, primitiveNormal);
    }
    return i;
}