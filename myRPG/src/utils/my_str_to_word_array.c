/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** my_str_to_word_array.c
*/

#include <stddef.h>
#include <stdlib.h>
#include "utils.h"

char **my_str_to_word_array(char const *str)
{
    if (str == NULL)
        return NULL;
    int nb_words = count_nb_lines(str);
    int len_word = 0, start = 0, j, index = 0;
    char **info = malloc(sizeof(char *) * (nb_words + 1));
    info[nb_words] = NULL;
    for (int i = 0; i < nb_words; i++) {
        len_word = len_line(str, start);
        info[i] = malloc(sizeof(char) * (len_word + 1));
        if (info[i] == NULL)
            return NULL;
        for (j = 0; j < len_word; j++, index++) {
            (str[index] == '\n') ? index++ : 0;
            info[i][j] = str[index];
        }
        info[i][j] = '\0';
        start = index + 1;
    }
    return info;
}

char **parse_line(char const *str)
{
    if (str == NULL)
        return NULL;
    int nb_words = count_words(str);
    int len_word = 0, start = 0, j, index = 0;
    char **info = malloc(sizeof(char *) * (nb_words + 1));
    info[nb_words] = NULL;
    for (int i = 0; i < nb_words; i++) {
        len_word = len_words(str, start);
        info[i] = malloc(sizeof(char) * (len_word + 1));
        if (info[i] == NULL)
            return NULL;
        for (j = 0; j < len_word; j++, index++) {
            (str[index] == ';') ? index++ : 0;
            info[i][j] = str[index];
        }
        info[i][j] = '\0';
        start = index + 1;
    }
    return info;
}
