/*
** EPITECH PROJECT, 2024
** PrimitivesFactory
** File description:
** Raytracer
*/

#include "Factories/PrimitiveFactory.hpp"

Factories::PrimitiveFactory::PrimitiveFactory()
{
    this->getPlugins(PRIMITIVES_PLUGINS_PATH);

    for (auto &plugin : this->_plugins) {
        std::string name = plugin.first;
        auto &loader = plugin.second;
        if (loader->load(name) == false) {
            throw PluginNonExistent(name);
        }
        PRIMITIVE_TYPE type = currentPrimitivesPlugins.at(name);
        this->_factory.emplace(type, [&](const std::string &line)
        { return std::shared_ptr<Primitive::IPrimitive>(loader->getInstance(ENTRYPOINT, line), 
        [](Primitive::IPrimitive *p){ delete p; }); });
    }
}

std::shared_ptr<Primitive::IPrimitive> Factories::PrimitiveFactory::createPrimitive(PRIMITIVE_TYPE type, const std::string &line)
{
    return this->_factory[type](line);
}

void Factories::PrimitiveFactory::getPlugins(const std::string &folderPath)
{
    std::filesystem::path path = folderPath;

    if (!std::filesystem::exists(path) || !std::filesystem::is_directory(path)) { 
        throw PluginsFolderNonExistent(path);
    }
    for (const auto& file : std::filesystem::directory_iterator(folderPath)) { 
        std::string filepath = file.path();
        for (const auto &[name, type] : currentPrimitivesPlugins) {
            if (name == filepath) {
                this->_plugins.emplace(filepath, std::make_unique<DLLoader::DLLoader<Primitive::IPrimitive>>());
            }
        }
    }
}