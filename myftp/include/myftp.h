/*
** EPITECH PROJECT, 2024
** ftp header
** File description:
** ftp
*/

#ifndef _MY_FTP_H_
    #define _MY_FTP_H_
    #define SA struct sockaddr
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <stdbool.h>
    #include <sys/select.h>
    #include <sys/types.h>
    #include <dirent.h>

typedef struct ftp_s {
    int server_fd;
    int max_clients;
    int *client_list;
    char *directory;
    bool user_status;
} ftp_t;

int check_args(int argc, const char **argv);
int display_help(void);
int create_server(int port, const char *directory_path);
void close_all_clients(struct ftp_s *ftp_infos);
void fd_set_client_list(fd_set *fds, int *client_list, int max_clients);
void add_client_list(struct ftp_s *ftp_infos, int new_socket);
void init_ftp_infos(struct ftp_s *ftp_struct);
int handle_client(fd_set *fds, struct ftp_s *ftp_infos, int client_socket,
    const char *directory_path);
int handle_user(struct ftp_s *ftp_infos, int client_socket, char *buffer);
int handle_pass(struct ftp_s *ftp_infos, int client_socket, char *buffer,
    const char *directory_path);
int handle_noop(struct ftp_s *ftp_infos, int client_socket);
int handle_help(int client_socket);
int handle_pwd(struct ftp_s *ftp_infos, int client_socket);
int handle_cwd(struct ftp_s *ftp_infos, int client_socket, char *buffer);
int handle_list(int client_socket, char *buffer);
int handle_dele(struct ftp_s *ftp_infos, int client_socket, char *buffer);
int handle_cdup(struct ftp_s *ftp_infos, int client_socket);
int handle_retr(int client_socket, char *buffer);
int handle_stor(int client_socket, char *buffer);
int handle_quit(struct ftp_s *ftp_infos, int client_socket);
int handle_error(int client_socket);
char *remove_crtlf(char *str);
void reply_150(int client_socket);
void list_success_reply(int client_socket);

#endif
