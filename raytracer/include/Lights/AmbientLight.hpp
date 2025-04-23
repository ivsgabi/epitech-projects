/*
** EPITECH PROJECT, 2024
** AmbientLight
** File description:
** Raytracer
*/

#ifndef AMBIENT_LIGHT_HPP_
#define AMBIENT_LIGHT_HPP_
#include "Lights/ALight.hpp"

namespace Lights {
    class AmbientLight : public Lights::ALight {
        public:
            AmbientLight(const std::string &line);
            ~AmbientLight() = default;
            double computeLighting(const Math::Point3D &hitPoint,
            const Math::Vector3D &primitiveNormal) final;
    };
}

#endif /* !AMBIENT_LIGHT_HPP_ */
