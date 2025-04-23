/*
** EPITECH PROJECT, 2024
** SceneBuilder
** File description:
** Raytracer
*/

#ifndef SCENE_BUILDER_HPP_
#define SCENE_BUILDER_HPP_
#include <libconfig.h++>
#include <sstream>
#include "Scene/Scene.hpp"
#include "Factories/LightFactory.hpp"
#include "Factories/PrimitiveFactory.hpp"
#include "Factories/CameraFactory.hpp"

class SceneBuilder {
    public:
        SceneBuilder();
        ~SceneBuilder() = default;
        void setCamera(libconfig::Config &cfg);
        void setLights(libconfig::Config &cfg);
        void setPrimitives(libconfig::Config &cfg);
        std::shared_ptr<Scene> getScene() const;
        std::shared_ptr<RayTracer::Camera> getCamera() const;

    private:
        std::shared_ptr<Scene> _scene;
        std::shared_ptr<RayTracer::Camera> _camera;
        Factories::LightFactory _lightFactory;
        Factories::PrimitiveFactory _primitiveFactory;
        Factories::CameraFactory _cameraFactory;
};

const std::unordered_map<std::string, PRIMITIVE_TYPE> currentPrimitiveTypes =
{
    {"spheres", SPHERE}, {"planes", PLANE}
};

#endif /* !SCENE_BUILDER_HPP_ */
