/*
** EPITECH PROJECT, 2023
** utils functions
** File description:
** for my_paint
*/

#include <stdlib.h>
#include <unistd.h>
#include "../include/paint.h"

void my_putchar(char c)
{
    write(1, &c, 1);
}

int my_putstr(char *str)
{
    while (*str) {
        my_putchar(*str);
        str++;
    }
    return (0);
}

int my_put_nbr(int nb)
{
    if (nb < 0) {
        my_putchar('-');
        nb = nb * (-1);
    } if (nb > 9) {
        my_put_nbr(nb / 10);
        my_putchar(nb % 10 + 48);
    } else {
        my_putchar(nb + 48);
    }
    return (0);
}

int my_strlen(char const *str)
{
    int i = 0;
    while (str[i] != '\0') {
        i = i + 1;
    }
    return (i);
}
