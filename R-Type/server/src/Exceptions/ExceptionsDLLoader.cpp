/*
** EPITECH PROJECT, 2024
** Exceptions/DLLoader.cpp
** File description:
** R-Type
*/

#include "Exceptions.hpp"

Exceptions::DLLoader::LibraryDoesntExist::LibraryDoesntExist(const std::string &libraryName) noexcept : _libraryName(libraryName)
{
}

const char *Exceptions::DLLoader::LibraryDoesntExist::what() const noexcept
{
    const std::string errorMsg = "Library " + this->_libraryName + " to load doesn't exist.";

    return errorMsg.c_str();
}

const char *Exceptions::DLLoader::ErrorUnloadingLibrary::what() const noexcept
{
    const std::string errorMsg = "Error when unloading library.";

    return errorMsg.c_str();
}


const char *Exceptions::DLLoader::ErrorGetInstanceLibrary::what() const noexcept
{
    const std::string errorMsg = "Error when getting instance of library.";

    return errorMsg.c_str();
}
