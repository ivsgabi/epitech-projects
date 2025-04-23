/*
** EPITECH PROJECT, 2023
** array_utils
** File description:
** utils functions to array
*/

#include <stdlib.h>
#include "proto.h"

void free_array(char **array)
{
    for (int i = 0; array[i]; i++) {
        free(array[i]);
    } free(array);
}

void display_env(char **env)
{
    for (int i = 0; env[i] != NULL; i++) {
        mini_printf("%s\n", env[i]);
    }
}
