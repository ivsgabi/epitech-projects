/*
** EPITECH PROJECT, 2023
** my_unsetenv
** File description:
** recodification of unsetenv for minishell1
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "proto.h"

int compare_args(char **args, char **envcpy, int i)
{
    int keep_variable = 1;
    int nb_args = args_counter(args) - 1;
    for (int k = 1; k <= nb_args; k++) {
        if (my_strncmp(envcpy[i], args[k], my_strlen(args[k])) == 0) {
            keep_variable = 0;
            break;
        }
    } return (keep_variable);
}

char **my_unsetenv(char **args, char **envcpy)
{
    int nb_args = args_counter(args);
    if (nb_args == 1) {
        mini_printf("unsetenv: Too few arguments.\n");
    }
    int i, j;
    int len_arr = size_array(envcpy);
    char **unset_env = malloc(sizeof(char *) * (len_arr + 1));

    for (i = 0, j = 0; envcpy[i] != NULL; i++) {
        int keep_variable = compare_args(args, envcpy, i);
        if (keep_variable) {
            unset_env[j] = malloc(sizeof(char) * (my_strlen(envcpy[i]) + 1));
            my_strcpy(unset_env[j], envcpy[i]);
            j++;
        }
    } unset_env[j] = NULL;
    return (unset_env);
}
