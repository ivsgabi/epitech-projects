/*
** EPITECH PROJECT, 2023
** mysh_disp
** File description:
** minishell1
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "proto.h"

int command_opt(char **args, char ***env)
{
    int nb_args = args_counter(args);
    if ((my_strcmp(args[0], "env") == 0)
    || (my_strcmp(args[0], "setenv") == 0 && nb_args == 1)) {
        display_env(*env);
        return (0);
    }  if (my_strcmp(args[0], "exit") == 0) {
            if (my_exit(args) == 0) {
                exit(0);
            }
        return (0);
    } if (my_strcmp(args[0], "cd") == 0) {
        *env = my_chdir(args, *env);
        return (0);
    } if (my_strcmp(args[0], "setenv") == 0) {
        *env = my_setenv(*env, args);
        return (0);
    } if (my_strcmp(args[0], "unsetenv") == 0) {
        *env = my_unsetenv(args, *env);
        return (0);
    } return (84);
}
