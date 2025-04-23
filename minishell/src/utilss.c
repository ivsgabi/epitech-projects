/*
** EPITECH PROJECT, 2023
** mysh_utilss
** File description:
** utils functions for minishell1, second file
*/

#include <stdarg.h>
#include <unistd.h>
#include "proto.h"

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
        } i++;
    } va_end(ap);
    return (count);
}

int my_strcmp(char *str1, char *str2)
{
    int i = 0;

    while (str1[i] != '\0') {
        if (str1[i] != str2[i])
            return (1);
        i++;
    }
    return (str1[i] - str2[i]);
}

char *my_strncat(char *dest, const char *src, size_t n)
{
    size_t dest_len = my_strlen(dest);
    size_t i;

    for (i = 0 ; i < n && src[i] != '\0' ; i++)
        dest[dest_len + i] = src[i];
    dest[dest_len + i] = '\0';

    return dest;
}
