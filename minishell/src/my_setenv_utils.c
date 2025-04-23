/*
** EPITECH PROJECT, 2023
** my_setenv
** File description:
** my_setenv
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "proto.h"

bool is_variable_exist(char **envcpy, char *name, int len_name)
{
    for (int i = 0; envcpy[i] != NULL; i++) {
        if (my_strncmp(envcpy[i], name, len_name) == 0) {
            return true;
        }
    }
    return false;
}

char *create_filled_elem(char **args)
{
    int total_len = my_strlen(args[1]) + 1;
    if (args[2])
        total_len += my_strlen(args[2]);
    char *new_elem = malloc(sizeof(char) * total_len + 1);
    new_elem[total_len] = '\0';
    new_elem = my_strcpy(new_elem, args[1]);
    new_elem = my_strcat(new_elem, "=");
    if (args[2])
        new_elem = my_strcat(new_elem, args[2]);
    return (new_elem);
}

int size_array(char **envcpy)
{
    int i = 0;
    for (; envcpy[i] != NULL; i++);
    return (i);
}
