/*
** EPITECH PROJECT, 2024
** Ray.cpp
** File description:
** Raytracer
*/

#include "RayTracer/Ray.hpp"
using namespace RayTracer;

Ray:: Ray(const Math::Point3D& origin, const Math::Vector3D& direction) : _origin(origin), _direction(direction) {}

Math::Point3D Ray:: pointAt(double t) const {
    return _origin + (_direction * t);
}

Math::Point3D Ray:: getOrigin() const {
    return _origin;
}

Math::Vector3D Ray:: getDirection() const {
    return _direction;
}