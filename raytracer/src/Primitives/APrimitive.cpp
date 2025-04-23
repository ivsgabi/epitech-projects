/*
** EPITECH PROJECT, 2024
** APrimitive
** File description:
** Raytracer
*/

#include "Primitives/APrimitive.hpp"

VisualComp::Color Primitive::APrimitive::getColor() const
{
    return this->_color;
}