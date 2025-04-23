/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** display_window.c
*/

// #include "display.h"
#include "intro_struct.h"
#include "game_menu.h"

int display_window(arg_t *arg, intro_t *intro, game_menu_t *game_menu,
sfMusic **music)
{
    sfRenderWindow_clear(arg->window, sfBlack);
    display_all_img(arg, arg->window);

    sfRenderWindow_setView(arg->window, arg->view);
    if (handle_game_menu(arg, intro, game_menu, music) == BACK_TO_MENU)
        return (BACK_TO_MENU);
    sfRenderWindow_setView(arg->window, arg->view);
    sfRenderWindow_display(arg->window);
    return (0);
}
