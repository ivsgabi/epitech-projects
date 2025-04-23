/*
** EPITECH PROJECT, 2024
** Point3D
** File description:
** RayTracer
*/

#include "Math/Point3D.hpp"
using namespace Math;

Point3D::Point3D() : _x(0), _y(0), _z(0) {};

Point3D::Point3D(double x, double y, double z) : _x(x), _y(y), _z(z) {}

double Point3D::getX() const {
    return _x;
}

double Point3D::getY() const {
    return _y;
}

double Point3D::getZ() const {
    return _z;
}

Point3D Point3D::operator+(const Vector3D& v) const
{
    return {_x + v.getX(), _y + v.getY(), _z + v.getZ()};
}

Vector3D Point3D::operator-(const Point3D& other) const
{
    return Vector3D(_x - other._x, _y - other._y, _z - other._z);
}

Point3D Point3D:: operator-(const Vector3D& vec) const {
    return Point3D(_x - vec.getX(), _y - vec.getY(), _z - vec.getZ());
}

Point3D& Point3D::operator+=(const Vector3D& v)
{
    _x += v.getX();
    _y += v.getY();
    _z += v.getZ();
    return *this;
}

double Point3D:: distanceTo(const Point3D& other) const {
    return std::sqrt((_x - other._x) * (_x - other._x) +
    (_y - other._y) * (_y - other._y) +
    (_z - other._z) * (_z - other._z));
}

Point3D Point3D:: translate(const Point3D& translation) const {
    return Point3D(_x + translation._x, _y + translation._y, _z + translation._z);
}
