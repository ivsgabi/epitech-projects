##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## FTP
##

CC		=	gcc

CFLAGS		+=	-Wall -Wextra

CPPFLAGS	+=	-I./include

SRC		=	src/main.c		\
			src/check_args.c \
			src/display_help.c	\
			src/create_server.c	\
			src/create_server_utils.c	\
			src/init_struct.c	\
			src/handle_client.c 	\
			src/handle_commands.c	\
			src/handle_commands2.c	\
			src/handle_commands3.c	\
			src/handle_list.c	\
			src/handle_commands_utils.c

OBJ		=	$(SRC:.c=.o)

NAME		=	myftp


all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean:	clean
	$(RM) $(NAME)
	$(RM) *.c~
	$(RM) vgcore*
	$(RM) *~

re: fclean all

debug: CFLAGS += -g
debug: $(NAME)

.PHONY: all clean fclean re debug
