/*
** EPITECH PROJECT, 2024
** Plane.hpp
** File description:
** Plane
*/

#ifndef PLANE_HPP_
#define PLANE_HPP_
#include "APrimitive.hpp"

namespace Primitive {
    class Plane : public APrimitive {
        private:
            Math::Point3D _point;
            Math::Vector3D _normal;
        public:
            Plane(const std::string &line);
            ~Plane() = default;
            Math::Point3D getPoint() const;
            Math::Vector3D getNormalVec() const;
            bool hits(const RayTracer::Ray& ray, double t_min, double t_max, RayTracer::HitRecord& rec) const;
    };
}

#endif /* !PLANE_HPP_ */