/*
** EPITECH PROJECT, 2024
** SceneBuilder.cpp
** File description:
** Raytracer
*/

#include "Scene/SceneBuilder.hpp"

SceneBuilder::SceneBuilder()
{
    this->_scene = std::shared_ptr<Scene>(new Scene(),
        [](Scene *p){ delete p; });
}

void SceneBuilder::setCamera(libconfig::Config &cfg)
{
    CameraConfig config;
    std::ostringstream params;
    int width, height, x, y, z , fieldOfView = 0;


    const libconfig::Setting &camera = cfg.lookup("camera");
    const libconfig::Setting &resolution = camera["resolution"];
    resolution.lookupValue("width", width);
    resolution.lookupValue("height", height);
    config._resolution.first = width;
    config._resolution.second = height;

    const libconfig::Setting& pos = camera["position"];
    pos.lookupValue("x", x);
    pos.lookupValue("y", y);
    pos.lookupValue("z", z);
    config._position.setX(x);
    config._position.setY(y);
    config._position.setZ(z);

    const libconfig::Setting& rotation = camera["rotation"];
    rotation.lookupValue("x", x);
    rotation.lookupValue("y", y);
    rotation.lookupValue("z", z);
    config._rotation.setX(x);
    config._rotation.setY(y);
    config._rotation.setZ(z);

    camera.lookupValue("fieldOfView", fieldOfView);
    config._fieldOfWiew = fieldOfView;

    params << "resolution = { width = " << config._resolution.first
    << "; height = " << config._resolution.second << "; };" << std::endl;
    params << "position = { x = " << config._position.getX() << "; y = "
    << config._position.getY() << "; z = " << config._position.getZ() << "; };" << std::endl;
    params << "rotation = { x = " << config._rotation.getX() << "; y = "
    << config._rotation.getY() << "; z = " << config._rotation.getZ() << "; };" << std::endl;
    params << "fieldOfView = " << config._fieldOfWiew << ";" << std::endl;

    std::string str = params.str();
    this->_camera = this->_cameraFactory.createCamera(str);
}

void SceneBuilder::setLights(libconfig::Config &cfg)
{
    int x, y, z = 0;
    double ambient, diffuse;
    std::string lightsParams, pointLine;
    const libconfig::Setting& root = cfg.getRoot();
    const libconfig::Setting& lights = root["lights"];
    std::unordered_map<std::string, LIGHT_TYPE> sceneLights;

    lights.lookupValue("ambient", ambient);
    lightsParams = std::to_string(ambient);
    sceneLights.emplace(lightsParams, AMBIENT);

    if (lights.exists("diffuse")) {
        lights.lookupValue("diffuse", diffuse);
    }
    if (lights.exists("point")) {
        const libconfig::Setting& points = lights["point"];
        for (int i = 0; i < points.getLength(); i++) {
            const libconfig::Setting& point = points[i];
            point.lookupValue("x", x);
            point.lookupValue("y", y);
            point.lookupValue("z", z);
            pointLine = "{ x = " + std::to_string(x) + "; y = " + std::to_string(y) + "; z = " + std::to_string(z) + "; }";

            if (point.exists("offset")) {
                int offsetX, offsetY, offsetZ;
                const libconfig::Setting& offset = point["offset"];
                offset.lookupValue("x", offsetX);
                offset.lookupValue("y", offsetY);
                offset.lookupValue("z", offsetZ);
                lightsParams = "light: { intensity = " + std::to_string(diffuse) + "; values = " + pointLine + 
                " offset = { x = " + std::to_string(offsetX) + "; y = " + std::to_string(offsetY) + "; z = " + std::to_string(offsetZ) + "; }; }";
            } else {
                lightsParams = "light: { intensity = " + std::to_string(diffuse) + "; values = " + pointLine + " ;}";
            }
            sceneLights.emplace(lightsParams, POINT);
        }
    }
    if (lights.exists("directional")) {
        const libconfig::Setting& directional = lights["directional"];
        for (int i = 0; i < directional.getLength(); i++) {
            const libconfig::Setting& direction = directional[i];
            direction.lookupValue("x", x);
            direction.lookupValue("y", y);
            direction.lookupValue("z", z);
            pointLine = "{ x = " + std::to_string(x) + "; y = " + std::to_string(y) + "; z = " + std::to_string(z) + "; }";

            if (direction.exists("offset")) {
                int offsetX, offsetY, offsetZ;
                const libconfig::Setting& offset = direction["offset"];
                offset.lookupValue("x", offsetX);
                offset.lookupValue("y", offsetY);
                offset.lookupValue("z", offsetZ);
                lightsParams = "light: { intensity = " + std::to_string(diffuse) + "; values = " + pointLine + 
                " offset = { x = " + std::to_string(offsetX) + "; y = " + std::to_string(offsetY) + "; z = " + std::to_string(offsetZ) + "; }; }";
            } else {
                lightsParams = "light: { intensity = " + std::to_string(diffuse) + "; values = " + pointLine + " ;}";
            }
            sceneLights.emplace(lightsParams, DIRECTION);
        }
    }
    for (auto &[key, value] : sceneLights) {
        this->_scene->_lights.push_back(this->_lightFactory.createLight(value, key));
    }
}

void SceneBuilder::setPrimitives(libconfig::Config &cfg)
{
    int x, y, z = 0;
    double r = 0;
    int colorR, colorG, colorB = 0;
    int offsetX, offsetY, offsetZ = 0;
    std::string primParamLine;
    const libconfig::Setting& root = cfg.getRoot();
    const libconfig::Setting& primitives = root["primitives"];
    std::unordered_map<std::string, PRIMITIVE_TYPE> scenePrimitives;
    std::string params;

    if (primitives.exists("spheres")) {
        const libconfig::Setting& spheres = primitives["spheres"];
        for (int i = 0; i < spheres.getLength(); i++) {
            const libconfig::Setting& sphere = spheres[i];
            sphere.lookupValue("x", x);
            sphere.lookupValue("y", y);
            sphere.lookupValue("z", z);
            sphere.lookupValue("r", r);
            const libconfig::Setting& color = sphere["color"];
            color.lookupValue("r", colorR);
            color.lookupValue("g", colorG);
            color.lookupValue("b", colorB);

            if (sphere.exists("offset")) {
                const libconfig::Setting& offset = sphere["offset"];
                offset.lookupValue("x", offsetX);
                offset.lookupValue("y", offsetY);
                offset.lookupValue("z", offsetZ);
                params = "sphere: { x = " + std::to_string(x) + "; y = " + std::to_string(y) + "; z = " + std::to_string(z) +"; r = " + 
                std::to_string(r) + "; color = { r = " + std::to_string(colorR) + "; g = " + std::to_string(colorG) + "; b = " + std::to_string(colorB) +
                 "; } offset = { x = " + std::to_string(offsetX) + "; y = " + std::to_string(offsetY) + "; z = " + std::to_string(offsetZ) + "; }; }";
            } else {
                params = "sphere: { x = " + std::to_string(x) + "; y = " + std::to_string(y) + "; z = " + std::to_string(z) +"; r = " + 
                std::to_string(r) + "; color = { r = " + std::to_string(colorR) + "; g = " + std::to_string(colorG) + "; b = " + std::to_string(colorB) +
                 "; }; }";
            }
            scenePrimitives.emplace(params, SPHERE);
        }
    }
    if (primitives.exists("planes")) {
        const libconfig::Setting& planes = primitives["planes"];
        for (int i = 0; i < planes.getLength(); i++) {
            const libconfig::Setting& plane = planes[i];
            int posX, posY, posZ;
            int normalX, normalY, normalZ;

            const libconfig::Setting& point = plane["point"];
            point.lookupValue("x", posX);
            point.lookupValue("y", posY);
            point.lookupValue("z", posZ);

            const libconfig::Setting& normal = plane["normal"];
            normal.lookupValue("x", normalX);
            normal.lookupValue("y", normalY);
            normal.lookupValue("z", normalZ);

            const libconfig::Setting& color = plane["color"];
            color.lookupValue("r", colorR);
            color.lookupValue("g", colorG);
            color.lookupValue("b", colorB);

            if (plane.exists("offset")) {
                const libconfig::Setting& color = plane["offset"];
                color.lookupValue("x", offsetX);
                color.lookupValue("y", offsetY);
                color.lookupValue("z", offsetZ);
                params = "plane: { point = { x = " + std::to_string(posX) + "; y = " + std::to_string(posY) + "; z = " + 
                std::to_string(posZ) + "; }; normal = { x = " + std::to_string(normalX) + "; y = " + std::to_string(normalY) + "; z = " + 
                std::to_string(normalZ) + "; }; color = { r = " + std::to_string(colorR) + "; g = " + std::to_string(colorG) + "; b = " + 
                std::to_string(colorB) + "; } offset = { x = " + std::to_string(offsetX) + "; y = " + std::to_string(offsetY) + "; z = " + std::to_string(offsetZ) + "; }; }";
            } else {
                params = "plane: { point = { x = " + std::to_string(posX) + "; y = " + std::to_string(posY) + "; z = " + 
                std::to_string(posZ) + "; }; normal = { x = " + std::to_string(normalX) + "; y = " + std::to_string(normalY) + "; z = " + 
                std::to_string(normalZ) + "; }; color = { r = " + std::to_string(colorR) + "; g = " + std::to_string(colorG) + "; b = " + 
                std::to_string(colorB) + "; }; }";
            }
            scenePrimitives.emplace(params, PLANE);
        }
    }
    for (auto &[key, value] : scenePrimitives) {
        if (value == SPHERE || value == PLANE) {
            this->_scene->_primitives.push_back(this->_primitiveFactory.createPrimitive(value, key));
        }
    }
}

std::shared_ptr<Scene> SceneBuilder::getScene() const
{
    return this->_scene;
}

std::shared_ptr<RayTracer::Camera> SceneBuilder::getCamera() const
{
    return this->_camera;
}