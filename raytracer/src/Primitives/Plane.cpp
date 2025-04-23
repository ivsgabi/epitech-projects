/*
** EPITECH PROJECT, 2024
** Plane.cpp
** File description:
** Plane
*/

#include <stdbool.h>
#include "Primitives/Plane.hpp"
using namespace Primitive;

extern "C"
{
    Plane *entry_point(const char *input)
    {
        return new Plane(input);
    }
}

Plane::Plane(const std::string &line) : APrimitive()
{
    libconfig::Config cfg;

    try {
        cfg.readString(line);
    } catch(const libconfig::ParseException &pex) {
        std::cerr << "syntax error in line: " << pex.getError() << " -> " << pex.getLine() << std::endl;
        throw;
    }
    int pointX, pointY, pointZ;
    int normalX, normalY, normalZ;
    int red, green, blue;
    try {
        const libconfig::Setting& plane = cfg.getRoot()["plane"];

        plane["point"].lookupValue("x", pointX);
        plane["point"].lookupValue("y", pointY);
        plane["point"].lookupValue("z", pointZ);

        plane["normal"].lookupValue("x", normalX);
        plane["normal"].lookupValue("y", normalY);
        plane["normal"].lookupValue("z", normalZ);

        plane["color"].lookupValue("r", red);
        plane["color"].lookupValue("g", green);
        plane["color"].lookupValue("b", blue);

    } catch(const libconfig::SettingNotFoundException &nfex) {
        std::cerr << "required setting not found: " << nfex.getPath() << std::endl;
        throw;
    }
    _point = Math::Point3D(pointX, pointY, pointZ); 
    _normal = Math::Vector3D(normalX, normalY, normalZ);
    _color.setRGB(Math::Vector3D(red, green, blue));
}

Math::Point3D Plane:: getPoint() const {
    return _point;
}

Math::Vector3D Plane:: getNormalVec() const {
    return _normal;
}

bool Plane::hits(const RayTracer::Ray& ray, double t_min, double t_max, RayTracer::HitRecord& rec) const
{
    double denom = _normal.dot(ray.getDirection().normalize());
    if (std::abs(denom) > 0) {
        Math::Vector3D p0ToOrigin = _point - ray.getOrigin();
        double t = (p0ToOrigin.normalize()).dot(_normal) / denom;
        if (t < t_min) {
            return false;
        }
        rec.setT(t);
        rec.setPoint(ray.pointAt(t));
        rec.setFaceNormal(ray, _normal);
        return true;
    }
    return false;
}
