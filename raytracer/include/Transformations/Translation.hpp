/*
** EPITECH PROJECT, 2024
** Translation (header)
** File description:
** RayTracer
*/

#ifndef TRANSFORMATION_HPP_
#define TRANSFORMATION_HPP_

#include <iostream>
#include "../Math/Point3D.hpp"

namespace Transformations {
    class Translation {
        private:
            Math::Vector3D _offsetVector;
            Math::Point3D _offsetPoint;
        public:
            Translation() = default;
            Translation(const Math::Point3D &point);
            Translation(const Math::Vector3D &vector);
            ~Translation() = default;

            Math::Point3D applyTranslation(const Math::Point3D &point);
            Math::Vector3D applyTranslation(const Math::Vector3D &vector);
    };
};

#endif /* !RECTANGLE3D_HPP_ */