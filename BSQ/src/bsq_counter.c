/*
** EPITECH PROJECT, 2022
** BSQ_counter
** File description:
** rows and cols counter for BSQ project
*/

#include <stddef.h>
#include "../include/my.h"

int cols_counter(char *str)
{
    int i = 0;
    while (str[i] != '\n') {
        i++;
    } i++;
    int count = 0;
    while (str[i] != '\n') {
        i++;
        count++;
    }
    return (count);
}

int rows_counter(char *str)
{
    int i = 0;
    int res = 0;
    while (str[i] != '\0') {
        i++;
        if (str[i] == '\n' || str[i] == '\0') {
            res++;
        }
    }
    return (res - 2);
}
