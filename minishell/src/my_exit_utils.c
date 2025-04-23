/*
** EPITECH PROJECT, 2023
** my_exit_utils
** File description:
** utils for exit fct
*/

#include "proto.h"

int my_isalpha(int c)
{
    if (c >= 'A' && c <= 'Z') {
        return 0;
    } if (c >= 'a' && c <= 'z') {
        return 0;
    } return 84;
}

int my_isdigit(int c)
{
    if (c >= '0' && c <= '9') {
        return 0;
    } return 84;
}
