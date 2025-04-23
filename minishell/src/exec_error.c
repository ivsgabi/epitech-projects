/*
** EPITECH PROJECT, 2023
** exec_error
** File description:
** handle error handling tests
*/

#include <signal.h>
#include <errno.h>
#include "proto.h"

static const Execve_error_t EXECVE_ERROR[] = {
    {ENOENT, "Command not found.\n"},
    {ENOEXEC, "Exec format error. Wrong architecture.\n"},
    {EACCES, "Permisson denied.\n"},
};

void handle_exec_error(int status)
{
    long unsigned int i = 0;
    while (i < sizeof(EXECVE_ERROR) / sizeof(EXECVE_ERROR[0])) {
        if (status == EXECVE_ERROR[i].code)
            my_putstr(EXECVE_ERROR[i].message);
        i++;
    }
}
