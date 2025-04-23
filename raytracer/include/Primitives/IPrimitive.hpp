/*
** EPITECH PROJECT, 2024
** IPrimitive.hpp
** File description:
** IPrimitive
*/

#ifndef IPRIMITIVE_HPP_
#define IPRIMITIVE_HPP_

#include "../Math/Point3D.hpp"
#include "../RayTracer/Ray.hpp"
#include "../RayTracer/HitRecord.hpp"
#include "VisualComp/Color.hpp"

namespace Primitive {
    /*!
        All primitives inherit from the IPrimitive interface
    */
    class IPrimitive {
        public:
            virtual ~IPrimitive() = default;
            virtual bool hits(const RayTracer::Ray& ray, double t_min, double t_max, RayTracer::HitRecord& rec) const = 0;
            virtual VisualComp::Color getColor() const = 0;
    };
}

#endif /* !IPRIMITIVE_HPP_ */
