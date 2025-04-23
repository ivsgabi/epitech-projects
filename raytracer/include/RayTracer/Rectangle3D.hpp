/*
** EPITECH PROJECT, 2024
** Rectangle3D.hpp
** File description:
** Rectangle3D
*/

#ifndef RECTANGLE3D_HPP_
#define RECTANGLE3D_HPP_

#include "../Math/Point3D.hpp"

namespace RayTracer {
    class Rectangle3D {
        private:
            Math::Point3D _center;
            Math::Vector3D _horizontalVec;
            Math::Vector3D _verticalVec;

        public:
            Rectangle3D() = default;
            Rectangle3D(const Math::Point3D& center, const Math::Vector3D& horizontal, const Math::Vector3D& vertical);
            ~Rectangle3D() = default;

            Math::Point3D getCenter() const;
            Math::Vector3D getHorizontalVec() const;
            Math::Vector3D getVerticalVec() const;
            
            Math::Point3D getPointAt(double u, double v) const;
    };
};

#endif /* !RECTANGLE3D_HPP_ */
