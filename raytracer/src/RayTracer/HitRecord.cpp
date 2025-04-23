/*
** EPITECH PROJECT, 2024
** HitRecord.cpp
** File description:
** HitRecord
*/

#include "RayTracer/HitRecord.hpp"
using namespace RayTracer;

HitRecord::HitRecord() : _t(0.0), _frontFace(true) {}

void HitRecord:: setFaceNormal(const Ray& ray, const Math::Vector3D& outward_normal)
{
    _frontFace = ray.getDirection().dot(outward_normal) < 0;
    // The sign of the scalar product tells us if the ray hits surface
    // from the inside or the outside
    // If dot returns a negative value, then the ray hits from the outside
    // If ray hits from the inside, the normal vector is reversed to ensure correct calculations of shadows
    if (_frontFace == true)
        _normal = outward_normal;
    else
        _normal = outward_normal * -1;
}

Math::Point3D HitRecord:: getPoint() const
{
    return _point;
}

Math::Vector3D HitRecord:: getNormal() const {
    return _normal;
}

double HitRecord:: getT() const {
    return _t;
}

bool HitRecord:: isFrontFace() const {
    return _frontFace;
}

void HitRecord:: setNormal(Math::Vector3D normal) {
    _normal = normal;
    
}

void HitRecord:: setPoint(Math::Point3D point) {
    _point = point;
}

void HitRecord:: setT(double t) {
    _t = t;
}

void HitRecord:: setBoolFrontFace(bool frontFace) {
    _frontFace = frontFace;
}