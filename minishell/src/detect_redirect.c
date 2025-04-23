/*
** EPITECH PROJECT, 2023
** detect_redirect
** File description:
** detection redirection symbol in command line for minishell2
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "proto.h"

int detect_in(char **args, char **input_file)
{
    for (int i = 0; args[i] != NULL; i++) {
        if (my_strcmp(args[i], "<") == 0) {
            *input_file = args[i + 1];
            args[i] = NULL;
            return 1;
        }
    }
    return 0;
}

int detect_out(char **args, char **output_file)
{
    for (int i = 0; args[i] != NULL; i++) {
        if (my_strcmp(args[i], ">") == 0) {
            *output_file = args[i + 1];
            args[i] = NULL;
            return 1;
        }
    }
    return 0;
}

int detect_dbl_out(char **args, char **output_file)
{
    for (int i = 0; args[i] != NULL; i++) {
        if (my_strcmp(args[i], ">>") == 0) {
            *output_file = args[i + 1];
            args[i] = NULL;
            return 1;
        }
    }
    return 0;
}

int detect_dbl_in(char **args, char **output_file)
{
    for (int i = 0; args[i] != NULL; i++) {
        if (my_strcmp(args[i], "<<") == 0) {
            *output_file = args[i + 1];
            args[i] = NULL;
            return 1;
        }
    }
    return 0;
}
