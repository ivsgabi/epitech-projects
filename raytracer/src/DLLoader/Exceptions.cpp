/*
** EPITECH PROJECT, 2024
** DLLoader
** File description:
** Raytracer
*/

#include "DLLoader/DLLoader.hpp"

const char *DLLoader::ErrorUnloadingLib::what() const noexcept
{
    return "Error while unloading lib";
}

const char *DLLoader::ErrorGettingInstance::what() const noexcept
{
    return "Error while getting instance of lib";
}
