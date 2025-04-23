/*
** EPITECH PROJECT, 2023
** get_envhome
** File description:
** get home str in env for minishell2
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "proto.h"

char *create_homestr(char **envcpy, char *env_home, int i, int k)
{
    int j = 5;
    while (envcpy[i][j] != '\0') {
        env_home[k] = envcpy[i][j];
        j++;
        k++;
    }
    return (env_home);
}

char *get_home(char **envcpy)
{
    int i = 0; int k = 0;
    int count = 0;
    char *env_home = NULL;
    for (; envcpy[i] != NULL; i++) {
        if (envcpy[i][0] == 'H' && envcpy[i][1] == 'O'
            && envcpy[i][2] == 'M' && envcpy[i][3] == 'E'
            && envcpy[i][4] == '=') {
            count = get_count_home(envcpy, count, i);
            env_home = malloc(sizeof(char) * (count + 1));
            env_home = create_homestr(envcpy, env_home, i, k);
            k = get_knb(envcpy, env_home, i, k);
            env_home[k] = '\0';
        }
    } return (env_home);
}
