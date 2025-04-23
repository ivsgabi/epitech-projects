/*
** EPITECH PROJECT, 2024
** create_server_utils
** File description:
** myftp
*/

#include "myftp.h"

void close_all_clients(struct ftp_s *ftp_infos)
{
    for (int i = 0; i < ftp_infos->max_clients; i++) {
        close(ftp_infos->client_list[i]);
    }
}

void fd_set_client_list(fd_set *fds, int *client_list, int max_clients)
{
    for (int i = 0; i < max_clients; i++) {
        if (client_list[i] > 0)
            FD_SET(client_list[i], fds);
    }
}

void add_client_list(struct ftp_s *ftp_infos, int new_socket)
{
    for (int i = 0; i < ftp_infos->max_clients; i++) {
        if (ftp_infos->client_list[i] == 0) {
            ftp_infos->client_list[i] = new_socket;
            break;
        }
    }
}
