##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## wolfram
##

NAME	=	imageCompressor

BINARY := 	$(shell stack path --local-install-root)

all:
	stack build
	cp $(BINARY)/bin/$(NAME)-exe ./$(NAME)

clean:
	stack clean

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
