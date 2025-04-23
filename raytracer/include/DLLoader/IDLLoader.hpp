/*
** EPITECH PROJECT, 2024
** IDLLoader
** File description:
** Raytracer
*/

#ifndef IDLLOADER_HPP_
#define IDLLOADER_HPP_
#include <cstdbool>

template <typename T>
class IDLLoader
{
    public:
        virtual ~IDLLoader() = default;
        virtual bool load(const std::string &libName) = 0;
        virtual void unload() = 0;
        virtual T *getInstance(const std::string &entrypointName, const std::string &input) const = 0;
};

#endif /* !IDLLOADER_HPP_ */
