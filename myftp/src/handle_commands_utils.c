/*
** EPITECH PROJECT, 2024
** handle_commands_utils
** File description:
** myftp
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "myftp.h"

char *remove_crtlf(char *str)
{
    for (size_t i = 0; i < strlen(str); i++) {
        if (str[i] == '\r' && str[i + 1] == '\n')
            str[i] = '\0';
    }
    return (str);
}

void reply_150(int client_socket)
{
    dprintf(client_socket, "150 File status okay; about to open\
    data connection.\r\n");
}

void list_success_reply(int client_socket)
{
    dprintf(client_socket, "226 Closing data connection.\
    Requested file listing successful.\r\n");
}
