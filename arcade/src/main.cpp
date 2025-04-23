/*
** EPITECH PROJECT, 2024
** main.c
** File description:
** Arcade
*/

#include "Arcade.hpp"

int main(int ac, char **av)
{
    try {
        if (ac != 2) {
            throw Exceptions::Core::BadNumberArguments();
        }
        std::string graphicLibName = av[1];
        Core core(graphicLibName);
        core.runArcade();
    } catch (const std::exception &e) {
        std::cout << "Error: " << e.what() << std::endl;
        return ERROR;
    }
    return SUCCESS;
}
