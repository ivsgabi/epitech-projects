/*
** EPITECH PROJECT, 2023
** redirect_handler
** File description:
** handle "> >> < <<" in minishell2
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "proto.h"

void check_after_args(char **args)
{
    for (int i = 0; args[i] != NULL; i++) {
        if ((my_strcmp(args[i], ">") == 0 || my_strcmp(args[i], "<") == 0
        || my_strcmp(args[i], ">>") == 0 || my_strcmp(args[i], "<<") == 0)
        && (args[i + 1] == NULL)) {
            mini_printf("Missing name for redirect.\n");
            exit (84);
        }
    }
}

int handle_redirect(char **args)
{
    char *input_file = NULL;
    char *output_file = NULL;
    check_after_args(args);
    if (detect_in(args, &input_file)) {
        if (redirect_input(input_file)) {
            return 1;
        }
    } if (detect_out(args, &output_file)) {
        if (redirect_output(output_file, O_TRUNC)) {
            return 1;
        }
    } if (detect_dbl_out(args, &output_file)) {
        if (redirect_output(output_file, O_APPEND)) {
            return 1;
        }
    } if (detect_dbl_in(args, &output_file)) {
        if (redirect_dbl_input(input_file)) {
            return 1;
        }
    } return 0;
}
