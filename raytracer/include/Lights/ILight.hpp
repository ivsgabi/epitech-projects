/*
** EPITECH PROJECT, 2024
** ILight.hpp
** File description:
** Raytracer
*/

#ifndef ILIGHT_HPP_
#define ILIGHT_HPP_
#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"

namespace Lights {
    /*!
        All lights inherit from the ILight interface
    */
    class ILight {
        public:
            virtual ~ILight() = default;
            virtual double computeLighting(const Math::Point3D &hitPoint,
                const Math::Vector3D &primitiveNormal) = 0;
    };
}

#endif /* !ILIGHT_HPP_ */
