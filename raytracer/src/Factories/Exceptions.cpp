/*
** EPITECH PROJECT, 2024
** Exceptions Factories
** File description:
** Raytracer
*/

#include "Factories/Exceptions.hpp"

PluginsFolderNonExistent::PluginsFolderNonExistent(const std::string &folderName) : _folderName(folderName)
{}

const char *PluginsFolderNonExistent::what() const noexcept
{
    const std::string errorMsg = "Folder " + this->_folderName + " doesn't exist.\n";

    return errorMsg.c_str();
}

PluginNonExistent::PluginNonExistent(const std::string &pluginName) : _pluginName(pluginName)
{}

const char *PluginNonExistent::what() const noexcept
{
    const std::string errorMsg = "Plugin " + this->_pluginName + " doesn't exist.\n";

    return errorMsg.c_str(); 
}