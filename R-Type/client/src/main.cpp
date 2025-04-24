/*
** EPITECH PROJECT, 2025
** main.cpp
** File description:
** main
*/

#include "GameClient.hpp"
#include "ArgumentParser.hpp"
#include "Logger.hpp"

void printHelp()
{
    std::cout << "Usage: ./client [IP_ADDRESS] [PORT]\n"
              << "Options:\n"
              << "  -h          Show this help message and exit.\n\n"
              << "Arguments:\n"
              << "  IP_ADDRESS  The IP address of the server to connect to (default: 127.0.0.1).\n"
              << "  PORT        The port of the server to connect to (default: 4242).\n"
              << std::endl;
}

int main(int argc, char* argv[]) 
{
    try {
        ArgumentParser parser(argc, argv);

        if (parser.shouldShowHelp()) {
            printHelp();
            return 0;
        }

        std::string ipAddress = parser.getIpAddress();
        int port = parser.getPort();

        Logger::getInstance()->info("Starting client with IP: {}, Port: {}", ipAddress, port);

        GameClient gameClient(ipAddress, port);
        gameClient.connectServer();
        gameClient.loadObjects();
        int result = gameClient.runGameLoop();
        return result;

    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (const std::out_of_range& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        Logger::getInstance()->error("Unexpected exception: {}", e.what());
        std::cerr << "Error: An unexpected error occurred." << std::endl;
        return 1;
    }
}