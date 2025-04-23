/*
** EPITECH PROJECT, 2023
** env_error_handling
** File description:
** functions to handle disfunctional env
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "proto.h"

char **verif_env(char **envcpy)
{
    char cwd[2000];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        mini_printf("error : can not find the current pwd\n");
        return (NULL);
    }
    char *edit_path[] = {"setenv", "PATH", "/bin:/usr/bin", NULL};
    char *edit_pwd[] = {"setenv", "PWD", cwd, NULL};
    char *edit_oldpwd[] = {"setenv", "OLDPWD", "$PATH", NULL};
    char *edit_term[] = {"setenv", "TERM", "xterm", NULL};

    if (is_variable_exist(envcpy, "PATH=", 5) == 0) {
        envcpy = my_setenv(envcpy, edit_path);
    } if (is_variable_exist(envcpy, "PWD=", 4) == 0) {
        envcpy = my_setenv(envcpy, edit_pwd);
    } if (is_variable_exist(envcpy, "OLDPWD=", 7) == 0) {
        envcpy = my_setenv(envcpy, edit_oldpwd);
    } if (is_variable_exist(envcpy, "TERM=", 5) == 0) {
        envcpy = my_setenv(envcpy, edit_term);
    }
    return (envcpy);
}
