/*
** EPITECH PROJECT, 2022
** mini_printf
** File description:
** mini printf
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdarg.h>
#include "utils.h"
#include <string.h>

void display_f(int fd, int n, float temp)
{
    if (n == -1 && temp == 0)
        my_putstr(fd, ".000000");
    if (n != 0 && temp != 0){
        my_putchar(fd, '.');
        my_put_nbr(fd, temp);
    }
}

static int case_mini_printf(int fd, const char *format, int i, va_list ap)
{
    if (format[i] > 64 && format[i] < 90){
        my_putchar(fd, format[i - 1]);
        my_putchar(fd, format[i]);
    } switch (format[i]) {
        case 'd': my_put_nbr(fd, va_arg(ap, int));
            break;
        case 's': my_putstr(fd, va_arg(ap, char*));
            break;
        case 'c': my_putchar(fd, va_arg(ap, int));
            break;
        case 'f': my_put_float(fd, va_arg(ap, double), 1, 'f');
            break;
        case '%': my_putchar(fd, '%');
            break;
    }
    return 0;
}

int mini_printf(int fd, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    int comp = 0;
    int n = my_strlen(format);
    int i = 0;
    while (i < n){
        if (format[i] == '%'){
            case_mini_printf(fd, format, i + 1, ap);
            i += 2;
        } else {
            my_putchar(fd, format[i]);
            i++;
            comp++;
        }
    }
    va_end(ap);
    return comp;
}
