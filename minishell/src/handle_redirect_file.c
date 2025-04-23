/*
** EPITECH PROJECT, 2023
** handle_redirect
** File description:
** handle redirections for minishell2 (second file)
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "proto.h"

int redirect_input(char *input_file)
{
    int input_fd = open(input_file, O_RDONLY);
    if (input_fd == -1) {
        perror("open");
        return (84);
    }
    if (dup2(input_fd, STDIN_FILENO) == -1) {
        perror("dup2");
        return (84);
    }
    return 0;
}

int redirect_output(char *output_file, int flag)
{
    int output_fd = open(output_file, O_WRONLY | O_CREAT | flag,
    S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (output_fd == -1) {
        perror("open");
        return (84);
    }
    if (dup2(output_fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        return (84);
    }
    return 0;
}

int redirect_dbl_input(char *input_file)
{
    int input_fd = open(input_file, O_RDONLY);
    if (input_fd == -1) {
        perror("open");
        return (84);
    }
    if (dup2(input_fd, STDIN_FILENO) == -1) {
        perror("dup2");
        return (84);
    }
    return 0;
}
