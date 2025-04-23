/*
** EPITECH PROJECT, 2024
** Sphere
** File description:
** Raytracer
*/

#include <iostream>
#include "Primitives/Sphere.hpp"

using namespace Primitive;

extern "C"
{
    Sphere *entry_point(const char *input)
    {
        return new Sphere(input);
    }
}

Sphere::Sphere(const std::string &line) : APrimitive()
{
    libconfig::Config cfg;

    try {
        cfg.readString(line);
    } catch(const libconfig::ParseException &pex) {
        std::cerr << "syntax error in line: " << pex.getError() << " -> " << pex.getLine() << std::endl;
        throw;
    }
    int x, y, z;
    double r;
    int red, green, blue;
    int offsetX, offsetY, offsetZ;
    try {
        const libconfig::Setting& root = cfg.getRoot()["sphere"];
        root.lookupValue("x", x);
        root.lookupValue("y", y);
        root.lookupValue("z", z);
        root.lookupValue("r", r);
        const libconfig::Setting& colors = root["color"]; // parsing color attributes
        colors.lookupValue("r", red);
        colors.lookupValue("g", green);
        colors.lookupValue("b", blue);

        if (root.exists("offset")) {
            const libconfig::Setting& offset = root["offset"];
            offset.lookupValue("x", offsetX);
            offset.lookupValue("y", offsetY);
            offset.lookupValue("z", offsetZ);
            _translation = Transformations::Translation(Math::Point3D(offsetX, offsetY, offsetZ));
        } else {
            _translation = Transformations::Translation(Math::Point3D(0, 0, 0));
        }
    } catch(const libconfig::SettingNotFoundException &nfex) {
        std::cerr << "required setting not found: " << nfex.getPath() << std::endl;
        throw;
    }
    _center = Math::Point3D(x, y, z);
    _center = _translation.applyTranslation(_center);
    _radius = r;
    _color.setRGB(Math::Vector3D(red, green, blue));
}

Math::Point3D Sphere:: getCenter() const {
    return _center;
}

double Sphere::getRadius() const {
    return _radius;
}

bool Sphere::hits(const RayTracer::Ray& ray, double t_min, double t_max, RayTracer::HitRecord& rec) const
{
    Math::Vector3D oc = _center - ray.getOrigin();
    auto a = ray.getDirection().length_squared();
    auto h = ray.getDirection().dot(oc);
    auto c = oc.length_squared() - _radius * _radius;

    auto discriminant = h*h - a*c;
    if (discriminant < 0)
        return false;

    auto sqrtd = sqrt(discriminant);
    auto root = (h - sqrtd) / a;
    if (!(t_min < root && root < t_max)) {
        root = (h + sqrtd) / a;
        if (!(t_min < root && root < t_max))
            return false;
    }
    rec.setT(root);
    rec.setPoint(ray.pointAt(rec.getT()));
    Math::Vector3D outward_normal = (rec.getPoint() - _center) / _radius;
    rec.setFaceNormal(ray, outward_normal);
    return true;
}
