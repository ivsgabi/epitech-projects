##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## for minishell2
##

CC		=	gcc -Wall -Wextra

CFLAGS		=	-I include

NAME		=	mysh

SRC		=  	./src/main.c	\
			./src/get_command.c	\
			./src/parse_command.c	\
			./src/path_handling.c	\
			./src/strtok_array.c	\
			./src/command_gestion.c	\
			./src/exec_error.c	\
			./src/my_envcpy.c	\
			./src/my_unsetenv.c	\
			./src/my_setenv.c	\
			./src/env_error_handling.c	\
			./src/my_setenv_utils.c	\
			./src/get_envhome.c	\
			./src/my_exit.c	\
			./src/my_exit_utils.c	\
			./src/my_cdir.c	\
			./src/my_cdir_utils.c	\
			./src/get_pastdir.c	\
			./src/my_cdir2.c	\
			./src/my_segfault.c	\
			./src/redirect_handler.c	\
			./src/detect_redirect.c	\
			./src/handle_redirect_file.c	\
			./src/array_utils.c	\
			./src/utils.c	\
			./src/utilss.c	\
			./src/utilsss.c	\

INC		=	include/my.h

RM		=	rm -f

OBJ		=	$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) -g3

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) Makefile~
	$(RM) lib/my/*.o
	$(RM) *.c
	$(RM) src/*.c~
	$(RM) lib/my/build.sh~

re: fclean all
