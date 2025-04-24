/*
** EPITECH PROJECT, 2025
** ArgumentParser.hpp
** File description:
** ArgumentParser
*/

#ifndef ARGUMENTPARSER_HPP_
#define ARGUMENTPARSER_HPP_

#include <string>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <cstdlib>

class ArgumentParser {
    public:
        ArgumentParser(int argc, char* argv[]);
        bool shouldShowHelp() const;
        std::string getIpAddress() const;
        int getPort() const;

    private:
        void parseArguments();
        bool isValidIpAddress(const std::string& ip) const;
        void validatePort(const std::string& portStr);

        int _argc;
        char** _argv;
        std::string _ipAddress;
        int _port;
        bool _showHelp;
};
#endif /* !ARGUMENTPARSER_HPP_ */
