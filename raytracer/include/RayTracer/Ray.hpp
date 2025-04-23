/*
** EPITECH PROJECT, 2024
** Ray.hpp
** File description:
** Ray
*/

#ifndef RAY_HPP_
#define RAY_HPP_

#include "../Math/Point3D.hpp"

namespace RayTracer {
    class Ray {
        private:
            Math::Point3D _origin;
            Math::Vector3D _direction;

        public:
            Ray() = default;
            Ray(const Math::Point3D& origin, const Math::Vector3D& direction);
            ~Ray() = default;

            Math::Point3D pointAt(double t) const;

            Math::Point3D getOrigin() const;
            Math::Vector3D getDirection() const;
    };
} // namespace RayTracer

#endif /* !RAY_HPP_ */
