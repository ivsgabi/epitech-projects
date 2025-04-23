/*
** EPITECH PROJECT, 2024
** HitRecord.hpp
** File description:
** HitRecord
*/

#ifndef HITRECORD_HPP_
#define HITRECORD_HPP_

    #include "../Math/Point3D.hpp"
    #include "Ray.hpp"

namespace RayTracer {
    class HitRecord {
        private:
            Math::Point3D _point;
            Math::Vector3D _normal;
            double _t;
            bool _frontFace;
        public:
            HitRecord();
            ~HitRecord() = default;

            Math::Point3D getPoint() const;
            Math::Vector3D getNormal() const;
            double getT() const;
            bool isFrontFace() const;

            void setPoint(Math::Point3D point);
            void setNormal(Math::Vector3D normal);
            void setT(double t);
            void setBoolFrontFace(bool frontFace);

            void setFaceNormal(const Ray& ray, const Math::Vector3D& outward_normal);
    };
}

#endif /* !HITRECORD_HPP_ */
