/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** utils.h
*/

#ifndef UTILS_H
    #define UTILS_H

    typedef struct put_float_s {
        int t;
        float temp;
        int n;
        int entier;
    } float_t;

int count_nb_lines(char const *str);
int len_line(char const *str, int start);
char *my_strcpy(char *dest, char const *src);
char *my_strdup(const char *str);
int my_strlen(char const *str);
char **my_str_to_word_array(char const *file);
double my_atof(char const *str);
int my_atoi(const char *str);
int len_words(char const *str, int start);
int count_words(char const *str);
char **parse_line(char const *str);
char *my_strcat(char *dest, char const *src);
int my_strcmp(char *s1, char *s2);
char *my_itoa(int nb);
int my_strlen(char const *str);
int my_putstr(int fd, char const *str);
int my_put_nbr(int fd, int nb);
void my_put_float(int fd, float nb, int n, char f);
void my_putchar(int fd, char c);
void display_f(int fd, int n, float temp);
int mini_printf(int fd, const char *format, ...);

#endif /* UTILS_H */
