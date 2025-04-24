/*
** EPITECH PROJECT, 2025
** ArgumentParser.cpp
** File description:
** Implementation of ArgumentParser class
*/

#include "ArgumentParser.hpp"
#include "../../../networking/include/Logger.hpp"

ArgumentParser::ArgumentParser(int argc, char* argv[])
    : _argc(argc), _argv(argv), _ipAddress("127.0.0.1"), _port(4242), _showHelp(false)
{
    parseArguments();
}

void ArgumentParser::parseArguments()
{
    if (_argc == 2 && std::string(_argv[1]) == "-h") {
        _showHelp = true;
        return;
    }

    if (_argc == 3) {
        _ipAddress = _argv[1];
        if (!isValidIpAddress(_ipAddress)) {
            Logger::getInstance()->error("Invalid IP address format: {}", _ipAddress);
            throw std::invalid_argument("Error: Invalid IP address format.");
        }

        try {
            validatePort(_argv[2]);
        } catch (const std::exception& e) {
            Logger::getInstance()->error("Invalid port number: {}", _argv[2]);
            throw;
        }
    } else if (_argc != 1) {
        throw std::invalid_argument("Error: Invalid number of arguments. Run './client -h' for usage instructions.");
    }
}

bool ArgumentParser::shouldShowHelp() const
{
    return _showHelp;
}

std::string ArgumentParser::getIpAddress() const
{
    return _ipAddress;
}

int ArgumentParser::getPort() const
{
    return _port;
}

bool ArgumentParser::isValidIpAddress(const std::string& ip) const
{
    const std::regex ipPattern(
        R"(^((25[0-5]|2[0-4][0-9]|[0-1]?[0-9][0-9]?)\.){3}(25[0-5]|2[0-4][0-9]|[0-1]?[0-9][0-9]?)$)");
    return std::regex_match(ip, ipPattern);
}

void ArgumentParser::validatePort(const std::string& portStr)
{
    int port = std::stoi(portStr);
    if (port <= 0 || port > 65535) {
        throw std::out_of_range("Error: Port number must be between 1 and 65535.");
    }
    _port = port;
}
