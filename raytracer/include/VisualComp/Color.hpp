/*
** EPITECH PROJECT, 2024
** Color.hpp
** File description:
** Color
*/

#ifndef COLOR_HPP
#define COLOR_HPP

#include <cmath>
#include <iostream>
#include <fstream>
#include "../Math/Vector3D.hpp"

using namespace Math;

namespace VisualComp {
    class Color {
        private:
            Vector3D _rgb; // RGB color components
        
        public:
            Color() = default;
            Color(double r, double g, double b);
            Color(Vector3D rgb);
            ~Color() = default;

            Vector3D getRGB() const;
            void setRGB(const Vector3D& other);

            Color operator+(const Color& other) const;
            Color operator-(const Color& other) const;
            Color operator*(double scalar) const;
            Color& operator+=(const Color& other);
            Color& operator*=(double scalar);
            Color& operator/=(double scalar);
    };
}

#endif // COLOR_HPP

