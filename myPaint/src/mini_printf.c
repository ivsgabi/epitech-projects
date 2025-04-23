/*
** EPITECH PROJECT, 2023
** mini_printf
** File description:
** utils file
*/

#include <stdarg.h>
#include <unistd.h>
#include "../include/paint.h"

void conditions(va_list ap, int i, const char *format, ...)
{
    if (format[i] == 'd') {
        my_put_nbr(va_arg(ap, int));
    } if (format[i] == 'i') {
        my_put_nbr(va_arg(ap, int));
    } if (format[i] == 's') {
        my_putstr(va_arg(ap, char *));
    } if (format[i] == 'c') {
        my_putchar(va_arg(ap, int));
    }
}

int mini_printf(const char *format, ...)
{
    va_list ap;
    int i = 0;
    int count = 0;
    va_start(ap, format);
    while (format[i] != '\0') {
        if (format[i] == '%') {
            i++;
            conditions(ap, i, format);
            } else {
        my_putchar(format[i]);
        count++;
        }
        i++;
    }
    va_end(ap);
    return (count);
}
