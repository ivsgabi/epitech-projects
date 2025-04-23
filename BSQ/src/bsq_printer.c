/*
** EPITECH PROJECT, 2022
** bsq_printer
** File description:
** fuunction to print the final result
*/

#include "../include/my.h"
#include <stdio.h>
#include <stdlib.h>

char *delete_first_line(char *buffer)
{
    char *str = NULL;
    int i = 0, j = 0;
    while (buffer[i] != '\0') {
        i++;
        if (buffer[i] == '\n') {
            i++;
            str[j] = buffer[i];
        } while (buffer[i] == '\0') {
            i++;
            j++;
            str[j] = buffer[i];
        }
    } return str;
}

void got_x_bsq(int **map, int nb_rows, int nb_cols,
struct save_important_values *index)
{
    char *buffer = malloc(sizeof(char) * index->size);
    int a = 0;

    for (int i = 0; i < nb_rows; i++, a++) {
        for (int j = 0; j < nb_cols; j++, a++) {
            got_x_bsq_bis(buffer, index, map, i, j, a);
        } buffer[a] = '\n';
    } for (int i = 0; buffer[i]; i++)
        mini_printf("%c", buffer[i]);
}

void got_x_bsq_bis(char* buffer, struct save_important_values *index,
int **map, int i, int j, int a)
{
    if (map[i][j] == 0)
        buffer[a] = 'o';
    else if (i > index->save_i - index->biggest_square
&& j > index->save_j - index->biggest_square
&& i <= index->save_i && j <= index->save_j)
        buffer[a] = 'x';
    else
        buffer[a] = '.';
}
