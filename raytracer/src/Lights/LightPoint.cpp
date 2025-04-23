/*
** EPITECH PROJECT, 2024
** LightPoint
** File description:
** Raytracer
*/

#include <iostream>
#include "Lights/LightPoint.hpp"

extern "C"
{
    Lights::LightPoint *entry_point(const char *input)
    {
        return new Lights::LightPoint(input);
    }
}

Lights::LightPoint::LightPoint(const std::string &line) : ALight()
{
    libconfig::Config cfg;

    try {
        cfg.readString(line);
    } catch(const libconfig::ParseException &pex) {
        std::cerr << "syntax error in line: " << pex.getError() << " -> " << pex.getLine() << std::endl;
        throw;
    }
    int x, y, z;
    try {
        const libconfig::Setting& root = cfg.getRoot()["light"];
        root.lookupValue("intensity", _intensity);
        const libconfig::Setting& values = root["values"];
        values.lookupValue("x", x);
        values.lookupValue("y", y);
        values.lookupValue("z", z);

        if (root.exists("offset")) {
            int offsetX, offsetY, offsetZ;
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
    _position = Math::Point3D(x, y, z);
    _position = _translation.applyTranslation(_position);
}

double Lights::LightPoint::computeLighting(const Math::Point3D &hitPoint,
                const Math::Vector3D &primitiveNormal)
{
    Math::Vector3D lightDirection = _position - hitPoint;
    double normal_dot_light = lightDirection.dot(primitiveNormal);

    if (normal_dot_light > 0) {
        return this->_intensity * (normal_dot_light / (primitiveNormal.length()
        * lightDirection.length()));
    }
    return 0;
}
