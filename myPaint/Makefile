##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## for mypaint
##

CC	=	gcc

CFLAGS	=	-W -Wall -Wextra

NAME	=	my_paint

SRC	=	./src/main.c	\
		./src/init.c	\
		./src/draw_colors.c	\
		./src/draw_page.c	\
		./src/display.c	\
		./src/settings.c	\
		./src/handle_colors.c	\
		./src/handle_events.c	\
		./src/file_button.c	\
		./src/options_page.c	\
		./src/list_utils.c	\
		./src/mini_printf.c	\
		./src/utils.c	\

OBJ     =       $(SRC:.c=.o)

CSFML	=	-lcsfml-graphics -lcsfml-system -lcsfml-audio -lcsfml-window

RM	=	rm -f

all:$(NAME)

$(NAME):$(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(CFLAGS) $(CSFML)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) Makefile~
	$(RM) lib/my/*.o
	$(RM) src/*.c~
	$(RM) lib/my/build.sh~

re: fclean all
