/*
** EPITECH PROJECT, 2024
** main.c
** File description:
** raytracer
*/

#include "RayTracer/Raytracer.hpp"
#include "Core/Core.hpp"

int main(int argc, const char *argv[])
{
    Parsing::ParseArgs argsParser;

    try {
        argsParser.checkArgs(argc, argv);
    } catch (const Parsing::ParsingException& error) {
        return (argsParser.dislayHelp());
    }
    Core core;
    core.buildScene(argv[1]);
    core.renderScene();
    return (0);
}
