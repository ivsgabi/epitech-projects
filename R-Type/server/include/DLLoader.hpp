/*
** EPITECH PROJECT, 2024
** DLLoader
** File description:
** Arcade
*/

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_
#include <iostream>
#include <string>
#include <dlfcn.h>
#include "Exceptions.hpp"

template <typename T>
class DLLoader
{
    public:
        DLLoader() : _handle(nullptr) {}

        ~DLLoader() = default;

        void load(std::string libName)
        {
            _handle = dlopen(libName.c_str(), RTLD_NOW | RTLD_LAZY);
            if (_handle == NULL) {
                throw Exceptions::DLLoader::LibraryDoesntExist(libName);
            }
        }

        void unload()
        {
            if (dlclose(_handle) != 0) {
                throw Exceptions::DLLoader::ErrorUnloadingLibrary();
            }
        }

        T *getInstance(const std::string &entrypointName) const
        {
            T *(*entrypoint)();
            void *pointerEntrypoint = dlsym(_handle, entrypointName.c_str());
    
            if (!pointerEntrypoint) {
                throw Exceptions::DLLoader::ErrorGetInstanceLibrary();
            }
            entrypoint = reinterpret_cast<decltype(entrypoint)>(pointerEntrypoint);
            return entrypoint();
        }

    private:
        void *_handle;
};

#endif /* !DLLOADER_HPP_ */
