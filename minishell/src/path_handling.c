/*
** EPITECH PROJECT, 2023
** path_handling
** File description:
** to parse and use path line in env for minishell2
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include "proto.h"

// t'as cassé ton env, revoie les pointeurs msr
// besoin d'une copy pr pas tout casser

char **get_2dpath(char **envcpy)
{
    char **envcpy2 = my_envcpy(envcpy);
    char **path = NULL;
    for (int i = 0; envcpy2[i] != NULL; i++) {
        if (my_strncmp(envcpy2[i], "PATH=", 5) == 0) {
            path = strtok_array(envcpy2[i] + 5, ":");
        }
    }
    return (path);
}

char *path_handling(char **args, char **envcpy)
{
    char *path_str;
    char **path = get_2dpath(envcpy);
    int len;
    if (args == NULL || *args == NULL)
        return NULL;
    for (int i = 0; path[i]; i++) {
        len = my_strlen(path[i]) + my_strlen(args[0]) + my_strlen("/");
        path_str = malloc(sizeof(char) * (len + 1));
        my_strcpy(path_str, path[i]);
        my_strcat(path_str, "/");
        my_strcat(path_str, args[0]);
        path_str[len] = '\0';
        if (access(path_str, X_OK || F_OK) == 0) {
            return (path_str);
        } free(path_str);
    } return args[0];
}
