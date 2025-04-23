/*
** EPITECH PROJECT, 2024
** Camera.cpp
** File description:
** Raytracer
*/

#include <cstdlib>  // For std::rand()
#include <memory>
#include "RayTracer/Camera.hpp"
#include "RayTracer/HitRecord.hpp"

using namespace RayTracer;

extern "C"
{
    Camera *entry_point(const char *input)
    {
        return new Camera(input);
    }
}

Camera::Camera(const std::string &line)
{
    CameraConfig config;
    libconfig::Config cfg;

    try {
        cfg.readString(line);
    } catch(const libconfig::ParseException &pex) {
        std::cerr << "Syntax error in line: " << pex.getError() << " -> " << pex.getLine() << std::endl;
        throw;
    }
    int width, height, x, y, z , fieldOfView = 0;
    try {
        const libconfig::Setting &resolution = cfg.lookup("resolution");
        resolution.lookupValue("width", width);
        resolution.lookupValue("height", height);
        config._resolution.first = width;
        config._resolution.second = height;

        const libconfig::Setting& pos = cfg.lookup("position");
        pos.lookupValue("x", x);
        pos.lookupValue("y", y);
        pos.lookupValue("z", z);
        config._position.setX(x);
        config._position.setY(y);
        config._position.setZ(z);

        const libconfig::Setting& rotation = cfg.lookup("rotation");
        rotation.lookupValue("x", x);
        rotation.lookupValue("y", y);
        rotation.lookupValue("z", z);
        config._rotation.setX(x);
        config._rotation.setY(y);
        config._rotation.setZ(z);

        cfg.lookupValue("fieldOfView", fieldOfView);
        config._fieldOfWiew = fieldOfView;
        auto aspectRatio = 16.0 / 9.0;
        auto aperture = 1;
        this->_camPosition = config._position;
        this->_lensRadius = aperture / 2;

        _focalLength = 1.0;

        _imageWidth = width;
        _imageHeight = double(_imageWidth / aspectRatio);
        _imageHeight = (_imageHeight < 1) ? 1 : _imageHeight;
        _image = Image(_imageWidth, _imageHeight);

        _viewportHeight = 2.0;
        _viewportWidth = aspectRatio * (double(_imageWidth)/_imageHeight);

        Vector3D vecHorizontal(_viewportWidth, 0, 0);
        Vector3D vecVertical(0, -_viewportHeight, 0);

        _pixelDeltaH = vecHorizontal / _imageWidth;
        _pixelDeltaV = vecVertical / _imageHeight;

        auto viewportUpperLeft = _camPosition - Vector3D(0, 0, _focalLength) - vecHorizontal/2 - vecVertical/2;
        _pixel00Loc = viewportUpperLeft + (_pixelDeltaH + _pixelDeltaV) * 0.5;
        _viewport = Rectangle3D(_pixel00Loc, vecHorizontal, vecVertical);
    } catch (const libconfig::SettingNotFoundException &nfex) {
        std::cerr << "required setting not found: " << nfex.getPath() << std::endl;
        throw;
    }
}

void Camera::render(std::shared_ptr<Scene> scene)
{
    for (int j = 0; j < _image.getHeight(); ++j) {
        for (int i = 0; i < _image.getWidth(); ++i) {
            VisualComp::Color pixelColor(0, 0, 0);
            for (int s = 0; s < 100; ++s) {
                auto offset = Vector3D((rand() / (RAND_MAX + 1.0)) - 0.5, (rand() / (RAND_MAX + 1.0)) - 0.5, 0);
                auto pixel_sample = _pixel00Loc + (_pixelDeltaH * (i + offset.getX())) + (_pixelDeltaV * (j + offset.getY()));
                auto ray_origin = _camPosition;
                auto ray_direction = pixel_sample - ray_origin;
                Ray ray(ray_origin, ray_direction);
                pixelColor += traceRay(ray, scene);
            }
            pixelColor /= 100.0;
            _image.setPixel(i, j, pixelColor);
        }
    }
    _image.writeToPPM("output.ppm");
    std::cout << "Rendering Finished. Image saved as 'output.ppm'." << std::endl;
    std::cout << "Launching SFML window." << std::endl;
    _image.displaySFML();
}

VisualComp::Color Camera::traceRay(const Ray& ray, std::shared_ptr<Scene> scene)
{
    HitRecord rec;
    VisualComp::Color color;

    if (scene->hits(ray, 0, std::numeric_limits<double>::infinity(), rec, color)) {
        // outline of primitives in another color, to check if antialiasing works
        double dotProduct = ray.getDirection().normalize().dot(rec.getNormal().normalize());
        if (std::fabs(dotProduct) < 0.1) {
            return VisualComp::Color(0, 0, 0); //white
        }
        return color * scene->computeTotalLighting(rec.getPoint(), rec.getNormal());
    }
    return VisualComp::Color(128, 128, 128); // Grey for the background
}

Ray Camera:: getRay(double u, double v) const
{
    Point3D target = _viewport.getPointAt(u, v);
    Vector3D rayDirection = target - _camPosition;
    return Ray(_camPosition, rayDirection);     
}

Math::Point3D Camera:: getPosition() const
{
    return _camPosition;
}

Rectangle3D Camera:: getViewport() const
{
    return _viewport;
}

Image Camera:: getImage() const
{
    return _image;
}

double Camera:: getLensRadius() const
{
    return _lensRadius;
}
