/*
** EPITECH PROJECT, 2024
** LightDirection
** File description:
** Raytracer
*/

#include <iostream>
#include "Lights/LightDirection.hpp"

extern "C"
{
    Lights::LightDirection *entry_point(const char *input)
    {
        return new Lights::LightDirection(input);
    }
}

Lights::LightDirection::LightDirection(const std::string &line) : ALight()
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
            _translation = Transformations::Translation(Math::Vector3D(offsetX, offsetY, offsetZ));
        } else {
            _translation = Transformations::Translation(Math::Vector3D(0, 0, 0));
        }
    } catch(const libconfig::SettingNotFoundException &nfex) {
        std::cerr << "required setting not found: " << nfex.getPath() << std::endl;
        throw;
    }

    _direction = Math::Vector3D(x, y, z);
    _direction = _translation.applyTranslation(_direction);
}

double Lights::LightDirection::computeLighting(UNUSED const Math::Point3D &hitPoint,
                const Math::Vector3D &primitiveNormal)
{
    double normal_dot_light = primitiveNormal.dot(this->_direction);

    if (normal_dot_light > 0) {
        return this->_intensity * (normal_dot_light / (primitiveNormal.length()
        * this->_direction.length()));
    }
    return 0;
}
