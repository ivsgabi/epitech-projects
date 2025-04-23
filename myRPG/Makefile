##
## EPITECH PROJECT, 2022
## mypaint
## File description:
## Makefile
##


NAME = my_rpg

DISPLAY = display_img.c			\
	  	  display_window.c		\
		  display_text.c		\
		  display_battle.c		\
		  display_attack.c		\
		  display_bag.c			\
		  display_all_btn.c		\
		  display_inventory.c   \
		  display_all_pokemon.c	\
		  display_battle_arene.c

UTILS = count_nb_lines.c	    \
	    len_line.c				\
	    my_strcpy.c				\
	    my_strdup.c				\
	    my_strlen.c				\
	    my_str_to_word_array.c	\
		my_atoi.c				\
		my_atof.c				\
		my_itoa.c				\
		mini_printf.c			\
	    my_put_nbr.c			\
		my_put_float.c

MOVEMENTS = all_mvt.c			\
	        move_down.c			\
	        move_up.c			\
	        move_left.c			\
	        move_right.c

MENU = init_menu.c				\
       handle_intro.c			\
	   handle_settings.c		\
	   settings_opt.c			\
	   handle_buttons_opt.c		\
	   sound_settings.c			\
	   window_settings.c		\
	   choose_character.c		\

GAME_MENU = handle_game_menu.c	\
			game_menu_options.c	\
			game_menu_options2.c\
			save_game.c

INIT = init_struct_arg.c		\
	   init_struct_img.c		\
	   init_struct_player.c		\
	   init_struct_pokemon.c	\
	   init_struct_text.c		\
	   init_battle_inventory.c	\
	   init_struct_intro.c		\
	   init_struct_buttons.c	\
	   init_struct_gm.c			\
	   init_struct_save.c		\
	   init_choose.c

FREE = free_all.c	\
	   free_img.c	\
	   free_pokemon.c

BATTLE = attack_pressed.c		\
	  	 capture_pokemon.c		\
		 fight.c				\
		 manage_options.c		\
		 options_pressed.c		\
		 start_fight.c			\
		 end_of_battle.c		\
		 choose_pokemon.c		\
		 change_pos_btn.c		\
		 select_pokemon.c		\
		 change_pokemon_combat.c\
		 evolution_pokemon.c


SRC	= main.c					\
	  main_game.c				\
	  read_map.c				\
	  manage_event.c			\
	  begin_game.c				\
	  speak_to_pnj.c			\
	  display_button.c			\
	  teleportation.c           \
	  switch_pokemon.c			\
	  shop.c					\
	  save_party.c				\
	  resume_game.c				\

display = src/display

utils = src/utils

battle = src/battle

move_player = src/move_player

menu_intro = src/menu-intro

game_menu = src/game_menu

init = src/init

free = src/free

src = src

OBJ = $(addprefix $(display)/, $(DISPLAY:.c=.o)) \
	  $(addprefix $(utils)/, $(UTILS:.c=.o)) \
	  $(addprefix $(move_player)/, $(MOVEMENTS:.c=.o)) \
	  $(addprefix $(init)/, $(INIT:.c=.o)) \
	  $(addprefix $(menu_intro)/, $(MENU:.c=.o)) \
	  $(addprefix $(game_menu)/, $(GAME_MENU:.c=.o)) \
	  $(addprefix $(free)/, $(FREE:.c=.o)) \
	  $(addprefix $(battle)/, $(BATTLE:.c=.o)) \
	  $(addprefix $(src)/, $(SRC:.c=.o))

CPPFLAGS += -Iinclude

CFLAGS += -Wall -Wextra

LDFLAGS	= -lm -lcsfml-graphics -lcsfml-audio -lcsfml-system -lcsfml-window

MAKEFLAGS += --no-print-directoy

CC ?= gcc

all : $(NAME)

$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean :
	@$(RM) $(OBJ)
	@$(RM) $(wildcard *.log)

fclean : clean
	@$(RM) $(wildcard vgcore.*)
	@$(RM) $(NAME)

re : fclean
	make all

debug : re
debug : export CFLAGS = -g3

.PHONY : all clean fclean re debug
