/*
** EPITECH PROJECT, 2024
** CameraFactory
** File description:
** Raytracer
*/

#include "Factories/CameraFactory.hpp"

std::shared_ptr<RayTracer::Camera> Factories::CameraFactory::createCamera(const std::string &line)
{
    return std::make_shared<RayTracer::Camera>(line);
}
