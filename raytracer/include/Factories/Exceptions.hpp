/*
** EPITECH PROJECT, 2024
** Exceptions
** File description:
** Raytracer
*/

#ifndef EXCEPTIONS_FACTORIES_HPP_
#define EXCEPTIONS_FACTORIES_HPP_
#include <exception>
#include <string>

class PluginsFolderNonExistent : public std::exception {
    public:
        PluginsFolderNonExistent(const std::string &folderName);
        const char *what() const noexcept;
    private:
        const std::string _folderName;
};

class PluginNonExistent : public std::exception {
    public:
        PluginNonExistent(const std::string &pluginName);
        const char *what() const noexcept;
    private:
        const std::string _pluginName;
};

#endif /* !EXCEPTIONS_FACTORIES_HPP_ */
