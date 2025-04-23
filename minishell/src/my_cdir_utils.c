/*
** EPITECH PROJECT, 2023
** my_cdir2
** File description:
** functions cd for minishell1, pt.2
*/

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "proto.h"

int get_knb(char **envcpy, char *env_home, int i, int k)
{
    int j = 5;
    while (envcpy[i][j] != '\0') {
        env_home[k] = envcpy[i][j];
        j++;
        k++;
    }
    return (k);
}

int get_count_home(char **envcpy, int count, int i)
{
    int j = 0;
    j = 5;
    while (envcpy[i][j] != '\0') {
        j++;
        count++;
    }
    return (count);
}

int change_errcase(int change, char **args)
{
    if (change == -1) {
        mini_printf("%s: %s.\n", args[0], strerror(errno));
        return (84);
    }
    return (0);
}

int args_counter(char **args)
{
    int i = 0;
    for (; args[i] != NULL; i++);
    return (i);
}
