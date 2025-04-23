/*
** EPITECH PROJECT, 2024
** Core
** File description:
** Raytracer
*/

#ifndef CORE_HPP_
#define CORE_HPP_
#include <memory>
#include <libconfig.h++>
#include <exception>
#include "Scene/Scene.hpp"
#include "Scene/SceneBuilder.hpp"
#include "Parsing/Parsing.hpp"
#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include "RayTracer/Image.hpp"

/*!
    Class that handle the building of the scene
    (according to the scene config file passed as parameter)
    and render the scene
*/
class Core {
    public:
        Core();
        ~Core() = default;
        void buildScene(const std::string &filename);
        void renderScene();

    private:
        std::unique_ptr<SceneBuilder> _sceneBuilder;
        Math::Point3D _screenOrigin;
        Math::Vector3D _horizontal;
        Math::Vector3D _vertical;
        RayTracer::Rectangle3D _screen;
        std::vector<RayTracer::Image> _images;
};

class CoreException : public std::exception {
    private:
        std::string _message;

    public:
        CoreException(const std::string &msg);
        const char *what() const noexcept;
};

#endif /* !CORE_HPP_ */
