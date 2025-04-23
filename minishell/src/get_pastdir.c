/*
** EPITECH PROJECT, 2023
** my_cdir3
** File description:
** cd functions for minishell1, pt.3
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "proto.h"

int get_knb_pastdir(char **envcpy, char *past_dir, int i, int k)
{
    int j = 7;
    while (envcpy[i][j] != '\0') {
        past_dir[k] = envcpy[i][j];
        j++;
        k++;
    }
    return (k);
}

int get_count_pastdir(char **envcpy, int count, int i)
{
    int j = 7;
    while (envcpy[i][j] != '\0') {
        j++;
        count++;
    }
    return (count);
}

char *create_pastdirstr(char **envcpy, char *past_dir, int i, int k)
{
    int j = 7;
    while (envcpy[i][j] != '\0') {
        past_dir[k] = envcpy[i][j];
        j++;
        k++;
    }
    return (past_dir);
}

char *get_pastdir(char **envcpy)
{
    int i = 0; int k = 0;
    int count = 0;
    char *past_dir = NULL;
    for (; envcpy[i] != NULL; i++) {
        if (envcpy[i][0] == 'O' && envcpy[i][1] == 'L'
            && envcpy[i][2] == 'D' && envcpy[i][3] == 'P'
            && envcpy[i][4] == 'W' && envcpy[i][5] == 'D'
            && envcpy[i][6] == '=') {
            count = get_count_pastdir(envcpy, count, i);
            past_dir = malloc(sizeof(char) * (count + 1));
            past_dir = create_pastdirstr(envcpy, past_dir, i, k);
            k = get_knb_pastdir(envcpy, past_dir, i, k);
            past_dir[k] = '\0';
        }
    } return (past_dir);
}
