/*
** EPITECH PROJECT, 2024
** CameraFactory
** File description:
** Raytracer
*/

#ifndef CAMERA_FACTORY_HPP_
#define CAMERA_FACTORY_HPP_
#include <memory>
#include "RayTracer/Camera.hpp"
#include "Factories/Exceptions.hpp"
#define ENTRYPOINT "entry_point"

namespace Factories {
    class CameraFactory {
        public:
            CameraFactory() = default;
            ~CameraFactory() = default;
            std::shared_ptr<RayTracer::Camera> createCamera(const std::string &line);
    };
}

#endif /* !CAMERA_FACTORY_HPP_ */
