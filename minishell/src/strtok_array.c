/*
** EPITECH PROJECT, 2023
** strtok_array
** File description:
** str_to_word_array w/ strtok
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include "proto.h"

char **strtok_array(char *buffer, char *delim)
{
    char *dup = my_strdup(buffer);
    char **array = malloc(sizeof(char *) * (my_strlen(dup) + 1));
    int i = 0;
    char *token = strtok(buffer, delim);

    while (token != NULL) {
        char *dup_token = my_strdup(token);
        array[i] = dup_token;
        i++;
        token = strtok(NULL, delim);
    }
    array[i] = NULL;
    return array;
}
