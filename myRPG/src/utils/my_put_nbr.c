/*
** EPITECH PROJECT, 2022
** my_put_nbr
** File description:
** displays number
*/

#include <unistd.h>
#include "utils.h"

int my_putstr(int fd, char const *str)
{
    write(fd, str, my_strlen(str));
    return 0;
}

void my_putchar(int fd, char c)
{
    write(fd, &c, 1);
}

static int code_nb(int fd, int nb)
{
    int a = 0, w, s, compteur = 0, b;

    while (nb > 0) {
        w = nb % 10;
        nb = nb / 10;
        a = a * 10 + w;
        compteur += 1;
    }

    for (b = 0; b < compteur; b++){
        s = a % 10;
        a = a / 10;
        my_putchar(fd, 48 + s);
    }
    return 0;
}

static int if_nbr(int fd, int nb)
{
    if (nb == 0){
        my_putchar(fd, 48);
        code_nb(fd, nb);
    } else if (nb < 0){
        my_putchar(fd, 45);
        nb = -nb;
        code_nb(fd, nb);
    } else {
        code_nb(fd, nb);
    }
    return 0;
}

int my_put_nbr(int fd, int nb)
{
    if (nb == -2147483647){
        my_putchar(fd, 45);
        my_putchar(fd, 50);
        my_putchar(fd, 49);
        nb = 47483647;
        code_nb(fd, nb);
    } else if (nb == 2147483647) {
        my_putchar(fd, 50);
        my_putchar(fd, 49);
        nb = 47483647;
        code_nb(fd, nb);
    } else {
        if_nbr(fd, nb);
    }
    return 0;
}
