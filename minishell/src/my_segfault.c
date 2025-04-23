/*
** EPITECH PROJECT, 2023
** my_segfault
** File description:
** segfault handler for minishell1
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include "proto.h"

int segfault_handler(int status)
{
    int sig = WTERMSIG(status);
        if (sig == SIGSEGV) {
            my_putstr("Segmentation fault\n");
            return (84);
        } if (sig == SIGFPE) {
            my_putstr("Floation exception\n");
            return (84);
        } if (__WCOREDUMP(status)) {
            my_putstr("Segmentation fault (core dumped)\n");
        }
    return (0);
}
