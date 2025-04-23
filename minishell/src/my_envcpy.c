/*
** EPITECH PROJECT, 2023
** my_envcpy
** File description:
** my_arrcpy function
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "proto.h"

int rows_counter(char **arr)
{
    int count = 0;
    for (int i = 0; arr[i] != NULL; i++) {
        count++;
    }
    return (count);
}

char** my_envcpy(char **env)
{
    int nb_lines = rows_counter(env);
    char **envcpy = malloc(sizeof(char *) * (nb_lines + 1));

    if (envcpy == NULL) {
        return (NULL);
    }
    for (int i = 0; env[i] != NULL; i++) {
        envcpy[i] = malloc(sizeof(char) * (my_strlen(env[i]) + 1));
        envcpy[i][my_strlen(env[i])] = '\0';
        envcpy[i] = my_strcpy(envcpy[i], env[i]);
    }
    envcpy[nb_lines] = NULL;
    return (envcpy);
}
