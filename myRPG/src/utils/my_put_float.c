/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** my_put_float.c
*/

#include "utils.h"
#include <stdlib.h>

float if_f_printf(int fd, float_t *put_float)
{
    if ((put_float->t % 10) >= 5 && put_float->n != 0)
        put_float->temp += 1;
    if ((put_float->t % 10) >= 5 && put_float->n == 0)
        put_float->entier += 1;
    my_put_nbr(fd, put_float->entier);
    return put_float->temp;
}

float if_e_f_printf(int fd, float_t *put_float)
{
    if ((put_float->t % 10) > 5 && put_float->n != 0)
        put_float->temp += 1;
    if ((put_float->t % 10) >= 5 && put_float->n == 0)
        put_float->entier += 1;
    my_put_nbr(fd, put_float->entier);
    return put_float->temp;
}

float f_printf_bis(int n, float temp)
{
    if (n == -1){
        while (temp < 100000.0)
            temp = temp * 10;
    } else {
        for (int i = 0; i < n; i++)
            temp = temp * 10;
    }
    return temp;
}

float_t *init_put_float(int t, float temp, int n, int entier)
{
    float_t *put_float = malloc(sizeof(float_t));
    put_float->t = t;
    put_float->entier = entier;
    put_float->n = n;
    put_float->temp = temp;
    return put_float;
}

void my_put_float(int fd, float nb, int n, char f)
{
    int entier = nb, t, is_neg = 0;
    if (entier < 0){
        entier = -entier;
        nb = -nb;
        is_neg = 1;
    }
    float temp = nb - entier;
    if (temp != 0)
        temp = f_printf_bis(n, temp);
    if (n != -1)
        t = temp * 10;
    if (is_neg == 1)
        my_putchar(fd, '-');
    float_t *put_float = init_put_float(t, temp, n, entier);
    if (f == 'e')
        temp = if_e_f_printf(fd, put_float);
    else
        temp = if_f_printf(fd, put_float);
    display_f(fd, n, temp);
}
