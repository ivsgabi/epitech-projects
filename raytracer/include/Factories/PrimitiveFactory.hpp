/*
** EPITECH PROJECT, 2024
** PrimitivesFactory
** File description:
** Raytracer
*/

#ifndef PRIMITIVES_FACTORY_HPP_
#define PRIMITIVES_FACTORY_HPP_
// #include <vector>
#include <functional>
#include <iostream>
#include <algorithm>
#include <memory>
#include <unordered_map>
#include <filesystem>
#include "Primitives/APrimitive.hpp"
#include "Primitives/Plane.hpp"
#include "Primitives/Sphere.hpp"
#include "Factories/Exceptions.hpp"
#include "DLLoader/DLLoader.hpp"
#define PRIMITIVES_PLUGINS_PATH "./plugins/primitives"
#define ENTRYPOINT "entry_point"
/*!
    Your dynamic library must have a entrypoint named "entry_point"
*/

enum PRIMITIVE_TYPE { SPHERE, PLANE, TRANSLATION, NONE };
/*!
    If you want to add a new primitive, you will need to create a new PRIMITIVE_TYPE
    (e.g. TORUS if you want to implement one)
*/

namespace Factories {
    class PrimitiveFactory {
        public:
            PrimitiveFactory();
            ~PrimitiveFactory() = default;
            std::shared_ptr<Primitive::IPrimitive> createPrimitive(PRIMITIVE_TYPE type, const std::string &line);
            void getPlugins(const std::string &folderPath);

            private:
                std::unordered_map<PRIMITIVE_TYPE,std::function<std::shared_ptr<Primitive::IPrimitive>(const std::string &)>> _factory;
                std::unordered_map<std::string, std::unique_ptr<DLLoader::DLLoader<Primitive::IPrimitive>>> _plugins;
    };
}

/*!
    After creating the new primitive, you will need to add the dynamic library
    (containing the source code of your primitive) to the currentPrimitivesPlugins map
    Add the name of your plugin, and the corresponding type
*/
const std::unordered_map<std::string, PRIMITIVE_TYPE> currentPrimitivesPlugins = {
    {"./plugins/primitives/libsphere.so", SPHERE},
    {"./plugins/primitives/libplane.so", PLANE},
};

#endif /* !PRIMITIVES_FACTORY_HPP_ */
