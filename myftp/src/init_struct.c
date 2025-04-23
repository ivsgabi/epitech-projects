/*
** EPITECH PROJECT, 2024
** init_struct
** File description:
** myftp
*/

#include <stdlib.h>
#include "myftp.h"

void init_ftp_infos(struct ftp_s *ftp_infos)
{
    ftp_infos->server_fd = 0;
    ftp_infos->max_clients = 10;
    ftp_infos->client_list = malloc(ftp_infos->max_clients * sizeof(int));
    ftp_infos->directory = NULL;
    ftp_infos->user_status = false;
}
