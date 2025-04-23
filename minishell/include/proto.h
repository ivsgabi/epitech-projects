/*
** EPITECH PROJECT, 2023
** proto header
** File description:
** for minishell2
*/

#include <stdbool.h>
#include <stdarg.h>
#include <stddef.h>

typedef struct Execve_error_s {
    int code;
    const char *message;
} Execve_error_t;

#ifndef PROTO_H_
    #define PROTO_H_
    #define UNUSED __attribute__ ((unused))
void my_putchar(char c);
int my_putstr(char const *str);
int my_put_nbr(int nb);
int my_strlen(char const *str);
int mini_printf(const char *format, ...);
void conditions(va_list ap, int i, const char *format, ...);
int my_strcmp(char *str1, char *str2);
char *my_strncat(char *dest, const char *src, size_t n);
char *my_strcpy(char *dest, const char *src);
char *my_strdup(const char *s);
int my_strncmp(const char *s1, const char *s2, size_t n);
char *my_strcat(char *dest, char const *src);
int get_command(char **env);
void parse_command(char *line, char **args);
int init_processes(char **args, char ***env);
int processes_condition(char **args, char ***env);
void parse_semicolons(char *line, char ***envcpy);
bool is_semicolons(char *str);
int command_opt(char **args, char ***env);
void display_env(char **env);
char** my_envcpy(char **env);
int rows_counter(char **arr);
int segfault_handler(int status);
char *path_handling(char **args, char **envcpy);
char **get_2dpath(char **envcpy);
char **strtok_array(char *buffer, char *delim);
char **my_setenv(char **envcpy, char **args);
char **my_chdir(char **args, char **envcpy);
char *get_home(char **envcpy);
char *create_homestr(char **envcpy, char *env_home, int i, int k);
char *create_pastdirstr(char **envcpy, char *past_dir, int i, int k);
char *get_pastdir(char **envcpy);
int get_count_pastdir(char **envcpy, int count, int i);
int get_knb_pastdir(char **envcpy, char *past_dir, int i, int k);
bool is_variable_exist(char **envcpy, char *name, int len_name);
char *create_filled_elem(char **args);
int size_array(char **envcpy);
char* create_currentwd(char *cwd);
char *create_pwdstr(char **envcpy);
int cdenv_condition(char **envcpy, char **changed_env, char *cwd, int i);
char **change_cdenv(char **envcpy);
int args_counter(char **args);
char **my_unsetenv(char **args, char **envcpy);
int compare_args(char **args, char **envcpy, int i);
int change_errcase(int change, char **args);
int get_count_home(char **envcpy, int count, int i);
int get_knb(char **envcpy, char *env_home, int i, int k);
int condition_nb_args(char **envcpy, int nb_args);
char **verif_env(char **envcpy);
void handle_exec_error(int status);
void execve_condition(char **args, char ***env);
int handle_redirect(char **args);
int redirect_output(char *output_file, int flag);
int redirect_input(char *input_file);
int redirect_dbl_input(char *input_file);
int detect_dbl_in(char **args, char **output_file);
int detect_dbl_out(char **args, char **output_file);
int detect_out(char **args, char **output_file);
int detect_in(char **args, char **input_file);
int my_exit(char **args);
int my_isalpha(int c);
int my_isdigit(int c);
void free_array(char **array);
#endif
