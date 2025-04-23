/*
** EPITECH PROJECT, 2024
** LightPoint
** File description:
** Raytracer
*/

#ifndef LIGHTPOINT_HPP_
#define LIGHTPOINT_HPP_
#include "Lights/ALight.hpp"

namespace Lights {
    class LightPoint : public Lights::ALight {
        public:
            LightPoint(const std::string &line);
            ~LightPoint() = default;
            double computeLighting(const Math::Point3D &hitPoint,
                const Math::Vector3D &primitiveNormal) final;

        private:
            Math::Point3D _position;
    };
}

#endif /* !LIGHTPOINT_HPP_ */
