/*
** EPITECH PROJECT, 2024
** DLLoader
** File description:
** RType
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
            if (_handle == nullptr) {
                const char* error = dlerror();
                if (error != nullptr) {
                    throw Exceptions::DLLoader::LibraryDoesntExist(libName + ": " + error);
                }
                throw Exceptions::DLLoader::LibraryDoesntExist(libName);
            }
        }

        void unload()
        {
            if (_handle && dlclose(_handle) != 0) {
                throw Exceptions::DLLoader::ErrorUnloadingLibrary("Error when unloading library.");
            }
        }

        T *getInstance(const std::string &entrypointName) const
        {
            if (!_handle) {
                throw Exceptions::DLLoader::ErrorGetInstanceLibrary("Library not loaded.");
            }

            void* pointerEntrypoint = dlsym(_handle, entrypointName.c_str());
            if (!pointerEntrypoint) {
                const char* error = dlerror();
                throw Exceptions::DLLoader::ErrorGetInstanceLibrary(entrypointName + ": " + (error ? error : "Unknown error"));
            }

            using EntrypointFunc = T* ();
            EntrypointFunc* entrypoint = reinterpret_cast<EntrypointFunc*>(pointerEntrypoint);
            return entrypoint();
        }

    private:
        void *_handle;
};

#endif /* !DLLOADER_HPP_ */
