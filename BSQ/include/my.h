/*
** EPITECH PROJECT, 2022
** my.h
** File description:
** header for BSQ project
*/

#include <stdarg.h>

#pragma once
#ifndef MY_H_
    #define MY_H_
typedef struct save_important_values {
    int save_i;
    int save_j;
    int biggest_square;
    int size;
} save_index_t;
void my_putchar(char c);
int my_put_nbr(int nb);
int my_putstr(char const *str);
char *my_strcpy(char *dest, char const *src);
int mini_printf(const char *format, ...);
void conditions(va_list ap, int i, const char *format, ...);
char *open_read_file(char *str);
int** board(char *buffer, int nb_rows, int nb_cols);
int **load_2d_arr_from_file(char *buffer, int nb_rows, int nb_cols);
int main(int ac, char **av);
void reverse_minesweeper(unsigned short **tab, save_index_t *index);
int cols_counter(char *str);
int rows_counter(char *str);
void my_bsq(int **tab, struct save_important_values *index,
int nb_cols, int nb_rows);
void my_bsq_bis(int **tab, int i, int j,
struct save_important_values *index);
void got_x_bsq(int **buffer, int nb_rows,
int nb_cols, struct save_important_values *index);
void got_x_bsq_bis(char* buffer, struct save_important_values *index,
    int **map, int i, int j, int a);
char* delete_first_line(char *buffer);
#endif
