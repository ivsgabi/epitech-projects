/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** ftp
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/socket.h>
#include "myftp.h"

int server_accept(int server_fd, struct sockaddr_in *server_infos)
{
    int addrlen = sizeof(&server_infos);
    int new_socket = accept(server_fd, (SA*)server_infos,
                (socklen_t *)&addrlen);

    if (new_socket < 0) {
        printf("error: accept failed.");
        close(new_socket);
        return (84);
    }
    return (new_socket);
}

static int create_socket_bind_listen(struct sockaddr_in *server_infos,
    int port)
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd < 0) {
        printf("socket creation failed");
        return (84);
    }
    server_infos->sin_family = AF_INET;
    server_infos->sin_addr.s_addr = INADDR_ANY;
    server_infos->sin_port = htons(port);
    if (bind(server_fd, (SA*)server_infos, sizeof(*server_infos)) < 0) {
        printf("error: bind failed.");
        return (close(server_fd), 84);
    }
    if (listen(server_fd, 5) < 0) {
        printf("error: listen failed.");
        close(server_fd);
        return (84);
    }
    return (server_fd);
}

int handle_client_requests(fd_set *fds, struct ftp_s *ftp_infos,
    struct sockaddr_in *server_infos, const char *directory_path)
{
    int new_socket = 0;

    if (FD_ISSET(ftp_infos->server_fd, fds)) {
        new_socket = server_accept(ftp_infos->server_fd, server_infos);
        if (new_socket == 84)
            return 84;
        dprintf(new_socket, "220 Service ready for new user.\r\n");
        add_client_list(ftp_infos, new_socket);
    }
    for (int i = 0; i < ftp_infos->max_clients; i++) {
        if (handle_client(fds, ftp_infos, ftp_infos->client_list[i],
            directory_path) == 84) {
            close(ftp_infos->client_list[i]);
            return (84);
        }
    }
    return (0);
}

int init_ftp_server(struct ftp_s *ftp_infos, struct sockaddr_in *server_infos,
    int port)
{
    init_ftp_infos(ftp_infos);
    for (int i = 0; i < ftp_infos->max_clients; i++) {
        ftp_infos->client_list[i] = 0;
    }
    ftp_infos->server_fd = create_socket_bind_listen(server_infos, port);
    if (ftp_infos->server_fd < 0)
        return (84);
    return (0);
}

int handle_select(struct ftp_s *ftp_infos, struct sockaddr_in *server_infos,
    const char *directory_path)
{
    fd_set fds;
    int result;

    FD_ZERO(&fds);
    FD_SET(ftp_infos->server_fd, &fds);
    fd_set_client_list(&fds, ftp_infos->client_list, ftp_infos->max_clients);
    if (select(FD_SETSIZE, &fds, NULL, NULL, NULL) < 0) {
        printf("error: select failed.");
        close(ftp_infos->server_fd);
        return (84);
    }
    result = handle_client_requests(&fds, ftp_infos, server_infos,
        directory_path);
    if (result == 84)
        return (84);
    return (0);
}

int create_server(int port, const char *directory_path)
{
    struct ftp_s ftp_infos;
    struct sockaddr_in server_infos;

    if (init_ftp_server(&ftp_infos, &server_infos, port) != 0) {
        return (84);
    }
    while (1) {
        if (handle_select(&ftp_infos, &server_infos, directory_path) != 0)
            return (84);
    }
    close_all_clients(&ftp_infos);
    return (0);
}

//printf("Server IP adress %s : %d\n", inet_ntoa(server_infos->sin_addr),
//ntohs(server_infos->sin_port));
//printf("Server is listening on port %d\n", port);
