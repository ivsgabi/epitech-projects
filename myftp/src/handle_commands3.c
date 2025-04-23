/*
** EPITECH PROJECT, 2024
** handle_commands3
** File description:
** myftp
*/


#include <unistd.h>
#include <stdio.h>
#include "myftp.h"

int handle_retr(int client_socket, char *buffer)
{
    FILE *file;
    char *line = NULL;
    size_t len = 0;

    file = fopen(buffer, "r");
    if (file == NULL) {
        dprintf(client_socket, "550 File can not be open.\r\n");
        return (42);
    }
    reply_150(client_socket);
    if (getline(&line, &len, file) == -1) {
        dprintf(client_socket, "550 File can not be read.\r\n");
        return (42);
    }
    while (getline(&line, &len, file) != -1) {
        dprintf(client_socket, "%s", line);
    }
    list_success_reply(client_socket);
    return (fclose(file), 0);
}

int handle_stor(int client_socket, char *buffer)
{
    FILE *file;
    char save[1024];

    file = fopen(buffer, "w");
    if (file == NULL) {
        dprintf(client_socket, "550 File can not be open.\r\n");
        return (42);
    }
    reply_150(client_socket);
    while ((recv(client_socket, save, 1024, 0)) > 0) {
        fprintf(file, "%s", save);
    }
    if (recv(client_socket, save, 1024, 0)) {
        dprintf(client_socket, "426 Error receiving data.\r\n");
        return (42);
    }
    list_success_reply(client_socket);
    fclose(file);
    return (0);
}
