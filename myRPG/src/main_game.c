/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** main_game.c
*/

#include "my.h"
#include "utils.h"
#include <unistd.h>
#include "game_menu.h"

void event_begin_game(arg_t *arg);

int main_game(arg_t *arg, intro_t *intro, game_menu_t *game_menu, int start)
{
    int bas = 60;
    int droite = 15;
    while (sfRenderWindow_isOpen(arg->window)) {
        manage_event(arg, intro, game_menu);
        if (display_window(arg, intro, game_menu, &intro->music)
        == BACK_TO_MENU)
            return BACK_TO_MENU;
        if (start == 0) {
            walk_png(arg, &bas, &droite, &start);
        }
    }
    return (0);
}



//!!!!! SHOP + CENTRE POKEMON
// SAVE
