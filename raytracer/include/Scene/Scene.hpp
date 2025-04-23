/*
** EPITECH PROJECT, 2024
** Scene
** File description:
** Raytracer
*/

#ifndef SCENE_HPP_
#define SCENE_HPP_
#include <vector>
#include <memory>
#include "Lights/ILight.hpp"
#include "VisualComp/Color.hpp"
#include "Primitives/IPrimitive.hpp"

class Scene {
    public:
        Scene() = default;
        ~Scene() = default;
        bool hits(const RayTracer::Ray& ray, double t_min, double t_max, RayTracer::HitRecord& rec, VisualComp::Color &color) const;
        double computeTotalLighting(const Math::Point3D &hitPoint, const Math::Vector3D &primitiveNormal) const;
        std::vector<std::shared_ptr<Lights::ILight>> _lights;
        std::vector<std::shared_ptr<Primitive::IPrimitive>> _primitives;
};

#endif /* !SCENE_HPP_ */
