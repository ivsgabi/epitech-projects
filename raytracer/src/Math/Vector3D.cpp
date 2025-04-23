/*
** EPITECH PROJECT, 2024
** Vector3D.cpp
** File description:
** Raytracer
*/

#include "Math/Vector3D.hpp"

Math::Vector3D::Vector3D() : _x(0), _y(0), _z(0) {}

Math::Vector3D::Vector3D(double x, double y, double z) : _x(x), _y(y), _z(z) {}

double Math::Vector3D::getX() const {
    return _x;
}

double Math::Vector3D::getY() const {
    return _y;
}

double Math::Vector3D::getZ() const {
    return _z;
}

Math::Vector3D Math::Vector3D::operator+(const Vector3D& v) const
{
    return {_x + v._x, _y + v._y, _z + v._z};
}

Math::Vector3D Math::Vector3D::operator-(const Vector3D& v) const
{
    return {_x - v._x, _y - v._y, _z - v._z};
}

Math::Vector3D Math::Vector3D::operator/(double scalar) const
{
    return {_x / scalar, _y / scalar, _z / scalar};
}
Math::Vector3D Math::Vector3D::operator*(double scalar) const
{
    return {_x * scalar, _y * scalar, _z * scalar};
}

Math::Vector3D Math::Vector3D::operator-() const {
    return Vector3D(-_x, -_y, -_z);
}

Math::Vector3D& Math::Vector3D::operator+=(const Vector3D& v)
{
    _x += v._x;
    _y += v._y;
    _z += v._z;
    return *this;
}
Math::Vector3D& Math::Vector3D::operator-=(const Vector3D& v)
{
    _x -= v._x; 
    _y -= v._y; 
    _z -= v._z;
    return *this;
}

Math::Vector3D& Math::Vector3D::operator*=(double scalar)
{
    _x *= scalar; _y *= scalar; _z *= scalar;
    return *this;
}
Math::Vector3D& Math::Vector3D::operator/=(double scalar)
{
    _x /= scalar; _y /= scalar; _z /= scalar;
    return *this;
}

Math::Vector3D& Math::Vector3D::normalize()
{
    double length = std::sqrt(_x * _x + _y * _y + _z * _z);

    if (length > 0) {
        _x /= length;
        _y /= length;
        _z /= length;
    }
    return *this;
}

double Math::Vector3D::dot(const Vector3D& v) const
{
    return _x * v._x + _y * v._y + _z * v._z;
}

double Math::Vector3D::length() const
{
    return std::sqrt(_x*_x + _y*_y + _z*_z);
}

double Math::Vector3D::length_squared() const
{
    return (_x*_x + _y*_y + _z*_z);
}
