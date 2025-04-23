/*
** EPITECH PROJECT, 2024
** Core.cpp
** File description:
** Raytracer
*/

#include "Core/Core.hpp"

Core::Core()
{
    this->_sceneBuilder = std::unique_ptr<SceneBuilder>(new SceneBuilder());
    this->_screenOrigin = Math::Point3D(-2.0, -1.0, -1.0);
    this->_horizontal = Math::Vector3D(4.0, 0.0, 0.0);
    this->_vertical = Math::Vector3D(0.0, 2.0, 0.0);
    this->_screen = RayTracer::Rectangle3D(this->_screenOrigin, this->_horizontal, this->_vertical);
}

void Core::buildScene(const std::string &filename)
{
    libconfig::Config cfg;

    try {
      cfg.readFile(filename);
    } catch(const libconfig::FileIOException &fioex) {
        throw CoreException("I/O error while reading file");
    }
    try {
        this->_sceneBuilder->setCamera(cfg);
        this->_sceneBuilder->setPrimitives(cfg);
        this->_sceneBuilder->setLights(cfg);
        //this->_sceneBuilder->setTransformations(cfg);
    } catch (const libconfig::SettingNotFoundException& nfex) {
        std::string error = "Missing a mandatory file section: " + std::string(nfex.getPath());
        throw CoreException(error);
    }
}

void Core::renderScene()
{
    this->_sceneBuilder->getCamera()->render(this->_sceneBuilder->getScene());
}

CoreException::CoreException(const std::string &msg) : _message(msg) {}

const char *CoreException::what() const noexcept
{
    return _message.c_str();
}
