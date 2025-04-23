/*
** EPITECH PROJECT, 2023
** my_cdir
** File description:
** recode cd function for minishell1
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "proto.h"

char **my_chdir(char **args, char **envcpy)
{
    int nb_args = args_counter(args);
    int change = 0;
    char *home = get_home(envcpy);
    char *past_dir = get_pastdir(envcpy);

    if (nb_args == 1 || (nb_args == 2 && args[1][0] == '~')) {
        change = chdir(home);
        change_errcase(change, args);
    } else if (nb_args == 2 && args[1][0] == '-') {
        change = chdir(past_dir);
        change_errcase(change, args);
    } else {
        change = chdir(args[1]);
        change_errcase(change, args);
    }
    envcpy = change_cdenv(envcpy);
    return (envcpy);
}
