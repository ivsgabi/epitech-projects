/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** my_strcpy.c
*/

#include <stdlib.h>
#include "utils.h"

char *my_strcpy(char *dest, char const *src)
{
    int i = 0;

    for (; src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return dest;
}

char *my_strcat(char *dest, char const *src)
{
    int index = 0;
    char *result = malloc(sizeof(char) *
    (my_strlen(dest) + my_strlen(src) + 1));
    for (int i = 0; dest[i] != '\0'; i++, index++)
        result[index] = dest[i];
    for (int i = 0; src[i] != '\0'; i++, index++) {
        result[index] = src[i];
    }
    result[index] = '\0';
    return result;
}
