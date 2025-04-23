/*
** EPITECH PROJECT, 2024
** LightDirection
** File description:
** Raytracer
*/

#ifndef LIGHT_DIRECTION_HPP_
#define LIGHT_DIRECTION_HPP_
#include "Lights/ALight.hpp"

namespace Lights {
    class LightDirection : public Lights::ALight {
        public:
            LightDirection(const std::string &line);
            ~LightDirection() = default;
            double computeLighting(const Math::Point3D &hitPoint,
                const Math::Vector3D &primitiveNormal) final;

        private:
            Math::Vector3D _direction;
    };
}

#endif /* !LIGHT_DIRECTION_HPP_ */
