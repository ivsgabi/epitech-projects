/*
** EPITECH PROJECT, 2024
** DLLoader
** File description:
** Raytracer
*/

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_
#include <dlfcn.h>
#include <string>
#include <exception>
#include "DLLoader/IDLLoader.hpp"

/*!
    Template class that can load a Dynamic Library
    Inherits from IDDLoader interface
*/
namespace DLLoader {
    class ErrorUnloadingLib : public std::exception {
        public:
            const char *what() const noexcept;
    };

    class ErrorGettingInstance : public std::exception {
        public:
            const char *what() const noexcept;
    };

    template <typename T>
    class DLLoader : public IDLLoader<T> {
        public:
            DLLoader() : _handle(nullptr) {}

            ~DLLoader() = default;

            bool load(const std::string &libName)
            {
                _handle = dlopen(libName.c_str(), RTLD_NOW | RTLD_LAZY);
                if (_handle == NULL) {
                    return false;
                }
                return true;
            }

            void unload()
            {
                if (dlclose(_handle) != 0) {
                    throw ErrorUnloadingLib();
                }
            }

            T *getInstance(const std::string &entrypointName, const std::string &input) const
            {
                T *(*entrypoint)(const char *input);
                void *pointerEntrypoint = dlsym(_handle, entrypointName.c_str());
        
                if (!pointerEntrypoint) {
                    throw ErrorGettingInstance();
                }
                entrypoint = reinterpret_cast<decltype(entrypoint)>(pointerEntrypoint);
                return entrypoint(input.c_str());
            }

        private:
            void *_handle;
    };
};

#endif /* !DLLOADER_HPP_ */
