/*
** EPITECH PROJECT, 2024
** handle_commands
** File description:
** myftp
*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include "myftp.h"

int handle_user(struct ftp_s *ftp_infos, int client_socket, char *buffer)
{
    char *server_reply = "331 User name okay, need password.\r\n";

    if (strcmp(buffer, "Anonymous") == 0)
        ftp_infos->user_status = true;
    dprintf(client_socket, "%s", server_reply);
    return (0);
}

int handle_pass(struct ftp_s *ftp_infos, int client_socket, char *buffer,
    const char *directory_path)
{
    char *server_reply;
    char directory[1024];

    if (ftp_infos->user_status == true && strcmp(buffer, "PASS ") == 0)
        server_reply = "230 User logged in, proceed.\r\n";
    else
        server_reply = "530 Wrong password, try again.\r\n.";
    dprintf(client_socket, "%s", server_reply);
    chdir(directory_path);
    ftp_infos->directory = getcwd(directory, sizeof(directory));
    if (ftp_infos->directory == NULL)
        return (84);
    return (0);
}

int handle_noop(struct ftp_s *ftp_infos, int client_socket)
{
    if (ftp_infos->user_status == false) {
        dprintf(client_socket, "530 Please log in first.\r\n");
        return (42);
    }
    dprintf(client_socket, "200 Command okay.\r\n");
    return (0);
}

int handle_help(int client_socket)
{
    dprintf(client_socket, "214 Help message.On how \
    to use the server or the meaning of a \
    particular non-standard command. This reply is \
    useful only to the human user.\r\n");
    return (0);
}

int handle_quit(struct ftp_s *ftp_infos, int client_socket)
{
    dprintf(client_socket, "221 Service closing control connection.\
    Logged out if appropriate.\r\n");
    for (int i = 0; i < ftp_infos->max_clients; i++) {
        ftp_infos->client_list[i] = 0;
    }
    if (close(client_socket) < 0)
        return (84);
    return (0);
}
