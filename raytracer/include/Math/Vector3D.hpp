/*
** EPITECH PROJECT, 2024
** Vector3D.hpp
** File description:
** Vector3D
*/


#ifndef VECTOR3D_HPP_
#define VECTOR3D_HPP_

#include <cmath>

namespace Math {
    class Vector3D {
        private:
            double _x;
            double _y;
            double _z;
        public:
            Vector3D();
            Vector3D(double x, double y, double z);
            ~Vector3D() = default;

            double getX() const;
            double getY() const;
            double getZ() const;

            void setX(double x) {_x = x;};
            void setY(double y) {_y = y; };
            void setZ(double z) {_z = z; };

            Vector3D operator+(const Vector3D& v) const;
            Vector3D operator-(const Vector3D& v) const;
            Vector3D operator/(double scalar) const;
            Vector3D operator*(double scalar) const;

            Vector3D operator-() const;
            
            Vector3D& operator+=(const Vector3D& v);
            Vector3D& operator-=(const Vector3D& v);
            Vector3D& operator*=(double scalar);
            Vector3D& operator/=(double scalar);

            Vector3D& normalize();

            //scalar product of two vectors =  x * v.x + y * v.y + z * v.z
            double dot(const Vector3D& v) const;

            // length of a vector square root of ((x * x) + (y * y) + (z * z))
            double length() const;
            double length_squared() const;

    };
} // namespace Math


inline Math::Vector3D unit_vector(const Math::Vector3D& v) {
    return v / v.length();
}

#endif /* !VECTOR3D_HPP_ */
