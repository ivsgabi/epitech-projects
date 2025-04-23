/*
** EPITECH PROJECT, 2024
** Rectangle3D.cpp
** File description:
** Raytracer
*/

#include "RayTracer/Rectangle3D.hpp"
using namespace RayTracer;

Math::Point3D Rectangle3D:: getCenter() const
{
    return _center;
}

Math::Vector3D Rectangle3D:: getHorizontalVec() const
{
    return _horizontalVec;
}

Math::Vector3D Rectangle3D:: getVerticalVec() const
{
    return _verticalVec;
}

Rectangle3D:: Rectangle3D
(const Math::Point3D& center, const Math::Vector3D& horizontal, const Math::Vector3D& vertical)
: _center(center), _horizontalVec(horizontal), _verticalVec(vertical) {}

Math::Point3D Rectangle3D:: getPointAt(double u, double v) const
{
    return _center - (_horizontalVec * 0.5) + (_horizontalVec * u) - (_verticalVec * 0.5) + (_verticalVec * v);
}