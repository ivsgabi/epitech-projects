/*
** EPITECH PROJECT, 2023
** my_setenv
** File description:
** my_setenv
*/

#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "proto.h"

int setenv_err(char **args)
{
    for (int i = 0; args[1][i]; i++) {
        if ((args[1][i] < 'a' || args[1][i] > 'z')
        && (args[1][i] < 'A' || args[1][i] > 'Z')
        && (args[1][i] < '0' || args[1][i] > '9')) {
            write(2, "setenv: Variable name ", 22);
            write(2, "must contain alphanumeric characters.\n", 38);
            return 84;
        }
    } if ((args[1][0] < 'a' || args[1][0] > 'z')
    && (args[1][0] < 'A' || args[1][0] > 'Z')) {
        write(2, "setenv: Variable name ", 22);
        write(2, "must begin with a letter.\n", 26);
        return 84;
        }
        return (0);
}

char **my_setenv(char **envcpy, char **args)
{
    setenv_err(args);
    int i = 0;
    char** new_env = NULL; int len_arr = size_array(envcpy);
    char *new_elem = create_filled_elem(args);
    bool variable_state = is_variable_exist(envcpy, args[1],
    my_strlen(args[1]));
    if (variable_state == true) {
        new_env = malloc(sizeof(char *) * (len_arr + 1));
        for (i = 0; envcpy[i]; i++) {
            new_env[i] = my_strncmp(envcpy[i], args[1], my_strlen(args[1])) == 0
                ? new_elem : my_strdup(envcpy[i]);
        }} else {
        new_env = malloc(sizeof(char *) * (len_arr + 1 + 1));
        for (i = 0; envcpy[i] != NULL; i++) {
            new_env[i] = my_strdup(envcpy[i]);
        } new_env[i++] = new_elem;
    } new_env[i] = NULL;
    return (new_env);
}
