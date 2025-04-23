/*
** EPITECH PROJECT, 2024
** main
** File description:
** FTP
*/

#include <stdlib.h>
#include "myftp.h"

int main(int argc, const char **argv)
{
    int port = 0;
    const char *directory_path;

    if (check_args(argc, argv) != 0)
        return (84);
    port = atoi(argv[1]);
    directory_path = argv[2];
    if (create_server(port, directory_path) != 0)
        return (84);
    return (0);
}
