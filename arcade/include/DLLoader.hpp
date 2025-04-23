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
#include "Exceptions/Exceptions.hpp"

/*!
    Template class that can load a Dynamic Library
*/
template <typename T>
class DLLoader
{
    public:
        DLLoader() : _handle(nullptr) {}

        ~DLLoader() = default;

        void load(std::string libName)
        {
            std::cout << "lib {" << libName.c_str() << "}";
            _handle = dlopen(libName.c_str(), RTLD_NOW | RTLD_LAZY);
            if (_handle == NULL) {
                char *error = dlerror();
                if (error != NULL) {
                    fprintf(stderr, "%s\n", error);
                    exit(EXIT_FAILURE);
                }
                throw Exceptions::Core::DLLoader::LibDoesntExist();
            }
        }

        void unload()
        {
            if (dlclose(_handle) != 0) {
                throw std::exception();
            }
        }

        T *getInstance(const std::string &entrypointName) const
        {
            T *(*entrypoint)();
            void *pointerEntrypoint = dlsym(_handle, entrypointName.c_str());
    
            if (!pointerEntrypoint) {
                throw std::exception();
            }
            entrypoint = reinterpret_cast<decltype(entrypoint)>(pointerEntrypoint);
            return entrypoint();
        }

    private:
        void *_handle;
};

#endif /* !DLLOADER_HPP_ */
