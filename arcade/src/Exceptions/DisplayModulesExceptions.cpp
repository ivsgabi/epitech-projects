/*
** EPITECH PROJECT, 2024
** DisplayModuleExceptions.cpp
** File description:
** Arcade
*/

#include "Exceptions/Exceptions.hpp"

const char *Exceptions::DisplayModule::FontNotFound::what() const noexcept
{
    return "Font not found";
}