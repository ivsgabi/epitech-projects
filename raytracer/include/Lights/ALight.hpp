/*
** EPITECH PROJECT, 2024
** ALight.hpp
** File description:
** Raytracer
*/

#ifndef ALIGHT_HPP_
#define ALIGHT_HPP_
#include <string>
#include <libconfig.h++>
#include "Transformations/Translation.hpp"
#include "Lights/ILight.hpp"
#define UNUSED __attribute__((unused))

namespace Lights {
    class ALight : public ILight {
        public:
            ALight() = default;
            virtual ~ALight() = default;

        protected:
            double _intensity;
            Transformations::Translation _translation;
    };
}

#endif /* !ALIGHT_HPP_ */
