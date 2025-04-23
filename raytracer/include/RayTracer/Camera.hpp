/*
** EPITECH PROJECT, 2024
** Camera.hpp
** File description:
** Camera
*/

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include <memory>
#include <libconfig.h++>
#include "Scene/Scene.hpp"
#include "Rectangle3D.hpp"
#include "RayTracer/Image.hpp"
#include "Ray.hpp"
#include "../Primitives/IPrimitive.hpp"
#include "Lights/ILight.hpp"

struct CameraConfig {
    std::pair<double, double> _resolution;
    Math::Point3D _position;
    Math::Point3D _rotation;
    float _fieldOfWiew;
};

namespace RayTracer {
    class Camera {
        private:
            Math::Point3D _camPosition;

            double _aspectRatio;
            double _lensRadius;
            double _focalLength;

            double _imageWidth;
            double _imageHeight;
            Image _image;

            double _viewportHeight;
            double _viewportWidth;
            Vector3D _pixelDeltaH;
            Vector3D _pixelDeltaV;
            Point3D _pixel00Loc;
            Rectangle3D _viewport;
        public:
            Camera(const std::string &line);
            ~Camera() = default;
            
            Math::Point3D getPosition() const;
            Rectangle3D getViewport() const;
            Image getImage() const;
            double getLensRadius() const;

            void render(std::shared_ptr<Scene> scene);
            double computeTotalLighting(const Math::Point3D &hitPoint, const Math::Vector3D &primitiveNormal);
            
            Ray getRay(double u, double v) const;
            VisualComp::Color traceRay(const Ray& ray, std::shared_ptr<Scene> scene);
    };
} // namespace RayTracer

#endif /* !CAMERA_HPP_ */
