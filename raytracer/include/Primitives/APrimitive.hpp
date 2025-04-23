/*
** EPITECH PROJECT, 2024
** APrimitive.hpp
** File description:
** APrimitive
*/

#ifndef APRIMITIVE_HPP_
#define APRIMITIVE_HPP_
#include <string>
#include <libconfig.h++>
#include "IPrimitive.hpp"
#include "Transformations/Translation.hpp"
#include "VisualComp/Color.hpp"

namespace Primitive {
    class APrimitive : public IPrimitive {
        public:
            APrimitive() = default;
            virtual ~APrimitive() = default;
            VisualComp::Color getColor() const final;

        protected:
            VisualComp::Color _color;
            Transformations::Translation _translation;
    };
}

#endif /* !APRIMITIVE_HPP_ */
