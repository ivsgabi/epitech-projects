/*
** EPITECH PROJECT, 2023
** utilsss.c
** File description:
** III
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "proto.h"

char *my_strcpy(char *dest, const char *src)
{
    char *dest_start = dest;
    while (*src != '\0') {
        *dest++ = *src++;
    }
    *dest = '\0';
    return (dest_start);
}

char *my_strdup(const char *s)
{
    size_t len = 0;
    const char *p = s;
    char *new_s;

    while (*p++) {
        len++;
    }
    new_s = (char *) malloc(len + 1);
    for (size_t i = 0; i <= len; i++) {
        new_s[i] = s[i];
    }
    return new_s;
}

int my_strncmp(const char *s1, const char *s2, size_t n)
{
    for (size_t i = 0; i < n; i++) {
        if (s1[i] != s2[i]) {
            return (s1[i] < s2[i]) ? -1 : 1;
        }
        if (s1[i] == '\0') {
            return 0;
        }
    }
    return 0;
}

char *my_strcat(char *dest, char const *src)
{
    int i = 0;
    int ii = 0;

    ii = my_strlen(dest);
    while (src[i] != '\0') {
        dest[ii + i] = src[i];
        i++;
    } dest[ii + i] = '\0';
    return (dest);
}
