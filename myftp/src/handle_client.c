/*
** EPITECH PROJECT, 2024
** handle_client
** File description:
** myftp
*/

#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include "myftp.h"

int more_command_conditions(char *buffer, int client_socket)
{
    if (strncmp(buffer, "LIST", 4) == 0)
        return handle_list(client_socket, buffer);
    if (strncmp(buffer, "RETR ", 5) == 0)
        return handle_retr(client_socket, buffer + 5);
    if (strncmp(buffer, "STOR ", 5) == 0)
        return handle_retr(client_socket, buffer + 5);
    return handle_error(client_socket);
}

int command_conditions(struct ftp_s *ftp_infos, char *buffer,
    int client_socket, const char *directory_path)
{
    buffer = remove_crtlf(buffer);
    if (strncmp(buffer, "USER ", 5) == 0)
        return handle_user(ftp_infos, client_socket, buffer + 5);
    if (strncmp(buffer, "PASS ", 5) == 0)
        return handle_pass(ftp_infos, client_socket, buffer, directory_path);
    if (strncmp(buffer, "PWD", 3) == 0)
        return handle_pwd(ftp_infos, client_socket);
    if (strncmp(buffer, "CWD ", 4) == 0)
        return handle_cwd(ftp_infos, client_socket, buffer + 4);
    if (strncmp(buffer, "DELE ", 5) == 0)
        return handle_dele(ftp_infos, client_socket, buffer + 5);
    if (strncmp(buffer, "CDUP", 4) == 0)
        return handle_cdup(ftp_infos, client_socket);
    if (strncmp(buffer, "NOOP", 4) == 0)
        return handle_noop(ftp_infos, client_socket);
    if (strncmp(buffer, "HELP", 4) == 0)
        return handle_help(client_socket);
    if (strncmp(buffer, "QUIT", 4) == 0)
        return handle_quit(ftp_infos, client_socket);
    return more_command_conditions(buffer, client_socket);
}

int handle_client(fd_set *fds, struct ftp_s *ftp_infos, int client_socket,
    const char *directory_path)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    FILE *input_stream;

    if (FD_ISSET(client_socket, fds)) {
        input_stream = fdopen(client_socket, "r");
        if (!input_stream)
            return (84);
        nread = getline(&line, &len, input_stream);
        if (nread < 0)
            return (84);
        if (command_conditions(ftp_infos, line,
            client_socket, directory_path) == 84)
            return (84);
    }
    return (0);
}
