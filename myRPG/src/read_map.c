/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** read_map.c
*/

#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include "utils.h"

char **read_map(char const *file)
{
    char *content_file = NULL;
    struct stat st;
    int fd = open(file, O_RDONLY);
    if (fd == -1 || stat(file, &st) == -1)
        return NULL;
    content_file = malloc(sizeof(char) * (st.st_size + 1));
    content_file[st.st_size] = '\0';
    if (content_file == NULL)
        return NULL;
    if (read(fd, content_file, st.st_size) == -1)
        return NULL;
    close(fd);
    char **map = my_str_to_word_array(content_file);
    if (map == NULL)
        return NULL;
    return map;
}
