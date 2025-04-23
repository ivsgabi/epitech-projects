/*
** EPITECH PROJECT, 2024
** ParseArgs
** File description:
** RayTracer
*/

#include <fstream>
#include <stdexcept>
#include <cstring>
#include "Parsing/Parsing.hpp"

Parsing::ParseArgs::ParseArgs() {}

Parsing::ParseArgs::~ParseArgs() {}

int Parsing::ParseArgs::dislayHelp()
{
    std::cout << "USAGE: ./raytracer <SCENE_FILE>" << std::endl;
    std::cout << "\tSCENE_FILE: scene configuration" << std::endl;
    return (ERROR);
}

int Parsing::ParseArgs::isValidFile(const char *filename)
{
    std::string line;
    std::ifstream file;

    file.open(filename);
    if (!file.is_open()) {
        throw Parsing::ParsingException("file not found");
    }
    if (!std::getline(file, line)) {
        throw Parsing::ParsingException("empty file");
    }
    file.close();
    return SUCCESS;
}

int Parsing::ParseArgs::checkArgs(int argc, const char *argv[])
{
    if (argc != 2 || std::strcmp(argv[1], "-h") == 0 || std::strcmp(argv[1], "--help") == 0)
        throw Parsing::ParsingException();
    try {
        Parsing::ParseArgs::isValidFile(argv[1]);
    } catch (const Parsing::ParsingException& error) {
        throw Parsing::ParsingException("file not found or empty");
        std::cout << "Parsing::ParsingException:  " << error.what() << std::endl; // change to std::cerr later
        return (ERROR);
    }
    return SUCCESS;
}
