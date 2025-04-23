/*
** EPITECH PROJECT, 2024
** Sphere.hpp
** File description:
** Sphere
*/

#ifndef SPHERE_HPP_
#define SPHERE_HPP_

#include "../RayTracer/Ray.hpp"
#include "../RayTracer/HitRecord.hpp"
#include "Primitives/APrimitive.hpp"

namespace Primitive {
    class Sphere : public APrimitive {
        private:
            Math::Point3D _center;
            double _radius;
            
        public:
            Sphere(const std::string &line);
            ~Sphere() = default;
            Math::Point3D getCenter() const;
            double getRadius() const;
            bool hits(const RayTracer::Ray& ray, double t_min, double t_max, RayTracer::HitRecord& rec) const final;
    };
}

#endif /* !SPHERE_HPP_ */
