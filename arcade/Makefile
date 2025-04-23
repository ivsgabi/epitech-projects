##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Arcade
##

SRC=src/main.cpp \
	src/Core.cpp \
	src/Exceptions/CoreExceptions.cpp \

OBJ	=	$(SRC:.cpp=.o)

NAME	=	arcade

CPPFLAGS=	-iquote ./include

CXXFLAGS=-Wall -Wextra -Werror -std=c++20 -fno-gnu-unique

LIBS_MAKEFILE=LibsMakefile

RM?	=	rm -f

all: 	$(NAME)

$(NAME): core
$(NAME): games
$(NAME): graphicals

core: $(OBJ)
	$(CXX) -o $(NAME) $(OBJ)

games:
	[ -d lib/ ] || mkdir -p lib/
	make games -f $(LIBS_MAKEFILE)

graphicals:
	[ -d lib/ ] || mkdir -p lib/
	make graphicals -f $(LIBS_MAKEFILE)

clean:
	make clean -f $(LIBS_MAKEFILE)
	$(RM) $(OBJ)

fclean: clean
	make fclean -f $(LIBS_MAKEFILE)
	$(RM) $(NAME)

re: fclean all

.PHONY: fclean clean re all core
