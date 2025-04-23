/*
** EPITECH PROJECT, 2024
** Exceptions.cpp
** File description:
** Arcade
*/

#include "Exceptions/Exceptions.hpp"

const char *Exceptions::Core::BadNumberArguments::what() const noexcept
{
    return "Bad number of arguments\n"
    "Usage:\t./arcade lib\n"
    "\tlib: the graphics library to use initially.\n"
    "Example: ./arcade ./lib/arcade_ncurses.so";
}

const char *Exceptions::Core::InvalidInitialGraphicLib::what() const noexcept
{
    return "Initial graphic lib doesn't exist or is not compatible";
}

const char *Exceptions::Core::DLLoader::LibDoesntExist::what() const noexcept
{
    return "Lib to load doesn't exist";
}

const char *Exceptions::Core::DLLoader::ErrorUnloadingLib::what() const noexcept
{
    return "Error while unloading lib";
}

const char *Exceptions::Core::LibFolderDoesntExist::what() const noexcept
{
    return "Lib folder doesn't exist";
}