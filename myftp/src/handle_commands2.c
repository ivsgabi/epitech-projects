/*
** EPITECH PROJECT, 2024
** handle_commands2
** File description:
** myftp
*/

#include <stdio.h>
#include <libgen.h>
#include <string.h>
#include <stdlib.h>
#include "myftp.h"

int handle_pwd(struct ftp_s *ftp_infos, int client_socket)
{
    char working_directory[1024];

    if (ftp_infos->user_status == false) {
        dprintf(client_socket, "530 Please log in first.\r\n");
        return (42);
    }
    if (getcwd(working_directory, sizeof(working_directory)) != NULL) {
        dprintf(client_socket, "257 \"%s\" created.\r\n", working_directory);
    } else {
        printf("error: getcwd() failed.");
        return (84);
    }
    return (0);
}

int handle_cwd(struct ftp_s *ftp_infos, int client_socket, char *buffer)
{
    char directory[1024];

    if (ftp_infos->user_status == false) {
        dprintf(client_socket, "530 Please log in first.\r\n");
        return (42);
    }
    if (chdir(buffer) < 0) {
        dprintf(client_socket, "550 Requested action not taken.\r\n");
        return (42);
    }
    ftp_infos->directory = getcwd(directory, sizeof(directory));
    if (ftp_infos->directory == NULL)
        return (84);
    dprintf(client_socket, "250 Requested file action okay, completed.\r\n");
    return (0);
}

int handle_cdup(struct ftp_s *ftp_infos, int client_socket)
{
    char directory[1024];

    if (ftp_infos->user_status == false) {
        dprintf(client_socket, "530 Please log in first.\r\n");
        return (42);
    }
    if (getcwd(directory, sizeof(directory)) == NULL) {
        printf("error: getcwd() failed.");
        return (84);
    }
    if (dirname(directory) == NULL) {
        printf("error: dirname() failed.");
        return (84);
    }
    chdir(dirname(directory));
    ftp_infos->directory = getcwd(directory, sizeof(directory));
    if (ftp_infos->directory == NULL)
        return (84);
    dprintf(client_socket, "200 Command okay.\r\n");
    return (0);
}

int handle_dele(struct ftp_s *ftp_infos, int client_socket, char *buffer)
{
    int remove_status = 0;
    char filepath[1024];

    if (ftp_infos->user_status == false) {
        dprintf(client_socket, "530 Please log in first.\r\n");
        return (42);
    }
    getcwd(filepath, sizeof(filepath));
    strcat(filepath, "/");
    strcat(filepath, buffer);
    if (access(filepath, F_OK) != 0) {
        dprintf(client_socket, "550 File not found\r\n");
        return (42);
    }
    remove_status = remove(filepath);
    if (remove_status != 0)
        return (42);
    dprintf(client_socket, "250 Requested file action okay, completed.\r\n");
    return (0);
}

int handle_error(int client_socket)
{
    dprintf(client_socket, "500 Unrecognised command, try HELP.\r\n");
    return (42);
}

//printf("buffer (before) = %s\n", buffer);
//printf("buffer (after) = %s\n", buffer);

//if (remove_status != 0) {
//        dprintf(client_socket, "error: remove() failed\r\n");
//        return (42);
//    } -> to win a line
