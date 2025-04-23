/*
** EPITECH PROJECT, 2023
** parse_command
** File description:
** handle command parsing in minishell2
*/

#include <string.h>
#include <stdlib.h>
#include "proto.h"

bool is_semicolons(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ';') {
            return true;
        }
    }
    return false;
}

void parse_semicolons(char *line, char ***envcpy)
{
    char **commandes = strtok_array(line, ";");

    for (int i = 0; commandes[i] != NULL; i++) {
        char **args = strtok_array(commandes[i], " \t\n\r");
        init_processes(args, envcpy);
        free_array(args);
    }
    free_array(commandes);
}

void parse_command(char *line, char **args)
{
    char *arg = strtok(line, " \t\n\r");
    int i = 0;

    while (arg != NULL) {
        args[i++] = arg;
        arg = strtok(NULL, " \t\n\r");
    } args[i] = NULL;
}
