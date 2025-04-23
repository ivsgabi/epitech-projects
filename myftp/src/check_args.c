/*
** EPITECH PROJECT, 2024
** checkArgs
** File description:
** FTP
*/

#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include "myftp.h"

static bool is_number(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (isdigit(str[i]) == 0)
            return (false);
    }
    return (true);
}

static bool is_directory(const char *directoryPath)
{
    DIR *directoryfd = opendir(directoryPath);

    if (directoryfd == NULL)
        return (false);
    return (true);
}

int check_args(int argc, const char **argv)
{
    if (argc != 3 || (argc == 2 && strcmp(argv[1], "-h") == 0)
    || (argc == 2 && strcmp(argv[1], "-help") == 0))
        return (display_help());
    if (is_number(argv[1]) != true) {
        printf("error: invalid port number");
        return (84);
    }
    if (is_directory(argv[2]) != true) {
        printf("error: can't open the given directory");
        return (84);
    }
    return (0);
}

//dir = readdir(directoryfd);
//    if (dir == NULL)
//        return (false);
