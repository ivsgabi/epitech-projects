/*
** EPITECH PROJECT, 2022
** BSQ_base
** File description:
** basis function for BSQ project
*/

#include <stddef.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "../include/my.h"

char *open_read_file(char *str)
{
    char *buffer = NULL;
    int fd = 0;
    struct stat size;
    if ((fd = open(str, O_RDONLY)) <= 0)
        return NULL;
    if (stat(str, &size) < 0)
        return NULL;
    buffer = malloc(sizeof(char) * (size.st_size + 1));
    if (read(fd, buffer, size.st_size) <= 0)
        return NULL;
    buffer[size.st_size] = '\0';
    close(fd);
    return (buffer);
}

int **board(char *buffer, int nb_rows, int nb_cols)
{
    int x = 0; int y = 0; int i = 0;
    int **board = malloc(sizeof(int *) * (nb_rows + 2));
    if (board == NULL)
        return NULL;
    for (int i = 0; i < nb_rows; i++)
        board[i] = malloc(sizeof(int) * (nb_cols + 2));

    for (; buffer[i] != '\n'; i++);
    i++;
    for (; buffer[i] != '\0'; i++) {
        if (buffer[i] == '\n') {
            y++;
            x = 0;
        } else {
            board[y][x] = buffer[i] == '.' ? 1 : 0;
            x++;
        }
    }
    return (board);
}

int main(int argc, char **argv)
{
    char *buffer = open_read_file(argv[1]);
    if (argc != 2) {
        mini_printf("%s", "missing one argument");
        return (84);
    } if (buffer[0] == '0') {
        return (84);
    } if (buffer == NULL) {
        return (84);
    } else {
        struct save_important_values save_index_t;
        int nb_rows = rows_counter(buffer);
        int nb_cols = cols_counter(buffer);
        int **map = board(buffer, nb_rows, nb_cols);
        my_bsq(map, &save_index_t, nb_rows, nb_cols);
        got_x_bsq(map, nb_rows, nb_cols, &save_index_t);
    }
    return (0);
}
