/*
** EPITECH PROJECT, 2024
** GameModulesExecptions.cpp
** File description:
** GameModulesExceptions
*/

#include "Exceptions/Exceptions.hpp"

const char *Exceptions::GameModule::LibFolderDoesntExist::what() const noexcept
{
    return "Lib folder doesn't exist";
}