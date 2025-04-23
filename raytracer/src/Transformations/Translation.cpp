/*
** EPITECH PROJECT, 2024
** Translation
** File description:
** RayTracer
*/

#include "Transformations/Translation.hpp"

Transformations::Translation::Translation(const Math::Point3D &point) : _offsetPoint(point) {}

Transformations::Translation::Translation(const Math::Vector3D &vector) : _offsetVector(vector) {}

Math::Point3D Transformations::Translation::applyTranslation(const Math::Point3D &point)
{
    int resX, resY, resZ;

    resX = point.getX() + _offsetPoint.getX();
    resY = point.getY() + _offsetPoint.getY();
    resZ = point.getZ() + _offsetPoint.getZ();

    Math::Point3D resPoint(resX, resY, resZ);
    return (resPoint);
}

Math::Vector3D Transformations::Translation::applyTranslation(const Math::Vector3D &vector)
{
    int resX, resY, resZ;

    resX = vector.getX() + _offsetVector.getX();
    resY = vector.getY() + _offsetVector.getY();
    resZ = vector.getZ() + _offsetVector.getZ();

    Math::Vector3D resVector(resX, resY, resZ);
    return (resVector);
}