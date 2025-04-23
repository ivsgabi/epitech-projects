/*
** EPITECH PROJECT, 2024
** ListModules.hpp
** File description:
** Arcade
*/

#ifndef LIST_MODULES_HPP_
#define LIST_MODULES_HPP_
#include <unordered_map>
#include <string>
#include <filesystem>
#include <fstream>
#define LIB_PATH "./lib"

enum ModuleType { GAME, GRAPHIC };

const std::unordered_map<std::string, ModuleType> availableModules = {
    {"./lib/arcade_ncurses.so", GRAPHIC},
    {"./lib/arcade_sdl2.so", GRAPHIC},
    {"./lib/arcade_sfml.so", GRAPHIC},
    {"./lib/arcade_menu.so", GAME},
    {"./lib/arcade_nibbler.so", GAME},
    {"./lib/arcade_snake.so", GAME}
};

#endif /* !LIST_MODULES_HPP_ */
