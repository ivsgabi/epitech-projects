/*
** EPITECH PROJECT, 2024
** handle_commands3
** File description:
** myftp
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myftp.h"

FILE *get_command_stream(char *command, int client_socket)
{
    FILE *command_output = popen(command, "r");

    if (command_output == NULL) {
        dprintf(client_socket, "550 Requested action not taken.\r\n");
        return (NULL);
    }
    return (command_output);
}

char *get_command(char *buffer)
{
    char *command = malloc(1024);

    if (command == NULL)
        return NULL;
    strcpy(command, "ls -l");
    if (strncmp(buffer, "LIST ", 5) == 0) {
        buffer = buffer + 4;
        strcat(command, buffer);
    }
    return (command);
}

int is_command_working(char *line, size_t len, FILE *ls_output,
    int client_socket)
{
    if (getline(&line, &len, ls_output) == -1) {
        dprintf(client_socket, "550 Requested action not taken.\r\n");
        free(line);
        fclose(ls_output);
        return (42);
    }
    return (0);
}

int handle_list(int client_socket, char *buffer)
{
    char *line = NULL;
    size_t len = 0;
    char *command = get_command(buffer);
    FILE *ls_output = get_command_stream(command, client_socket);

    if (ls_output == NULL)
        return (42);
    reply_150(client_socket);
    if (is_command_working(line, len, ls_output, client_socket) != 0)
        return (42);
    while (getline(&line, &len, ls_output) > 0) {
        dprintf(client_socket, "%s", line);
    }
    free(line);
    fclose(ls_output);
    list_success_reply(client_socket);
    return (0);
}
