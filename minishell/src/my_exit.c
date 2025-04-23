/*
** EPITECH PROJECT, 2023
** exit
** File description:
** for minishell2
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include "proto.h"

int verif_str(char *str)
{
    int has_digits = 0;
    int has_letters = 0;
    int i = 0;
    for (i = 0; i < my_strlen(str); i++) {
        if (my_isdigit(str[i]) == 0) {
            has_digits = 1;
        } if (my_isalpha(str[i]) == 0) {
            has_letters = 1;
        }
    } if (has_digits > 0 && has_letters == 0) {
        exit(0);
        return (0);
    } if (has_digits == 0 && has_letters > 0) {
        mini_printf("exit: Expression Syntax.\n");
    } else {
        mini_printf("exit: Badly formed number.\n");
    }
    return (1);
}

int my_exit(char **args)
{
    int nb_args = args_counter(args);

    if (nb_args > 2) {
        mini_printf("exit: Expression Syntax.\n");
    } else if (nb_args == 2) {
        return (verif_str(args[1]) == 0 ? 0 : 1);
    } else {
        return (0);
    }
    return (1);
}

// have to atoi
