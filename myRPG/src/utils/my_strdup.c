/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** my_strdup.c
*/

#include <stdio.h>
#include "utils.h"
#include <stdlib.h>

char *my_strdup(const char *str)
{
    char *dest = NULL;
    int size = my_strlen(str) + 1;

    dest = malloc(size);
    if (dest != NULL) {
        my_strcpy(dest, str);
    }
    return dest;
}
