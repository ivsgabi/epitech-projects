/*
** EPITECH PROJECT, 2024
** Point3D.hpp
** File description:
** Point3D
*/

#ifndef POINT3D_HPP_
#define POINT3D_HPP_

#include "Vector3D.hpp"

namespace Math {
    class Point3D {
        private:
            double _x, _y, _z;
        public:
            Point3D();
            Point3D(double x, double y, double z);
            ~Point3D() = default;

            double getX() const;
            double getY() const;
            double getZ() const;
            
            void setX(double x) {_x = x;};
            void setY(double y) {_y = y; };
            void setZ(double z) {_z = z; };

            Point3D operator+(const Vector3D& v) const;
            Vector3D operator-(const Point3D& other) const;
            Point3D& operator+=(const Vector3D& v);

            Point3D operator-(const Vector3D& vec) const;

            double distanceTo(const Point3D& other) const;

            Point3D translate(const Point3D& translation) const;
    };
} //namespace Math

#endif /* !POINT3D_HPP_ */
