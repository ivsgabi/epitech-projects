/*
** EPITECH PROJECT, 2022
** my_put_nbr
** File description:
** day07
*/

#include <unistd.h>

void my_putchar(char c);

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
