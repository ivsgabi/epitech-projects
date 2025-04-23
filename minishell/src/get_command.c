/*
** EPITECH PROJECT, 2023
** myshell_base
** File description:
** basis for minishell project
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>
#include "proto.h"

void execve_condition(char **args, char ***env)
{
    char *cmd = path_handling(args, *env);
    if (execve(cmd, args, *env) == -1) {
            mini_printf("%s: ", args[0]);
            handle_exec_error(errno);
            exit(-1);
        }
}

int processes_condition(char **args, char ***env)
{
    int status = 0;
    pid_t pid = fork();
    if (pid < 0) {
        return (84);
    } else if (pid == 0) {
        handle_redirect(args);
        execve_condition(args, env);
    } else {
        wait(&status);
        segfault_handler(status);
        kill(pid, status);
    }
    return (0);
}

int init_processes(char **args, char ***env)
{
    if (command_opt(args, env) == 84) {
        processes_condition(args, env);
    }
    return (0);
}

int get_command(char **env)
{
    char *line = NULL; char *args[30];
    size_t line_len = 0; int len = 0;
    char **envcpy = my_envcpy(env);
    envcpy = verif_env(envcpy);
    while (1) {
        write(1, "$> ", 3);
        len = getline(&line, &line_len, stdin);
        if (len == -1)
            break;
        line[len - 1] = '\0';
        if (*line == '\0')
            continue;
        if (is_semicolons(line) == 1) {
            parse_semicolons(line, &envcpy);
        } else {
            parse_command(line, args);
            init_processes(args, &envcpy);
        }
    } free(line);
    return (0);
}
