##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## Makefile for BSQ project
##

CC		=	gcc -Wall -Wextra -g

CFLAGS		=	-I include

NAME		=	bsq

SRC		=	src/bsq_base.c \
			src/bsq_searcher.c \
			src/bsq_counter.c \
			src/bsq_printer.c \
			src/mini_printf.c \
			src/my_putchar.c \
			src/my_put_nbr.c \
			src/my_putstr.c \

INC		=	include/my.h

RM		=	rm -f

OBJ		=	$(SRC:.c=.o)

all:$(NAME)

$(NAME):$(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) Makefile~
	$(RM) lib/my/*.o
	$(RM) src/*.c~
	$(RM) lib/my/build.sh~

re: fclean all
