/*
** EPITECH PROJECT, 2024
** LightFactory
** File description:
** Raytracer
*/

#ifndef LIGHT_FACTORY_HPP_
#define LIGHT_FACTORY_HPP_
// #include <vector>
#include <functional>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <filesystem>
#include "Lights/ILight.hpp"
#include "Lights/AmbientLight.hpp"
#include "Lights/LightDirection.hpp"
#include "Lights/LightPoint.hpp"
#include "Factories/Exceptions.hpp"
#include "DLLoader/DLLoader.hpp"
#define LIGHTS_PLUGINS_PATH "./plugins/lights"
#define ENTRYPOINT "entry_point"


enum LIGHT_TYPE { AMBIENT, POINT, DIRECTION };

namespace Factories {
    class LightFactory {
        public:
            LightFactory();
            ~LightFactory() = default;
            std::shared_ptr<Lights::ILight> createLight(LIGHT_TYPE type, const std::string &line);
            void getPlugins(const std::string &folderPath);

        private:
            std::unordered_map<LIGHT_TYPE,std::function<std::shared_ptr<Lights::ILight>(const std::string &)>> _factory;
            std::unordered_map<std::string, std::unique_ptr<DLLoader::DLLoader<Lights::ILight>>> _plugins;
    };
}

const std::unordered_map<std::string, LIGHT_TYPE> currentLightsPlugins = {
    {"./plugins/lights/libambient.so", AMBIENT},
    {"./plugins/lights/libdirectionnal.so", DIRECTION},
    {"./plugins/lights/libpoint.so", POINT},
};

#endif /* !LIGHT_FACTORY_HPP_ */
