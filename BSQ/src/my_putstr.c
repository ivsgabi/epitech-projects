/*
** EPITECH PROJECT, 2022
** mu_putstr
** File description:
** emacs
*/

void my_putchar(char c);

int my_putstr(char const *str)
{
    while (*str) {
        my_putchar(*str);
        str++;
    }
    return (0);
}
