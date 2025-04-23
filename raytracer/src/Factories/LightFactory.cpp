/*
** EPITECH PROJECT, 2024
** LightFactory
** File description:
** Raytracer
*/

#include "Factories/LightFactory.hpp"

Factories::LightFactory::LightFactory()
{
    this->getPlugins(LIGHTS_PLUGINS_PATH);

    for (auto &plugin : this->_plugins) {
        auto &name = plugin.first;
        auto &loader = plugin.second;
        if (loader->load(name) == false) {
            throw PluginNonExistent(name); 
        }
        LIGHT_TYPE type = currentLightsPlugins.at(name);
        this->_factory.emplace(type, [&](const std::string &line)
        { return std::shared_ptr<Lights::ILight>(loader->getInstance(ENTRYPOINT, line), 
        [](Lights::ILight *p){ delete p; }); });
    }
}

std::shared_ptr<Lights::ILight> Factories::LightFactory::createLight(LIGHT_TYPE type, const std::string &line)
{
    return this->_factory[type](line);
}

void Factories::LightFactory::getPlugins(const std::string &folderPath)
{
    std::filesystem::path path = folderPath;

    if (!std::filesystem::exists(path) || !std::filesystem::is_directory(path)) { 
        throw PluginsFolderNonExistent(path);
    }
    for (const auto& file : std::filesystem::directory_iterator(folderPath)) { 
        std::string filepath = file.path();
        for (const auto &[name, type] : currentLightsPlugins) {
            if (name == filepath) {
                this->_plugins.emplace(filepath, std::make_unique<DLLoader::DLLoader<Lights::ILight>>());
            }
        }
    }
}