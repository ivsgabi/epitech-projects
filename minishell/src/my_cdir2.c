/*
** EPITECH PROJECT, 2023
** my_cdir4
** File description:
** function to recode cd, pt.4
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "proto.h"

char* create_currentwd(char *cwd)
{
    int len = my_strlen(cwd) + 4;
    char *new_str = malloc(sizeof(char) * (len + 1));
    new_str[len] = '\0';
    new_str = my_strcpy(new_str, "PWD=");
    new_str = my_strcat(new_str, cwd);
    return (new_str);
}

char *create_pwdstr(char **envcpy)
{
    char *pwd_str = NULL;
    char *final_str = NULL;
    int i = 0;
    int j = 0;
    int k = 0;
    for (i = 0; envcpy[i] != NULL; i++) {
        if (my_strncmp(envcpy[i], "PWD=", 4) == 0) {
            pwd_str = malloc(sizeof(char) * (my_strlen(envcpy[i]) + 1));
            for (j = 4; envcpy[i][j] != '\0'; j++) {
                pwd_str[k] = envcpy[i][j];
                k++;
            }
        }
    } pwd_str[k] = '\0';
    final_str = malloc(sizeof(char) * (my_strlen(pwd_str)) + 7 + 1);
    final_str = my_strcpy(final_str, "OLDPWD=");
    final_str = my_strcat(final_str, pwd_str);
    final_str[my_strlen(pwd_str) + 7] = '\0';
    return (final_str);
}

int cdenv_condition(char **envcpy, char **changed_env, char *cwd, int i)
{
    char *currentwd = create_currentwd(cwd);
    char *pastwd = create_pwdstr(envcpy);
    if (my_strncmp(envcpy[i], "PWD=", 4) == 0) {
        changed_env[i] = currentwd;
    } else if (my_strncmp(envcpy[i], "OLDPWD=", 7) == 0) {
        changed_env[i] = pastwd;
    } else {
        changed_env[i] = my_strdup(envcpy[i]);
    }
    return (0);
}

char **change_cdenv(char **envcpy)
{
    envcpy = verif_env(envcpy);
    int len_arr = size_array(envcpy);
    char cwd[2000];
    char **changed_env = NULL;
    int i = 0;
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        mini_printf("error : can not find the current pwd\n");
        return (NULL);
    }
    changed_env = malloc(sizeof(char *) * (len_arr + 1));
    for (i = 0; envcpy[i] != NULL; i++) {
        cdenv_condition(envcpy, changed_env, cwd, i);
    } changed_env[i] = NULL;
    return (changed_env);
}
