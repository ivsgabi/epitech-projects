/*
** EPITECH PROJECT, 2024
** main.cpp
** File description:
** Sample server
*/

// #include "server/ServerNetwork.hpp"
#include "ECS/Registry/Registry.hpp" 
#include "Logger.hpp"
#include "GameServer.hpp"
#include "Exceptions.hpp"
#include <string>
#include <stdexcept>

void printHelp()
{
    std::cout << "Usage: ./r-type_server [CONFIG_FILE] [PORT]\n"
              << "Options:\n"
              << "  -h          Show this help message and exit.\n\n"
              << "Arguments:\n"
              << "  CONFIG_FILE  The configuration file used to load a game.\n"
              << "  PORT        The port of the server (default: 4242).\n"
              << std::endl;
}

int main(int ac, char **av)
{
    if (ac < 2) {
        std::cout << "Rtype server, an EPITECH Project.\n";
        std::cout << "USAGE: ./r-type_server <config_file>\n";
        return SUCCESS;
    }
    Logger::setLevel(spdlog::level::info);

    try {
        if (ac == 3) {
            GameServer gameServer(av[1], std::stoi(av[2]));
            gameServer.runGameLoop();
        } else if (ac == 2) {
            GameServer gameServer(av[1]);
            gameServer.runGameLoop();
        } else {
            throw std::invalid_argument("Invalid arguments.");
        }
    } catch (const std::exception &e) {
        std::string errorMsg = std::string("Error: ") + e.what();
        Logger::getInstance()->error(errorMsg);
        std::cout << std::endl;
        printHelp();
        return ERROR;
    }
    return SUCCESS;
}