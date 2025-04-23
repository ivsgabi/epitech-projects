/*
** EPITECH PROJECT, 2024
** AmbientLight
** File description:
** Raytracer
*/

#include "Lights/AmbientLight.hpp"

extern "C"
{
    Lights::AmbientLight *entry_point(const char *input)
    {
        return new Lights::AmbientLight(input);
    }
}

Lights::AmbientLight::AmbientLight(const std::string &line) : ALight()
{
    _intensity = std::atof(line.c_str());
}

double Lights::AmbientLight::computeLighting(UNUSED const Math::Point3D &hitPoint,
                UNUSED const Math::Vector3D &primitiveNormal)
{
    return this->_intensity;
}
