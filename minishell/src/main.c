/*
** EPITECH PROJECT, 2023
** main
** File description:
** main file
*/

#include "proto.h"

int main(int argc, UNUSED char **argv, char **env)
{
    if (argc > 1) {
        mini_printf("error : too much arguments\n");
        return (84);
    } else if (argc == 1) {
        get_command(env);
    }
    return (0);
}
