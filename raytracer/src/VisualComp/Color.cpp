/*
** EPITECH PROJECT, 2024
** Color.cpp
** File description:
** Color
*/

#include "VisualComp/Color.hpp"
using namespace VisualComp;

Color::Color(double r, double g, double b) : _rgb(r, g, b) {}

Color::Color(Vector3D rgb) : _rgb(rgb) {}

Vector3D Color:: getRGB() const {
    return _rgb;
}

void Color:: setRGB(const Vector3D& other) {
    _rgb = other;
}

Color Color:: operator+(const Color& other) const {
    return Color(_rgb + other.getRGB());
}

Color Color:: operator-(const Color& other) const {
    return Color(_rgb - other.getRGB());
}

Color Color:: operator*(double scalar) const {
    return Color(_rgb * scalar);
}

Color& Color:: operator+=(const Color& other) {
    _rgb += other.getRGB();
    return *this;
}

Color& Color:: operator*=(double scalar) {
    _rgb *= scalar;
    return *this;
}

Color& Color:: operator/=(double scalar) {
    _rgb /= scalar;
    return *this;
}