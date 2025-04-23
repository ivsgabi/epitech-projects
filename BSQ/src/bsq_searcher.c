/*
** EPITECH PROJECT, 2022
** bsq_searcher
** File description:
** find the BSQuare
*/

#include <stdio.h>
#include "../include/my.h"

void values_comparator_bis(int **tab, int x, int y)
{
    if (tab[x - 1][y] <= tab[x - 1][y - 1] && tab[x - 1][y] <= tab[x][y - 1]) {
        tab[x][y] = tab[x - 1][y] + 1;
    } else if (tab[x - 1][y - 1] <= tab[x][y - 1] &&
tab[x - 1][y - 1] <= tab[x - 1][y]) {
        tab[x][y] = tab[x - 1][y - 1] + 1;
    } else {
        tab[x][y] = tab[x][y - 1] + 1;
    }
}

void values_comparator(int **tab, int x, int y)
{
    if (tab[x][y] == 0 || tab[x - 1][y] == 0 || tab[x - 1][y - 1] == 0
        || tab[x - 1][y] == 0 || tab[x][y - 1] == 0)
        y++;
    else
        values_comparator_bis(tab, x, y);
}

void my_bsq(int **tab, struct save_important_values *index,
            int nb_rows, int nb_cols)
{
    index->biggest_square = 1;
    index->save_i = 0;
    index->save_j = 0;
    index->size = nb_rows * nb_cols;
    for (int i = 1; i < nb_rows; i++) {
        for (int j = 1; j < nb_cols; j++) {
            values_comparator(tab, i, j);
            my_bsq_bis(tab, i, j, index);
        }
    }
}

void my_bsq_bis(int **tab, int i, int j, struct save_important_values *index)
{
    if (tab[i][j] > index->biggest_square) {
        index->save_i = i;
        index->save_j = j;
        index->biggest_square = tab[i][j];
    }
}
