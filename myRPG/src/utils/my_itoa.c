/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** my_itoa.c
*/

#include "utils.h"
#include <stdlib.h>

static char *my_revstr(char *str)
{
    int len = my_strlen(str) - 1;
    for (int j = 0; j < len; j++){
        char temp = str[len];
        str[len] = str[j];
        str[j] = temp;
        len--;
    }
    return str;
}

char *my_itoa(int nb)
{
    int i = 0;
    int len = 0;
    if (nb == 0) {
        return "0";
    }
    for (int copie = nb; copie > 0; copie /= 10, len++);
    char *str = malloc(sizeof(char) * (len + 1));
    if (nb != 0){
        do {
            str[i++] = nb % 10 + '0';
        } while ((nb /= 10) > 0);
        str[i] = '\0';
    }
    str = my_revstr(str);

    return str;
}
